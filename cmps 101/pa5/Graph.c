//Ryan Coley
//rjcoley
//pa5
//Graph.c
//Graph datastruture implementation

#include "List.h"
#include "Graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//define White Grey Black
int W = 0;
int P = 1;
int B = 2;

//define private function
void makeNull(Graph G);

//define graph struct
typedef struct GraphObj{
	List* listAdjacency;
	int* intColor;
	int* intParent;
	int* intDiscover;
	int* intFinish;
	int intOrder;
	int intSize;
} GraphObj;


//constructor and deconstructor
Graph newGraph(int n){
	if(n<1){
		printf("Graph Error: calling newGraph() with no size!\n");
		exit(1);
	}
	Graph graphNew = malloc(sizeof(GraphObj));
	graphNew->listAdjacency = calloc(n+1,sizeof(List));
	graphNew->intColor = calloc(n+1,sizeof(int));
	graphNew->intDiscover = calloc(n+1,sizeof(int));
	graphNew->intFinish = calloc(n+1,sizeof(int));
	graphNew->intParent = calloc(n+1,sizeof(int));
	graphNew->intOrder = n;
	graphNew->intSize = 0;
	for(int i=1;i<=n;i++){
		graphNew->intParent[i] = NIL;
		graphNew->intColor[i] = W;
		graphNew->listAdjacency[i] = newList();
	}
	return graphNew;
}
void freeGraph(Graph* pG){
	if(pG!=NULL && *pG!=NULL){
		makeNull((*pG));
		for(int i=1;i<=getOrder((*pG));i++){
			freeList(&((*pG)->listAdjacency[i]));
		}
		free((*pG)->listAdjacency);
		free((*pG)->intColor);
		free((*pG)->intParent);
		free((*pG)->intDiscover);
		free((*pG)->intFinish);
		free(*pG);
		*pG = NULL;
	}else{
		printf("Graph Error: calling freeGraph() on NULL Graph reference!\n");
		exit(1);
	}
}

//access functions

//return the number of vertices
int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference!\n");
		exit(1);
	}
	return(G->intOrder);
}

//return the number of edges
int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference!\n");
		exit(1);
	}
	return(G->intSize);
}

//returns the parent of the vertex based off of the last time DFS() was called
/* Pre: 1<=u<=n<=getOrder(G)*/
int getParent(Graph G,int u){
	if(G == NULL){
		printf("Graph Error: calling getParent() on NULL Graph reference!\n");
		exit(1);
	}else if(u<1 || u>getOrder(G)){
		printf("Graph Error: vertex is not within bounds of the Graph!\n");
		exit(1);
	}
	return(G->intParent[u]);
}

//returns the discover time of the vertex based off of the last time DFS() was called
/* Pre: 1<=u<=n<=getOrder(G)*/
int getDiscover(Graph G,int u){
	if(G == NULL){
		printf("Graph Error: calling getDiscover() on NULL Graph reference!\n");
		exit(1);
	}else if(u<1 || u>getOrder(G)){
		printf("Graph Error: vertex is not within bounds of the Graph!\n");
		exit(1);
	}
	return(G->intDiscover[u]);
}

//returns the finish time of the vertex based off of the last time DFS() was called
/* Pre: 1<=u<=n<=getOrder(G)*/
int getFinish(Graph G,int u){
	if(G == NULL){
		printf("Graph Error: calling getFinish() on NULL Graph reference!\n");
		exit(1);
	}else if(u<1 || u>getOrder(G)){
		printf("Graph Error: vertex is not within bounds of the Graph!\n");
		exit(1);
	}
	return(G->intFinish[u]);
}

//manipulation funcitons

//removes all edges and arcs from a graph
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: calling makeNull() on NULL Graph reference!\n");
		exit(1);
	}
	int intOrderOfG = getOrder(G);
	for(int i=1;i<=intOrderOfG;i++){
		clear(G->listAdjacency[i]);
	}
}

//adds a two way arc to two verticies
/* Pre: 1<=u<=n, 1<=v<=n */
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addEdge() on NULL Graph reference!\n");
		exit(1);
	}else if(u<1 || u>getOrder(G) || v<1 || v>getOrder(G)){
		printf("Graph Error: a vertex is not within bounds of the Graph!\n");
		exit(1);
	}
	addArc(G,u,v);
	addArc(G,v,u);
}

//adds v to adjacency list of u
/* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: calling addArc() on NULL Graph reference!\n");
		exit(1);
	}else if(u<1 || u>getOrder(G) || v<1 || v>getOrder(G)){
		printf("Graph Error: a vertex is not within bounds of the Graph!\n");
		exit(1);
	}
	List listInsert = G->listAdjacency[u];
	
	//insertion sort
	if(length(listInsert) == 0){
		append(listInsert,v);
		return;
	}
	for(int i=0;i<length(listInsert);i++){
		moveTo(listInsert,i);
		
		//get the word in the list
		int intvertexInList = getElement(listInsert);
		
		//the vertex comes first in the list
		if(intvertexInList > v){
			prepend(listInsert,v);
			return;
		//the vertex is last in the list
		}else if(i==length(listInsert)-1){
			append(listInsert,v);
			return;
		//the vertex is somewhere inbetween
		}else{
			moveTo(listInsert,i+1);
			int intvertexInListAfter = getElement(listInsert);
			if(intvertexInList < v && intvertexInListAfter > v){
				insertBefore(listInsert,v);
				return;
			}
		}
	}
}

//performs DFS on the graph with List S as a Stack and a Order
/* Pre: getLength(S)==getOrder(G)*/
void DFS(Graph G, List S){
	if(G == NULL){
		printf("Graph Error: calling DFS() on NULL Graph reference!");
		exit(1);
	}else if(S == NULL){
		printf("Graph Error: calling DFS() on NULL List reference!");
		exit(1);
	}else if(length(S) != getOrder(G)){
		printf("Graph Error: calling DFS() with different sized List and Graph order!");
		exit(1);
	}
	
	List listOrder = copyList(S);
	clear(S);
	int intTime = 0;
	
	for(int i=0;i<getOrder(G);i++){
		G->intParent[i] = NIL;
		G->intColor[i] = W;
	}
	
	void Visit(int intNode){
		intTime++;
		G->intDiscover[intNode] = intTime;
		G->intColor[intNode] = P;
		for(int i=0;i<length(G->listAdjacency[intNode]);i++){
			moveTo(G->listAdjacency[intNode],i);
			int intNodeTemp = getElement(G->listAdjacency[intNode]);
			if(G->intColor[intNodeTemp] == W){
				G->intParent[intNodeTemp] = intNode;
				Visit(intNodeTemp);
			}
		}
		G->intColor[intNode] = B;
		intTime++;
		G->intFinish[intNode] = intTime;
		prepend(S,intNode);
	}
	
	while(length(listOrder) != 0){
		int intNode = front(listOrder);
		deleteFront(listOrder);
		if(G->intColor[intNode] == W){
			Visit(intNode);
		}
	}
}

//other operations

//switch the way of the lines to the graph
Graph transpose(Graph G){
	Graph graphNew = newGraph(getOrder(G));
	
	for(int i=1;i<=getOrder(G);i++){
		List listTemp = G->listAdjacency[i];
		for(int j=0;j<length(listTemp);j++){
			moveTo(listTemp,j);
			int intTemp = getElement(listTemp);
			addArc(graphNew,intTemp,i);
		}
	}
	
	return graphNew;
}

//returns an exact copy of the graph
Graph copyGraph(Graph G){
	Graph graphNew = newGraph(getOrder(G));
	
	for(int i=0;i<getOrder(G);i++){
		List listTemp = G->listAdjacency[i];
		for(int j=0;j<length(listTemp);j++){
			moveTo(listTemp,j);
			int intTemp = getElement(listTemp);
			addArc(graphNew,i,intTemp);
		}
	}
	
	return graphNew;
}

//print out the current graph in adjacency list form
void printGraph(FILE* out, Graph G){
	if(G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference!\n");
		exit(1);
	}else if(out == NULL){
		printf("Graph Error: calling printGraph() on NULL FILE reference!\n");
		exit(1);
	}else{
		for(int i=1;i<=getOrder(G);i++){
			fprintf(out,"%d: ",i);
			if(length(G->listAdjacency[i])!=0) printList(out,G->listAdjacency[i]);
			fprintf(out,"\n");
		}
	}
}