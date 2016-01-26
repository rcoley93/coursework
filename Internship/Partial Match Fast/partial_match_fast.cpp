#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <regex.h>
#include <list>
#include <unordered_map>
#include <sstream>

using namespace std;

//converts an int to a string
string inttostring(int i) {
	stringstream ss;
	ss << i;
	return ss.str();
}

//appends the given line to a file
void outfile(string filename, string line){
	
	//open file to append
	ofstream outFile;
	outFile.open(filename.c_str(), fstream::out | fstream::app);
	
	//append
	outFile << line << endl;
	
	//close
	outFile.close();
}

//process the file
list<string> processFile(string strFileName){
	//open file
	ifstream ifsFile(strFileName);
	
	string strLine;
	
	//count number of lines
	int intCount = 0;
	while (getline(ifsFile, strLine)) {
		++intCount;
	}
	
	//write value to results
	outfile("results.txt","Lines in "+strFileName+": "+inttostring(intCount));
	cout << "Lines in " << strFileName << ": " << intCount << endl;
	
	//reset file
	ifsFile.clear();
	ifsFile.seekg(0, ios::beg);
	
	//create results
	list<string> strLines;
	
	//get lines in file
	while (getline(ifsFile, strLine)) {
		string line(strLine.begin(),strLine.end()-1);
		istringstream ss(line);
		getline(ss, strLine, '\n');
		strLines.emplace_back(strLine);		
	}
	
	//close file
	ifsFile.close();
	
	//return results
	return strLines;
	
}

//generate the regex
void generateRegEx(regex_t* regex, string strWord){
	
	//the pieces of the regex
	string strBegin("(.*)\\b(");
	string strEnd(")(s|es)?\\b(.*)");
	string strAltEnd("ies)\\b(.*)");
	
	string strRegEx = strBegin+strWord;
	
	//if it ends in a y and the letter before is a vowel then check for ies
	if(strWord[strWord.length()-1] == 'y' && (strWord[strWord.length()-2] == 'a' || strWord[strWord.length()-2] == 'e' || strWord[strWord.length()-2] == 'i' || strWord[strWord.length()-2] == 'o' || strWord[strWord.length()-2] == 'u')){
		strRegEx += "|" +strWord.substr(0,strWord.length()-1) + strAltEnd;
	}else strRegEx += strEnd;
	
	//compile the regex expression
	regcomp(regex, strRegEx.c_str() ,REG_EXTENDED|REG_ICASE|REG_NEWLINE);
}

//main
int main() {
	
	/* START Process the comparison words file */
	
		//get the compare file
		string strCompareFile = "nouns.txt";
		list<string> strCompare = processFile(strCompareFile);
	
	/* END Process the comparison words file */
	
	/* START Process the input file */

		//get the input file
		string strInputFile = "sample_text.txt";		
		list<string> strInput = processFile(strInputFile);
	
	/* END Process the input file */	

	/* START Compare the words */
	
		int intLineCount = 0;
		//for each line in the input
		for(auto strLine : strInput){
			
			//show progress
			if(intLineCount%100 == 0) cout<<intLineCount<<endl;
			++intLineCount;
			
			//for each comparison word
			for(auto strWord : strCompare){
				
				//generate the regex
				regex_t regex;
				generateRegEx(&regex,strWord);
				
				//see if it matches
				if(!regexec(&regex,strLine.c_str(),0,NULL,0)){
					
					//write it out to the file
					outfile("results.txt","Match found for: " + strWord + " (" + inttostring(intLineCount) + "): " + strLine);
				}
			
				//free regex
				regfree(&regex);
			}
		}	
	
	/* END Compare the words */	

	return 0;
}