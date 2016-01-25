//Ryan Coley
//rjcoley@ucsc.edu
//asg1
// $Id: commands.cpp,v 1.11 2014-06-11 13:49:31-07 - - $

#include <string>
#include <typeinfo>
#include "commands.h"
#include "debug.h"

commands::commands(): map ({
   {"cat"   , fn_cat   },
   {"cd"    , fn_cd    },
   {"echo"  , fn_echo  },
   {"exit"  , fn_exit  },
   {"ls"    , fn_ls    },
   {"lsr"   , fn_lsr   },
   {"make"  , fn_make  },
   {"mkdir" , fn_mkdir },
   {"prompt", fn_prompt},
   {"pwd"   , fn_pwd   },
   {"rm"    , fn_rm    },
   {"rmr"    , fn_rmr    },
   {"#"     , fn_hash  },
}){}

command_fn commands::at (const string& cmd) {
   // Note: value_type is pair<const key_type, mapped_type>
   // So: iterator->first is key_type (string)
   // So: iterator->second is mapped_type (command_fn)
   command_map::const_iterator result = map.find (cmd);
   if (result == map.end()) {
      throw yshell_exn (cmd + ": no such function");
   }
   return result->second;
}

//prints out the contents of a file
void fn_cat (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
    //get temp directory
   inode_ptr tempCWD = state.getCWD();
  
   //set up path
   wordvec path = split(words.at(1),"/");
   //remove the file name
   path.pop_back();
   path.insert(path.begin(),"cd");
   if(path.size() > 0){
      //change directories
      fn_cd(state,path);
   }
   
   
   directory_ptr dir = directory_ptr_of(state.getCWD()->getContents());
   map<string,inode_ptr> dMap = dir->getMap();
   wordvec filename = split(words.at(1),"/");
   plain_file_ptr pf;
   
   if(dMap.count(filename.back())==0){
     complain()<< "cat: ";
     for(string word : filename){
        cout<< word << "/";
     }
     cout<<": File does not exist!" << endl;
     return;
   }else{
      auto it = dMap.find(filename.back());
      pf = plain_file_ptr_of(it->second->getContents());
      wordvec data = pf->readfile();
      for(string word : data){
         cout<<word<<" ";
      }
      cout<<endl;
   }
   state.setCWD(tempCWD);
}

//changes the current directory
void fn_cd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1){
      state.setCWD(state.getRoot());
      return;
   }else if(words.size() > 2){
      complain() << "cd: More than two operands given!" <<endl;
   }else{
      wordvec path = split(words.at(1),"/");
      if(path.size() == 1 && path.at(0) == ".") return;
      try{
         inode_ptr tempCWD = state.getCWD();
         inode_ptr ptr;
         directory_ptr dir  = directory_ptr_of(tempCWD->getContents());
         map<string,inode_ptr>::iterator it;
         map<string,inode_ptr> contents = dir->getMap();
         for(unsigned i=0;i<path.size();++i){
            it = contents.find(path.at(i));
            if(it == contents.end()) throw invalid_argument
                                       ("No such directory!");
            else{
               dir = directory_ptr_of(it->second->getContents());
               contents = dir->getMap();
               ptr = it->second;
            }
         }
         state.setCWD(ptr);
      }catch(invalid_argument& ex){
         complain() << "cd: ";
         for(string word : path){
            cout<<word<<"/";
         }
         cout << " " << ex.what() << endl;
      } 
   }
}

//echo the words except for the command word
void fn_echo (inode_state& state, const wordvec& words){
   for(unsigned i = 1; i<words.size(); ++i){
      cout << words[i] << " ";
   }
   //set a new line
   cout << endl;
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

//exits the program and sets the exit status accordingly
void fn_exit (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   wordvec word;
   word.emplace_back("cd");
   fn_cd(state,word);
   vector<inode_ptr> temp;
   temp.emplace_back(state.getRoot());
   fn_rmr_helper(state,temp);
   //if there only is the operand then set the exitstatus to 0 and exit
   if(words.size() == 1){
      throw ysh_exit_exn();
   //if there is more than one operand then set 
   //the exit status to 127 and exit
   }else if(words.size() > 2){
      exit_status::set(127);
      throw ysh_exit_exn();
   //otherwise try to parse the exit status and exit
   }else{
      try{
         exit_status::set(stoi(words[1]));
         throw ysh_exit_exn();
      }catch(invalid_argument& ex){
         exit_status::set(127);
         throw ysh_exit_exn();
      }
   }
}

//lists all files and directories
void fn_ls (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr tempCWD = state.getCWD();
   if(words.size() != 1){
      fn_cd(state,words);
   }
   wordvec temp;
   temp.emplace_back(":");
   fn_pwd(state,temp);
   inode_ptr newCWD = state.getCWD();
   directory_ptr dir = directory_ptr_of(newCWD->getContents());
   map<string,inode_ptr> contents = dir->getMap();
   for(auto it : contents){
      cout << it.second->get_inode_nr() << "\t";
      try{
         directory_ptr dir = directory_ptr_of(it.second->getContents());
         cout << dir->size()<< "\t" << it.first << "/" << endl;
      }catch(...){
         plain_file_ptr dir = plain_file_ptr_of
                                 (it.second->getContents());
         cout << dir->size()<< "\t" << it.first << endl;
      }
   }
   
   state.setCWD(tempCWD);
}

//lists all files and directories recursively
void fn_lsr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr tempCWD = state.getCWD();
   if(words.size() != 1){
      fn_cd(state,words);
   }
   vector<inode_ptr> ptr;
   ptr.emplace_back(state.getCWD());
   fn_lsr_helper(state,ptr);
   state.setCWD(tempCWD);
}

//helper function to lsr
void fn_lsr_helper(inode_state& state, vector<inode_ptr>& ptrVec){
   while(!ptrVec.empty()){
      inode_ptr itVec = ptrVec.at(0);
      directory_ptr dir = directory_ptr_of(itVec->getContents());
      ptrVec.erase(ptrVec.begin());
      map<string,inode_ptr> contents = dir->getMap();
      wordvec temp;
      temp.emplace_back(":");
      state.setCWD(itVec);
      fn_pwd(state,temp);
      for(auto it : contents){
         cout << it.second->get_inode_nr() << "\t";
         try{
            directory_ptr dirTest = directory_ptr_of
                                       (it.second->getContents());
            if(it.first != "." && it.first != "..") 
               ptrVec.emplace_back(it.second);
            cout << dirTest->size()<< "\t" << it.first << "/\t"<< endl;
         }catch(...){
            plain_file_ptr pfTest = plain_file_ptr_of
                                       (it.second->getContents());
            cout << pfTest->size()<< "\t" << it.first << endl;
         }
      }
   }  
}

//makes a new file and inputs words or if it exists it replaces it
void fn_make (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   //get temp directory
   inode_ptr tempCWD = state.getCWD();
  
   //set up path
   wordvec path = split(words.at(1),"/");
   //remove the file name
   path.pop_back();
   path.insert(path.begin(),"cd");
   if(path.size() > 0){
      //change directories
      fn_cd(state,path);
   }
   
   
   directory_ptr dir = directory_ptr_of(state.getCWD()->getContents());
   map<string,inode_ptr> dMap = dir->getMap();
   wordvec filename = split(words.at(1),"/");
   wordvec data;
   plain_file_ptr pf;
   for(unsigned i = 2; i<words.size(); ++i){
         data.emplace_back(words.at(i));
   }
   try{
      if(dMap.count(filename.back())==0){
         pf = plain_file_ptr_of
                  (dir->mkfile(filename.back()).getContents());
      }else{
         auto it = dMap.find(filename.back());
         pf = plain_file_ptr_of(it->second->getContents());
      }
      pf->writefile(data);
   }catch(...){
      complain()<<"make: "<<filename.back()<<
                              ": This is a directory"<<endl;
   }
   
   //return to cwd
   state.setCWD(tempCWD);
   
}

//make a new dir
void fn_mkdir (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() == 1){
      complain()<<"mkdir: not enough operands";
      return;
   }
   //get temp directory
   inode_ptr tempCWD = state.getCWD();
  
   //set up path
   wordvec path = split(words.at(1),"/");
   path.insert(path.begin(),"cd");
   //remove the file name
   path.pop_back();
   if(path.size() > 0){
      //change directories
      fn_cd(state,path);
   }
   
   
   directory_ptr dir = directory_ptr_of(state.getCWD()->getContents());
   map<string,inode_ptr> dMap = dir->getMap();
   wordvec filename = split(words.at(1),"/");
   if(dMap.count(filename.back())==0){
      dir->mkdir(filename.back(),state.getCWD());
   }else{
      complain()<<"mkdir: "<< filename.back() 
            << " already exists as a file or directory!" << endl;
   }
   
   
   //return to cwd
   state.setCWD(tempCWD);
}

//changes prompt to new one
void fn_prompt (inode_state& state, const wordvec& words){
   string strNewPrompt;
   //get new prompt declaration
   for(unsigned i = 1; i<words.size(); ++i){
      strNewPrompt += words[i] + " ";
   }
   //set the new declaration
   state.prompt = strNewPrompt;
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

//prints out the current working directory
void fn_pwd (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   wordvec path;
   wordvec temp;
   temp.emplace_back("cd");
   temp.emplace_back("..");
   inode_ptr tempCWD = state.getCWD();
   while(state.getCWD() != state.getRoot()){
      inode_ptr ptr = state.getCWD();
      fn_cd(state,temp);
      directory_ptr dir = directory_ptr_of
                              (state.getCWD()->getContents());
      map<string,inode_ptr> dMap = dir->getMap();
      for(auto it : dMap){
         if(it.second == ptr){
            path.emplace_back(it.first);
            break;
         }
      }
   }
   cout << "/";
   for(auto str : path){
      cout << str << "/";
   }
   if(words.at(0) ==  ":") cout << ":";
   cout << endl;
   state.setCWD(tempCWD);
}

//removes files
void fn_rm (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   if(words.size() > 1){
      //get temp directory
      inode_ptr tempCWD = state.getCWD();
  
      //set up path
      wordvec path = split(words.at(1),"/");
      //remove the file name
      path.pop_back();
      path.insert(path.begin(),"cd");
      if(path.size() > 0){
         //change directories
         fn_cd(state,path);
      }
   
      wordvec filename = split(words.at(1),"/");
   
      directory_ptr dir = directory_ptr_of
                              (state.getCWD()->getContents());
      map<string,inode_ptr> dMap = dir->getMap();
      if(dMap.count(filename.back()) > 0){
         inode_ptr root = state.getRoot();
         inode_ptr inodePtr = dMap.find(filename.back())->second;
         if(root != inodePtr) dir->remove(filename.back());
         else complain()<<"rm: cannot remove root directory"<<endl;
      }else{ 
         complain()<<"rm: " << filename.back() << 
                                 ": No such file or directory" << endl;
         return;
      }
   
      //return to cwd
      state.setCWD(tempCWD);
   }else complain()<<"rm: missing operand" <<endl;
}

//remove all files
void fn_rmr (inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
   inode_ptr tempCWD = state.getCWD();
   if(words.size() != 1){
      fn_cd(state,words);
   }
   vector<inode_ptr> ptr;
   ptr.emplace_back(state.getCWD());
   fn_rmr_helper(state,ptr);
   state.setCWD(tempCWD);
}

//helper function for rmr
void fn_rmr_helper(inode_state& state, vector<inode_ptr>& ptrVec){
     while(!ptrVec.empty()){
      inode_ptr itVec = ptrVec.at(0);
      directory_ptr dir = directory_ptr_of(itVec->getContents());
      ptrVec.erase(ptrVec.begin());
      map<string,inode_ptr> contents = dir->getMap();
      vector<inode_ptr> temp;
      state.setCWD(itVec);
      for(auto it : contents){
         try{
            directory_ptr dirTest = directory_ptr_of
                                       (it.second->getContents());
            if(it.first != "." && it.first != "..") {
               temp.emplace_back(it.second);
               fn_rmr_helper(state,temp);
               dir->remove(it.first);
            }
            
         }catch(...){
            dir->remove(it.first);
         }
      }
     }
}

//this function only prints out flag information since its purpose
//is suppose to be a comment line
void fn_hash(inode_state& state, const wordvec& words){
   DEBUGF ('c', state);
   DEBUGF ('c', words);
}

int exit_status_message() {
   int exit_status = exit_status::get();
   cout << execname() << ": exit(" << exit_status << ")" << endl;
   return exit_status;
}
