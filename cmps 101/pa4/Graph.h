//Ryan Coley
//rjcoley
//pa4
//Graph.h
//Header file for Graph.c

#include<stdio.h>
#include "List.h"
#define NIL -3
#define INF -2

//define graph object
typedef struct GraphObj* Graph;

//constructor and deconstructor
Graph newGraph(int n);
void freeGraph(Graph* pG);

//access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G,int u);
int getDist(Graph G,int u);
void getPath(List L, Graph G, int u);

//manipulation funcitons
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int V);
void BFS(Graph G, int s);

//other operations
void printGraph(FILE* out, Graph G);