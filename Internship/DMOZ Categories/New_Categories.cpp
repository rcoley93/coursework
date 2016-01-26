//all the includes
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

#define FILENAME "dmoz_map.txt"

//class to hold the url information
class dmozInfo {
   
   //variables needed for class
   private:
      int intID=-1;
      string strName = "";
      string strCategory= "";
   
   //functions needed for class
   public:
      //contructors
      dmozInfo(){}
      dmozInfo (int id,string name,string category){
         this->intID = id;
         this->strCategory = category;
         this->strName = name;
      }
      
      //getters
      string getCategory() { return this->strCategory; }
      int getID() { return this->intID; }
      string getName() { return this->strName; }

};

//class to hold the categories
class categoryInfo{
   //variables needed for class
   private:
      int intNewCategory=-1;
      string strName = "";
      list<categoryInfo> lstChildren;
      categoryInfo* ciParent = nullptr;
   
   //functions needed for class
   public:
      //contructors
      categoryInfo(){}
      categoryInfo (string name){
         this->strName = name;
      }
      
      //getters
      int getNewCategory() { return this->intNewCategory; }
      string getName() { return this->strName; }
      categoryInfo* getParent() { return this->ciParent; }
      list<categoryInfo>* getChildren() { return &(this->lstChildren); }
      
      string listChildren(){
         string strResult = "\n******CHILDREN******\n";
         int intCount = -1;
         for(auto& child : lstChildren){
            strResult += to_string(++intCount);
            strResult += ". ";
            strResult += child.getName();
            strResult += "\n";
         }
         return strResult;
      }
      
      categoryInfo* getChild(int id){
         if(id < lstChildren.size()){
            int intCount = -1;
            for(auto& child : lstChildren){
               if(++intCount == id) return &child;
            }
         }else return this;
      }
      
      //setter
      void setNewCategory(int category) {
         this->intNewCategory = category;
         for(auto& child : lstChildren){
            child.setNewCategory(category);
         }
      }
      
      void setParent(categoryInfo* const parent) {this->ciParent = parent;}
      
      //modifiers
      categoryInfo* insertChild(categoryInfo& newChild) {
         newChild.setParent(this);
         for(auto& child : lstChildren){
            if(child.getName() == newChild.getName()){
               return &child;
            }
         }
         lstChildren.emplace_back(newChild);
         return &newChild;
      }
      
      void clear() {
         lstChildren.clear();
      }
};

//appends the given line to a file
void outFile(string filename, string line){
	
	//open file to append
	ofstream osOutFile;
	osOutFile.open(filename.c_str(), fstream::out | fstream::app);
	
	//append
	osOutFile << line;
	
	//close
	osOutFile.close();
}

//takes a line and returns a dmozInfo object
dmozInfo parseLine(string line){
   int intPos, intID;
   string strName,strTemp,strCategory;
   
   //get the id
   intPos = -1;
   while(line[++intPos] != ','){
      strTemp += line[intPos];
   }
   intID = stoi(strTemp.c_str());
   
   //get the name
   while(line[++intPos] != ','){
      strTemp += line[intPos];
   }
   strName = strTemp;
   
   //get the Category
   strCategory = line.substr(++intPos);
   dmozInfo newDI(intID,strName,strCategory);
      
   return newDI;
}

list<string> parseCategories(string categories){
   list<string> lstResult;
   istringstream issCategories(categories);
   string strTemp;
   
   //no need for the Top category
   getline(issCategories,strTemp,',');
   
   while(getline(issCategories,strTemp,',')){
      lstResult.emplace_back(strTemp);
   }
   
   return lstResult;
}
   
void insertIntoTree(categoryInfo* parent, list<string>& categories){
   if(categories.size() > 0){
      
      //get the category
      string strCategory = categories.front();
      categories.pop_front();
      
      //create new child
      categoryInfo ciChild(strCategory);
      
      //insert child
      categoryInfo* ciNewParent = parent->insertChild(ciChild);
      
      //call function again on child
      insertIntoTree(ciNewParent,categories);
   }
}

void printTreeHelper(categoryInfo parent, string path,int& i){
   //print out progress
   if((++i)%1000 == 0) cout << i << endl;
  
  
   //print out itself 
   outFile(FILENAME,path);
   outFile(FILENAME, "|");
   outFile(FILENAME,to_string(parent.getNewCategory()));
   outFile(FILENAME,"\n");
   
   //print out the path of all of its children
   list<categoryInfo>* lstChildren = parent.getChildren();
   for(auto& child : *lstChildren){
      string strNewPath = path;
      strNewPath += ",";
      strNewPath += child.getName();
      printTreeHelper(child,strNewPath,i);
   }
}

void printTree(categoryInfo top){
   //print out the schematic
   outFile(FILENAME,"Path|newCategoryID");
   outFile(FILENAME,"\n");
   
   //print out the tree
   int intCount = -1;
   printTreeHelper(top,"Top",intCount);
}

void printMenu() {
   cout << "\n-------MENU-------" << endl;
   cout << "1. List children" << endl;
   cout << "2. Go to child" << endl;
   cout << "3. Go to parent" << endl;
   cout << "4. Set new id" << endl;
   cout << "5. View current id" << endl;
   cout << "6. Quit" << endl;
}
   
//main function
int main(){
   string strLine;
   
   //open the category data file
   ifstream isDMOZData;
   isDMOZData.open("dmoz_url_cats.csv", ios::in);
   
   //get the description line
   getline(isDMOZData,strLine);
   
   //parse all of the other lines
   map<string,int> mCategories;
   while(getline(isDMOZData,strLine)){
      dmozInfo diNew = parseLine(strLine);
      //get all the different categories
      mCategories[diNew.getCategory()] = -1;
   }
   
  
   //get root node ready for tree
   categoryInfo ciTop("Top");
   ciTop.setNewCategory(1075);
   
   //set up tree
   int intCount =-1;
   for(auto& category : mCategories){
      if(++intCount%100 == 0) cout << intCount << endl;
      list<string> lstTemp = parseCategories(category.first);
      insertIntoTree(&ciTop,lstTemp);
   }
   
   
   categoryInfo* ciCurrentNode = &ciTop;
   
   int intCommand = -1;
   while(intCommand != 7){
      cout << "********************************************" << endl;
      cout << "\nCurrent node: " << ciCurrentNode->getName() << endl;
      //print out the options
      printMenu();
      
      
      //get the user input
      cout<<"\nEnter in your choice: ";
      cin >> intCommand;
      
      //deal with the input
      switch (intCommand){
         int intID;
         case 1:
            cout << ciCurrentNode->listChildren();
            break;
         case 2:
            cout << "Enter the child id: ";
            cin >> intID;
            ciCurrentNode = ciCurrentNode->getChild(intID);
            break;
         case 3:
            if(ciCurrentNode->getParent() != nullptr){
               ciCurrentNode = ciCurrentNode->getParent();
            }
            break;
         case 4:
            cout << "Enter the new category id: ";
            cin >> intID;
            ciCurrentNode->setNewCategory(intID);
            break;
         case 5:
            cout << ciCurrentNode->getNewCategory() << endl;
            break;
         case 6:
            printTree(ciTop);
            break;
         default:
            cout << "Please enter in a valid command!" << endl;
      }
   }
   
   return 0;
}