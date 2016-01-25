//Ryan Coley
//rjcoley@ucsc.edu
//asg1
// $Id: inode.cpp,v 1.12 2014-07-03 13:29:57-07 - - $

#include <iostream>
#include <stdexcept>

using namespace std;

#include "debug.h"
#include "inode.h"

int inode::next_inode_nr {1};

//inode constructor
inode::inode(inode_t init_type):
   inode_nr (next_inode_nr++), type (init_type)
{
   switch (type) {
      case PLAIN_INODE:
           contents = make_shared<plain_file>();
           break;
      case DIR_INODE:
           contents = make_shared<directory>();
           break;
   }
   DEBUGF ('i', "inode " << inode_nr << ", type = " << type);
}

//returns the inode number of the inode
int inode::get_inode_nr() const {
   DEBUGF ('i', "inode = " << inode_nr);
   return inode_nr;
}

plain_file_ptr plain_file_ptr_of (file_base_ptr ptr) {
   plain_file_ptr pfptr = dynamic_pointer_cast<plain_file> (ptr);
   if (pfptr == nullptr) throw invalid_argument ("Not a plain file!");
   return pfptr;
}

directory_ptr directory_ptr_of (file_base_ptr ptr) {
   directory_ptr dirptr = dynamic_pointer_cast<directory> (ptr);
   if (dirptr == nullptr) throw invalid_argument ("Not a directory!");
   return dirptr;
}

//returns the size of a file_
//formula is size = number_of_words - 1 + number_of_char_in_each_char
size_t plain_file::size() const {
   size_t size {0};
   size = data.size()-1;
   for(string word : data){
      size += word.size();
   }
   DEBUGF ('i', "size = " << size);
   return size;
}

//prints out the file contents
const wordvec& plain_file::readfile() const {
   DEBUGF ('i', data);
   return data;
}

//writes the file contents to the plain file
void plain_file::writefile (const wordvec& words) {
   DEBUGF ('i', words);
   data.clear();
   for(unsigned i = 0; i<words.size(); ++i){
      data.emplace_back(words.at(i));
   }
}

//returns the size of the current directory
size_t directory::size() const {
   size_t size {0};
   size = dirents.size();
   DEBUGF ('i', "size = " << size);
   return size;
}

//removes a file or directory
void directory::remove (const string& filename) {
   DEBUGF ('i', filename);
   auto result = dirents.find(filename);
   shared_ptr<inode> file = result->second;
   try{
      directory_ptr dir = directory_ptr_of
                              (result->second->getContents());
      map<string,inode_ptr> dMap = dir->getMap();
      if(dir->size() <= 2){
         dMap.find(".")->second = nullptr;
         dMap.erase(dMap.find(".."));
         dir=nullptr;
         dirents.erase(result);
      }else complain() << "rm: The directory still has files in it!" 
               << endl;
   }catch(...){
      dirents.find(result->first)->second = nullptr;
      dirents.erase(result);
   }
}

//returns the map of the cwd
map<string,inode_ptr> directory::getMap(){
   return dirents;
}

//returns the contents of an inode
file_base_ptr inode::getContents(){
   return contents;
}

//makes and returns the address of a new directory
inode& directory::mkdir (const string& dirname, inode_ptr ptr){
   shared_ptr<inode> dir = make_shared<inode>(DIR_INODE);
   dirents.insert(pair<string,inode_ptr>(dirname,dir));
   directory_ptr dirNew = directory_ptr_of(dir->getContents());
   dirNew->dirents.insert(pair<string,inode_ptr>(".",dir));
   dirNew->dirents.insert(pair<string,inode_ptr>("..",ptr));
   return *dir;
}

//makes and returns the address of a new file
inode& directory::mkfile (const string& filename){
   shared_ptr<inode> pf = make_shared<inode>(PLAIN_INODE);
   dirents.insert(pair<string,inode_ptr>(filename,pf));
   return *pf;
}

//sets up root
inode_ptr directory::setupRoot(){
   shared_ptr<inode> root = make_shared<inode>(DIR_INODE);
   directory_ptr dirNew = directory_ptr_of(root->getContents());
   dirNew->dirents.insert(pair<string,inode_ptr>(".",root));
   dirNew->dirents.insert(pair<string,inode_ptr>("..",root));
   return root;
}

//deletes the root;
void directory::deleteRoot(inode_ptr ptr){
      directory_ptr dir = directory_ptr_of(ptr->getContents());
      map<string,inode_ptr> dMap = dir->getMap();
      for(auto it : dMap){
         it.second = nullptr;
      }
      ptr = nullptr;
}

void inode_state::deleteState(){
   directory dir;
   dir.deleteRoot(root);
}

//constructor for inode_state
inode_state::inode_state() {
   directory dir;
   root = dir.setupRoot();
   cwd = root;
   DEBUGF ('i', "root = " << root << ", cwd = " << cwd
          << ", prompt = \"" << prompt << "\"");
}

//returns the root
inode_ptr inode_state::getRoot(){
   DEBUGF('i', "root = " << root);
   return root;
}

//returns the cwd
inode_ptr inode_state::getCWD(){
   DEBUGF('i', "cwd = " << cwd);
   return cwd;
}

//sets cwd
void inode_state::setCWD(inode_ptr ptr){
   cwd = ptr;
}

ostream& operator<< (ostream& out, const inode_state& state) {
   out << "inode_state: root = " << state.root
       << ", cwd = " << state.cwd;
   return out;
}
