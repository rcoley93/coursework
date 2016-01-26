//all the includes
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>

using namespace std;

#define FILENAME "dmoz_map.txt"

//class to hold the category information
class dmozInfo {
   
   //variables needed for class
   private:
      int intID=-1;
      int intNewCategory=-1;
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
      int getNewCategory() { return this->intNewCategory; }
      int getID() { return this->intID; }
      string getName() { return this->strName; }
      
      //setter
      void setNewCategory(int category) {this->intNewCategory = category;}
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
   
   while(getline(issCategories,strTemp,',')){
      lstResult.emplace_back(strTemp);
   }
   
   return lstResult;
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
   map<dmozInfo,int> mCategories;
   while(getline(isDMOZData,strLine)){
      
      dmozInfo diNew = parseLine(strLine);
      
      //get all the different categories
      mCategories[diNew] = -1;
   }
   
   //insert them into a tree
   for(auto& category : mCategories){
      list<string> lstTemp = parseCategories(category.first.getCategory());
   }
   
   cout << "The number of categories is " << mCategories.size()<<endl;

   /*cout << "Enter your starting place: ";
   int intStart;
   cin >> intStart;
   
   //get the new category
   int count = -1;
   int intNewCategory;
   for(auto& category : mCategories){
      if(++count >= intStart){
         //get the input
         cout<<category.first<<": ";
         string strInput;
         cin>>strInput;
         if(strInput == "q"){
            cout << "Ending place: " << count <<endl;
            return 0;
         }else if(strInput == "."){
         }else{
            intNewCategory = stoi(strInput);
         }
      
         //write the output
         outFile(FILENAME,category.first);
         outFile(FILENAME,"|");
         outFile(FILENAME,to_string(intNewCategory));
         outFile(FILENAME,"\n");
      }
   }
   return 0;*/
}