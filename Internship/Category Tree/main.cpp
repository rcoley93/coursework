//all the includes
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <sstream>

#define FILENAME "new_dmoz_url_cats.csv"

using namespace std;

//class to hold the url information
class dmozInfo {
   
   //variables needed for class
   private:
      int intID=-1;
      string strName = "";
      string strCategory = "";
      string strNewCategory = "";
   
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
      string toString() {
         string strResult = to_string(intID);
         strResult+=",";
         strResult+=strName;
         strResult+=",";
         strResult+=strNewCategory;
         return strResult;
      }
      
      //setters
      void setNewCategory(string category){ this->strNewCategory = category; }

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
   
   //get the url
   while(line[++intPos] != ','){
      strTemp += line[intPos];
   }
   strName = strTemp;
   
   //get the Category
   strCategory = line.substr(++intPos);
   dmozInfo newDI(intID,strName,strCategory);
      
   return newDI;
}

int main() {
   cout<<"Starting to parse all of the files!"<<endl;
   string strLine;
   
   //parse the map
   ifstream isDMOZMap;
   isDMOZMap.open("dmoz_map.csv", ios::in);
   
   //get the format structure line
   getline(isDMOZMap,strLine);
   
   //parse all of the lines
   map<string,int> mNewCategories;
   while(getline(isDMOZMap,strLine)){
      int intPos = strLine.find("|");
      
      string strCategory = strLine.substr(0,intPos++);
      int intCategory = stoi(strLine.substr(intPos));
      
      mNewCategories[strCategory] = intCategory;
   }
   
   isDMOZMap.close();
   
   cout << "Parsed dmoz_map.csv" << endl;
   
   //parse the new categories
   ifstream isNewCategories;
   isNewCategories.open("category_tree.txt", ios::in);
   
   //get the format structure line
   getline(isDMOZMap,strLine);
   
   //parse all of the lines
   map<int,string> mOriginalCategories;
   while(getline(isNewCategories,strLine)){
      //get the id number
      int intStart = strLine.find("(");
      int intEnd = strLine.find(")");
      
      int intID = stoi(strLine.substr(intStart+1,intEnd));
      
      //get the category tree
      string strCategory = strLine.substr(0,intStart);
      
      mOriginalCategories[intID] = strCategory;
   }
   
   isNewCategories.close();
   
   cout << "Parsed category_tree.txt" << endl;
   
   //parse the dmoz url file
   ifstream isDMOZURLCategories;
   isDMOZURLCategories.open("dmoz_url_cats.csv",ios::in);
   
   //parse all of the lines
   int intLineCount = 0;
   list<dmozInfo> lstDMOZInfo;
   while(getline(isDMOZURLCategories,strLine)){
      dmozInfo diNew = parseLine(strLine);
      lstDMOZInfo.emplace_back(diNew);
      ++intLineCount;
   }
   
   isDMOZURLCategories.close();
   
   cout << "Parsed dmoz_url_cats.csv" << endl; 
   cout << "Finished Parsing files" << endl;
   cout << "Remapping the categories" << endl;
   cout << "Number of Categories to remap: " << intLineCount << endl;
      
   //set all of the new categories and print them out
   int intRemapCount = 0;
   for(auto& dmoz : lstDMOZInfo){
      if((++intRemapCount)%1000 == 0) cout << intRemapCount << endl;
      string strCategory = dmoz.getCategory();
      string strNewCategory = mOriginalCategories[mNewCategories[strCategory]];
      dmoz.setNewCategory(strCategory);
      outFile(FILENAME,dmoz.toString());
   }
   
   cout << "Finished Remapping the categories" << endl;
}