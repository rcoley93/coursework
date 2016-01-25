//Ryan Coley
//rjcoley
//pa5
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
int getParent(Graph G,int u); /* Pre: 1<=u<=n<=getOrder(G)*/
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n<=getOrder(G)*/
int getFinish(Graph G, int u); /* Pre: 1<=u<=n<=getOrder(G)*/

//manipulation funcitons
void addEdge(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void addArc(Graph G, int u, int v); /* Pre: 1<=u<=n, 1<=v<=n */
void DFS(Graph G, List S); /* Pre: getLength(S)==getOrder(G)*/

//other operations
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);