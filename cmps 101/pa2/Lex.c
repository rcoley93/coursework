//Ryan Coley
//rjcoley
//pa2
//Lex.c
//sorts a set of words from a document 
//then arranges them lexographically 
//then saves it in a new file

#include "List.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 160

int main(int argc, char* argv[]){
	
	FILE *fileIn, *fileOut;
	char charLine[MAX_LEN];
	List listOrderedWords = newList();
	int intLineCount=0;
	
	//make sure that there is the correct amount of arguments
	if(argc != 3){
		printf("Usage: inputFile outputFile\n");
		exit(1);
	}else{
		
		fileIn = fopen(argv[1],"r");
		fileOut = fopen(argv[2],"w");
		
		//if input file is null quit
		if(fileIn==NULL){
			printf("Error: unable to read input file!\n");
			exit(1);
		}
		
		//if output file is null quit
		if(fileOut==NULL){
			printf("Error: unable to write to output file!\n");
			exit(1);
		}
		
		//get number of lines in file
		while(fgets(charLine,MAX_LEN,fileIn)!=NULL){
			intLineCount++;
		}
		fclose(fileIn);
		
		//set up string array and get words
		fileIn = fopen(argv[1],"r");
		char charUnorderedWords[intLineCount][MAX_LEN];
		for(int i=0;i<intLineCount;i++){
			for(int j = 0;j<MAX_LEN;j++){
				charUnorderedWords[i][j] = '\0';
			}
			fgets(charLine,MAX_LEN,fileIn);
			if(i==intLineCount-1) strcpy(charUnorderedWords[i],charLine);
			else strncpy(charUnorderedWords[i],charLine,strlen(charLine)-2);
		}
		fclose(fileIn);
		
		//insertsion sort
		append(listOrderedWords,0);
		for(int i=1;i<intLineCount;i++){
			moveTo(listOrderedWords,0);
			
			
			char charWordToInsert[MAX_LEN];
			char charWordInList[MAX_LEN];
			
			for(int i=0;i<MAX_LEN;i++){
				charWordToInsert[i]='\0';
				charWordInList[i]='\0';
			}
			
			//get the word to insert
			strncat(charWordToInsert,charUnorderedWords[i],sizeof(charUnorderedWords[i]));
			
			//get the word currently in the list
			strncat(charWordInList,charUnorderedWords[getElement(listOrderedWords)],sizeof(charUnorderedWords[getElement(listOrderedWords)]));
			
			//see if they are the WordToInsert is first
			if(strcmp(charWordToInsert,charWordInList) < 0) prepend(listOrderedWords,i);
			else{
				for(int j=0;j<length(listOrderedWords);j++){
					//insert the WordToInsert if it comes last
					if(j == length(listOrderedWords)-1){
								append(listOrderedWords,i);
								break;
					}else{
						moveTo(listOrderedWords,j);
						
						
						char charWordInListCurrent[MAX_LEN];
						char charWordInListAfter[MAX_LEN];
						
						for(int i=0;i<MAX_LEN;i++){
							charWordInListCurrent[i]='\0';
							charWordInListAfter[i]='\0';
						}
						
						//get the current word
						strcat(charWordInListCurrent,charUnorderedWords[getElement(listOrderedWords)]);
						
						moveTo(listOrderedWords,j+1);
						
						//get the word after the current word
						strcat(charWordInListAfter,charUnorderedWords[getElement(listOrderedWords)]);
						
						//see if the the WordToInsert is between WordInListCurrent and WordInListAfter
						if(strcmp(charWordToInsert, charWordInListCurrent) > 0 && strcmp(charWordToInsert,charWordInListAfter) < 0){
							insertBefore(listOrderedWords,i);
							break;
						}
					}
				}
			}
			
		}
		
		for(int i=0;i<length(listOrderedWords);i++){
			moveTo(listOrderedWords,i);
			
			//get word to print
			char charWord[MAX_LEN];
			strncpy(charWord,charUnorderedWords[getElement(listOrderedWords)],sizeof(charUnorderedWords[getElement(listOrderedWords)]));
			
			//print word
			fprintf(fileOut,"%s\n",charWord);
		}
		
		//close the file and free the list
		fclose(fileOut);
		freeList(&listOrderedWords);
		
		return 0;		
	}
}