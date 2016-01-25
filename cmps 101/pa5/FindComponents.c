//Ryan Coley
//rjcoley
//pa5
//FindComponents.c
//Finds the strongly connected components of a graph

#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
		
		addArc(graphInput,intVertexA,intVertexB);
	}
	
	//print adjacency list to file
	fprintf(fileOut,"Adjacency list representation of G:\n");
	printGraph(fileOut,graphInput);
	fprintf(fileOut,"\n");
	
	//start running DFS
	List listOrder = newList();
	
	for(int i=1;i<=getOrder(graphInput);i++){
		append(listOrder,i);
	}
	
	DFS(graphInput,listOrder);
	
	Graph graphInputTranspose = transpose(graphInput);
	DFS(graphInputTranspose,listOrder);
	
	int intComponentNumber = -1;
	int intNumberOfComponents = 0;
		
	for(int i=1;i<=getOrder(graphInput);i++){
		if(getParent(graphInputTranspose,i)==NIL){
			intNumberOfComponents++;
		}
	}

	fprintf(fileOut,"G contains %d strongly connected components:",intNumberOfComponents);
	
	List listArray[intNumberOfComponents];
	for(int i=0;i<intNumberOfComponents;i++){
		listArray[i] = newList();
	}
	
	for(int i=0;i<length(listOrder);i++){
		moveTo(listOrder,i);
		int intNode = getElement(listOrder);
		if(getParent(graphInputTranspose,intNode) == NIL) intComponentNumber++;
		append(listArray[intComponentNumber],intNode);
	}
	
	for(int i=intNumberOfComponents-1;i>=0;i--){
		fprintf(fileOut,"\nComponent %d: ",intNumberOfComponents+1-i);
		printList(fileOut,listArray[i]);
	}
	
	for(int i=0;i<intNumberOfComponents;i++){
		freeList(&listArray[i]);
	}
	
	fprintf(fileOut,"\n");
		
	freeGraph(&graphInputTranspose);
	freeList(&listOrder);
	fclose(fileIn);
	fclose(fileOut);
	freeGraph(&graphInput);
	
	return 0;
}