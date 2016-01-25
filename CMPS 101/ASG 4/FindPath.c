//Ryan Coley
//rjcoley
//pa2
//FindPath.c
//takes an input file of a graph and
//outputs the adjacency list and paths from the file

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char* argv[]){
	FILE *fileIn, *fileOut;
	Graph graphInput;
	int intVertexA = -1, intVertexB = -1, intGraphSize;
	
	//make sure that there is the correct amount of arguments
	if(argc != 3){
		printf("Usage: inputFile outputFile\n");
		exit(1);
	}
	
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
	
	//get the graph size
	fscanf(fileIn,"%d",&intGraphSize);
	
	//create the graph
	graphInput = newGraph(intGraphSize);
	
	//read all of the verticies and add them to the graph
	while(1){
		fscanf(fileIn,"%d",&intVertexA);
		fscanf(fileIn,"%d",&intVertexB);
		
		if(intVertexA == 0 && intVertexB == 0) break;
		
		addEdge(graphInput,intVertexA,intVertexB);
	}
	
	//print adjacency list to file
	printGraph(fileOut,graphInput);
	fprintf(fileOut,"\n");
	
	//start running BFS
	while(1 && !feof(fileIn)){
		fscanf(fileIn,"%d",&intVertexA);
		fscanf(fileIn,"%d",&intVertexB);
			
		if(intVertexA == 0 && intVertexB == 0) break;
		
		BFS(graphInput,intVertexA);
		
		List listPath = newList();
		getPath(listPath,graphInput,intVertexB);
		
		if(front(listPath) == NIL) fprintf(fileOut,"The distance from %d to %d is infinite.\nNo %d-%d path exists.\n\n",intVertexA, intVertexB, intVertexA, intVertexB);
		else {
			fprintf(fileOut,"The distance from %d to %d is %d.\nA shortest %d-%d path is: ",intVertexA, intVertexB, getDist(graphInput,intVertexB) ,intVertexA, intVertexB);
			printList(fileOut,listPath);
			fprintf(fileOut,"\b.\n\n");
		}
		
		freeList(&listPath);
	}
	
	fclose(fileIn);
	fclose(fileOut);
	freeGraph(&graphInput);
	
	return 0;
}