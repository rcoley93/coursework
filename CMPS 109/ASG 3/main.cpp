//Ryan Coley
//rjcoley@ucsc.edu
//asg3
// $Id: main.cpp,v 1.8 2015-04-28 19:23:13-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;
using line_pair = xpair<string,string>;

//define the map that is going to be used
str_str_map test;

//print out all keys with a certain value
//if blank then all keys
void printKeys(string value){
   if(value == ""){
      for(auto itor = test.begin();itor != test.end();++itor){
         str_str_pair pair = *itor;
         cout<<pair.first<<" = "<<pair.second<<endl;
      }
   }else {
      for(auto itor = test.begin();itor != test.end();++itor){
         str_str_pair pair = *itor;
         if(pair.second == value) 
            cout<<pair.first<<" = "<<pair.second<<endl;
      }
   }
}

//prints out a key and its value
void echoKey(string key){
   auto itor = test.find(key);
   if(itor == test.end()){
      cerr<<key<<": key not found"<<endl;
      sys_info::set_exit_status(1);
   }else{
      str_str_pair pair = *itor;
      cout<<key<<" = "<<pair.second<<endl;
   }
}

//modifies a key
void modifyKey(string key, string value){
   auto itor = test.find(key);
   if(value == ""){
      if(itor == test.end()){
         cerr<<key<<": key not found"<<endl;
         sys_info::set_exit_status(1);
      }else test.erase(itor);
   }else{
      if(itor != test.end()){
         test.erase(itor);
      }
      test.insert(str_str_pair(key,value.substr(1)));
   }         
}

//function processes the line 
//to make it do the correct command
line_pair processLine(string strLine){   
   //no input
   if(strLine.length() == 0) return line_pair("#","");
   
   string strTrim = trim_copy(strLine, " \f\n\r\t\v");
   
   if(strTrim.length() == 0) return line_pair("#","");
   
   //if the first char is a #
   else if(strTrim.at(0) == '#'){
      
      //if the strTrim is more than just #
      if(strTrim.length() > 1) return line_pair("#",strTrim);
      //it only contained the #
      else return line_pair("#","");
      
   }else if(strTrim.at(0) == '='){
      
      //the string contained more than the =
      if(strTrim.length() > 1) return line_pair("=",strTrim);
      //string only contained =
      else return line_pair("=","");
   }
   
   //the last possible combination
   for(unsigned int i=0;i<strTrim.length();++i){
      if(strTrim.at(i) == '=')
         return line_pair(strTrim.substr(0,i),strTrim.substr(i));
   }
   
   return line_pair(strTrim,"");
}

//function deals with the line
void implementLine(line_pair lp){
   if(lp.first == "#") return;
   else if(lp.first == "="){
      //=
      if(lp.second == ""){
         printKeys("");
         //=value
      }else printKeys(lp.second.substr(1));
      return;
   }else{
      //key
      if(lp.second == "") echoKey(lp.first);
      
      else{
         
         line_pair partTwo = processLine(lp.second);
         //key=
         if(partTwo.second == "") modifyKey(lp.first,"");
         //key=value
         else modifyKey(lp.first,lp.second);
         
      }
   }
}

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);
   
   if((argc - optind) >= 1){
      
      int iOffset = 0;
      if((argc-optind)>1) ++iOffset;
      
      int iLineNumber = 0;
      for (char** argp = &argv[optind+iOffset]; argp != &argv[argc]; 
                                                               ++argp){
         string strLine;
         ifstream inputFile (*argp);
         if(inputFile.is_open()){
            while(getline(inputFile,strLine)){
               cout<<*argp<<": "<<++iLineNumber<<": "<<strLine<< endl;
               line_pair line = processLine(strLine);
               implementLine(line);
            }
         }else{
            cerr << "Error: Unable to open file!" << endl;
            sys_info::set_exit_status(1);
         }
         inputFile.close();
      }
   }else{
      string strLine;
      while(true){
         cout<<"-: ";
         if(getline(cin,strLine).eof()) break;
         line_pair line = processLine(strLine);
         implementLine(line);
      }
   }
   return sys_info::get_exit_status();
}

