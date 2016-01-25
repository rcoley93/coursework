//Ryan Coley
//rjcoley@ucsc.edu
//asg5
// $Id: cixd.cpp,v 1.3 2015-05-12 19:06:46-07 - - $

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"

logstream log (cout);
struct cix_exit: public exception {};

void reply_get(accepted_socket& client_sock, cix_header& header){
   //get the file
   ifstream file (header.filename, ifstream::binary);
   
   if(file){
      log << "Got the file: " << header.filename << "." << endl;
      //get length of file
      file.seekg(0,file.end);
      unsigned int fileLength = file.tellg();
      file.seekg(0, file.beg);
      
      //start the buffer
      log << "Reading file!" << endl;
      char* buffer = new char[fileLength];
      file.read(buffer,fileLength);
      
      //start the header
      cix_header header;
      header.command = CIX_FILE;
      header.nbytes = fileLength;
      
      //send the packet
      log << "Sent the header: " << header << "." << endl;
      send_packet (client_sock, &header, sizeof header);
      send_packet(client_sock, buffer, fileLength);
      
      //send the file
      log << "Sent the file." << endl;
      
      delete[] buffer;
   }else{
      cix_header header;
      header.command = CIX_NAK;
      string str = "Error! Unable to return file!";
      strcpy(header.filename,str.c_str());
      send_packet(client_sock,&header,sizeof header);
   }
   
   //close the file
   file.close();
}

void reply_put(accepted_socket& client_sock, cix_header& header){
   //set up the buffer
   char* buffer = new char[header.nbytes];
   recv_packet(client_sock, buffer, header.nbytes);
   log << "Received the file!" << endl;
   
   //get the file
   log << "Received the file!" << endl;
   
   //open the new file
   ofstream file(header.filename,ofstream::binary);
   
   if(file){
      
      //write the file
      file.write(buffer,header.nbytes+1);
      log << "Wrote the file!" << endl;
      
      //send the response
      header.command = CIX_ACK;
      header.nbytes = 0;
      string str = "";
      strcpy(header.filename,str.c_str());
      send_packet(client_sock, &header, sizeof header);
      
   }else{
      //send failure response
      header.command = CIX_NAK;
      header.nbytes = 0;
      string str = "Error! Unable to write file!";
      strcpy(header.filename, str.c_str());
      send_packet(client_sock, &header, sizeof header);
   }
   
   //delete the buffer and close the file
   delete[] buffer;
   file.close();
}

void reply_rm(accepted_socket& client_sock, cix_header& header) {
   string str(header.filename);
   if(unlink(header.filename) != 0){
      log << "Failed to remove file: "<< str << "." << endl;
      header.command = CIX_NAK;
      header.nbytes = errno;
      send_packet(client_sock, &header, sizeof header);
   }else{
      header.command = CIX_ACK;
      send_packet(client_sock, &header, sizeof header);
   }   
}

void reply_ls (accepted_socket& client_sock, cix_header& header) {
   FILE* ls_pipe = popen ("ls -l", "r");
   if (ls_pipe == NULL) { 
      log << "ls -l: popen failed: " << strerror (errno) << endl;
      header.command = CIX_NAK;
      header.nbytes = errno;
      send_packet (client_sock, &header, sizeof header);
   }
   string ls_output;
   char buffer[0x1000];
   for (;;) {
      char* rc = fgets (buffer, sizeof buffer, ls_pipe);
      if (rc == nullptr) break;
      ls_output.append (buffer);
   }
   header.command = CIX_LSOUT;
   header.nbytes = ls_output.size();
   memset (header.filename, 0, FILENAME_SIZE);
   log << "sending header " << header << endl;
   send_packet (client_sock, &header, sizeof header);
   send_packet (client_sock, ls_output.c_str(), ls_output.size());
   log << "sent " << ls_output.size() << " bytes" << endl;
}

void run_server (accepted_socket& client_sock) {
   log.execname (log.execname() + "-server");
   log << "connected to " << to_string (client_sock) << endl;
   try {   
      for (;;) {
         cix_header header; 
         recv_packet (client_sock, &header, sizeof header);
         log << "received header " << header << endl;
         switch (header.command) {
            case CIX_LS: 
               reply_ls (client_sock, header);
               break;
            case CIX_RM:
               reply_rm(client_sock,header);
               break;
            case CIX_PUT:
               reply_put(client_sock,header);
               break;
            case CIX_GET:
               reply_get(client_sock,header);
            default:
               log << "invalid header from client" << endl;
               log << "cix_nbytes = " << header.nbytes << endl;
               log << "cix_command = " << header.command << endl;
               log << "cix_filename = " << header.filename << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   throw cix_exit();
}

void fork_cixserver (server_socket& server, accepted_socket& accept) {
   pid_t pid = fork();
   if (pid == 0) { // child
      server.close();
      run_server (accept);
      throw cix_exit();
   }else {
      accept.close();
      if (pid < 0) {
         log << "fork failed: " << strerror (errno) << endl;
      }else {
         log << "forked cixserver pid " << pid << endl;
      }
   }
}

void reap_zombies() {
   for (;;) {
      int status;
      pid_t child = waitpid (-1, &status, WNOHANG);
      if (child <= 0) break;
      log << "child " << child
           << " exit " << (status >> 8)
           << " signal " << (status & 0x7F)
           << " core " << (status >> 7 & 1) << endl;
   }
}

void signal_handler (int signal) {
   log << "signal_handler: caught " << strsignal (signal) << endl;
   reap_zombies();
}

void signal_action (int signal, void (*handler) (int)) {
   struct sigaction action;
   action.sa_handler = handler;
   sigfillset (&action.sa_mask);
   action.sa_flags = 0;
   int rc = sigaction (signal, &action, nullptr);
   if (rc < 0) log << "sigaction " << strsignal (signal) << " failed: "
                   << strerror (errno) << endl;
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   signal_action (SIGCHLD, signal_handler);
   in_port_t port = get_cix_server_port (args, 0);
   try {
      server_socket listener (port);
      for (;;) {
         log << to_string (hostinfo()) << " accepting port "
             << to_string (port) << endl;
         accepted_socket client_sock;
         for (;;) {
            try {
               listener.accept (client_sock);
               break;
            }catch (socket_sys_error& error) {
               switch (error.sys_errno) {
                  case EINTR:
                     log << "listener.accept caught "
                         << strerror (EINTR) << endl;
                     break;
                  default:
                     throw;
               }
            }
         }
         log << "accepted " << to_string (client_sock) << endl;
         try {
            fork_cixserver (listener, client_sock);
            reap_zombies();
         }catch (socket_error& error) {
            log << error.what() << endl;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

