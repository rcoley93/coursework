//Ryan Coley
//rjcoley@ucsc.edu
//asg5
// $Id: cix.cpp,v 1.2 2015-05-12 18:59:40-07 - - $

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
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

//borrowed the following code from 
//http://www.cplusplus.com/faq/sequences/strings/trim/
string trim_right_copy(const string& s,
                       const string& delimiters = " \f\n\r\t\v"){
  return s.substr(0,s.find_last_not_of(delimiters)+1);
}

string trim_left_copy(const string& s,
                      const string& delimiters = " \f\n\r\t\v"){
  return s.substr(s.find_first_not_of(delimiters));
}

string trim_copy(const string& s,
                 const string& delimiters = " \f\n\r\t\v"){
  return trim_left_copy(trim_right_copy(s,delimiters),delimiters);
}
//end code borrowing

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT},
   {"help", CIX_HELP},
   {"ls"  , CIX_LS  },
   {"rm"  , CIX_RM  },
   {"put" , CIX_PUT },
   {"get" , CIX_GET },
};

void cix_help() {
   static vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_get(client_socket& server, string filename){
   
   //start the request
   cix_header header;
   header.command = CIX_GET;
   strcpy(header.filename,filename.c_str());
   send_packet(server, &header, sizeof header);
   log << "Sent the request!" <<endl;
   
   //get the response
   recv_packet(server, &header, sizeof header);
   log << "Got the response!" << endl;
      
   //the command couldn't be done
   if(header.command == CIX_NAK) {
      log << "Error! The command was sent, but there was an error in \
              the request! please try again! " << endl;
      log << "The server returned: " << header << "." <<endl;
   //the server returned something other than a CIX_FILE
   }else if (header.command != CIX_NAK && header.command != CIX_FILE){
      log << "CIX_GET was sent, but the server did not return CIX_FILE." 
          << endl;
      log << "The server returned: " << header << "." << endl;
   }else{
   
      //set up the buffer
      char* buffer = new char[header.nbytes];
      recv_packet(server, buffer, header.nbytes);
      log << "Received the file!" << endl;
      
      //open the new file
      ofstream file(filename,ofstream::binary);
   
      if(file){
      
         //write the file
         file.write(buffer,header.nbytes);
         log << "Wrote the file!" << endl;
            
      }else{
         log << "Unable to write file!" << endl;
         delete[] buffer;
         file.close();
         return;
      }
   
      //delete the buffer and close the file
      delete[] buffer;
      file.close();
      cout << "The file was successfully received!" << endl;
   }
}

void cix_put(client_socket& server, string filename){
   //get the file
   ifstream file (filename, ifstream::binary);
   
   if(file){
      log << "Got the file: " << filename << "." << endl;
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
      header.command = CIX_PUT;
      header.nbytes = fileLength;
      strcpy(header.filename, filename.c_str());
      
      //send the packet
      log << "Sent the header: " << header << "." << endl;
      send_packet (server, &header, sizeof header);
      send_packet(server, buffer, fileLength);
      
      //send the file
      log << "Sent the file." << endl;
      
      //get the response
      recv_packet(server, &header, sizeof header);
      
      //the command couldn't be done
      if(header.command == CIX_NAK) {
         log << "Error! The command was sent, but there was an error in \
                 the request! please try again! " << endl;
         log << "The server returned: " << header << "." <<endl;
      //the server returned something other than a CIX_ACK
      }else if (header.command != CIX_NAK && header.command != CIX_ACK){
         log << "CIX_PUT was sent, but the server did not return CIX_ACK." 
             << endl;
         log << "The server returned: " << header << "." << endl;
      }else{
         cout << "The file was successfully sent!" << endl;
      }
      
      delete[] buffer;
   }else{
      log << "Error! Unable to open the file!" << endl;
   }
   
   //close the file
   file.close();
}

void cix_rm(client_socket& server, string filename){
   
   //set up the header
   cix_header header;
   
   //set the request
   header.command = CIX_RM;
   
   //set the file name
   strcpy(header.filename, filename.c_str());;
   
   //send the header
   log << "Sent the header: " << header << "." << endl;
   send_packet (server, &header, sizeof header);
   
   //receive the return header
   recv_packet (server, &header, sizeof header);
   
   //get the response
   //the command couldn't be done
   if(header.command == CIX_NAK) {
      log << "Error! The command was sent, but there was an error in \
              the request! please try again! " << endl;
      log << "The server returned: " << header << "." <<endl;
   //the server returned something other than a CIX_ACK
   }else if (header.command != CIX_NAK && header.command != CIX_ACK){
      log << "CIX_RM was sent, but the server did not return CIX_ACK." 
          << endl;
      log << "The server returned: " << header << "." << endl;
   }else{
      cout << "The file was successfully removed!" << endl;
   }       
}

void cix_ls (client_socket& server) {
   //start the header
   cix_header header;
   header.command = CIX_LS;
   log << "Sent the header: " << header << "." << endl;
   
   //send the packet
   send_packet (server, &header, sizeof header);
   
   //get the response
   recv_packet (server, &header, sizeof header);
   
   //the command couldn't be done
   if(header.command == CIX_NAK){
      log << "Error! The command was sent, but there was an error in \
              the request! please try again! " << endl;
      log << "The server returned: " << header << "." <<endl;
   //the server returned something other than CIX_LSOUT
   }else if (header.command != CIX_LSOUT && header.command != CIX_NAK) {
      log << "CIX_LS was sent, but the server did not return CIX_LSOUT"
          << endl;
      log << "The server returned: " << header << "." << endl;
      
   //everything was fine
   //print out the info seceived
   }else {
      //get the next packet
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "Received: " << header.nbytes << " bytes." << endl;
      buffer[header.nbytes] = '\0';
      
      //print out the list of files
      cout << buffer;
   }
}

void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

vector<string> split(string str){
   
   vector<string> strCommand;
   
   //get the position of the first space
   size_t space_pos = str.find_first_of(" ");
   
   //if there isn't then just send the command on its way
   if(space_pos == string::npos){
      strCommand.push_back(str);
      return strCommand;
   }else{
      //check to see if there is a \ in the file name
      size_t slash_check = str.find_first_of("\\");
      if(slash_check != string::npos){
         //if there is then there is an error in the syntax
         strCommand.push_back("Error! Command syntax error!");
         return strCommand;
      }
      
      //final check to make sure that the string is the correct length
      if(str.substr(space_pos+1).length()-1 > FILENAME_SIZE){
         strCommand.push_back("Error! Filename too long!");
         return strCommand;
      }
   }
   
   //otherwise return the command
   strCommand.push_back(str.substr(0,space_pos));
   strCommand.push_back(str.substr(space_pos+1));
   
   return strCommand;
   
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "Starting." << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() != 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "Connecting to " << host << " on port " << port << "."
          <<endl;
      client_socket server (host, port);
      log << "Connected to " << to_string (server) << "."<<endl;
      for (;;) {
         string line;
         getline (cin, line);
         vector<string> strCommand = split(trim_copy(line));
         if (cin.eof()) throw cix_exit();
         log << "Command: " << line << "." << endl;
         const auto& itor = command_map.find (strCommand.at(0));
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               cix_ls (server);
               break;
            case CIX_PUT:
               cix_put(server, strCommand.at(1));
               break;
            case CIX_GET:
               cix_get(server, strCommand.at(1));
               break;
            case CIX_RM:
               cix_rm (server, strCommand.at(1));
               break;
            default:
               log << line << ": invalid command" << endl;
               break;
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

