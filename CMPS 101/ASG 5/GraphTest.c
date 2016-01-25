//Ryan Coley
//rjcoley
//pa5
//GraphTest.c
//Graph.c ADT test

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc,char* argv[]){
	//undirected graph test
	//testing new graph
	Graph graphUndirected = newGraph(7);
	//testing add edge
	addEdge(graphUndirected,1,2);
	addEdge(graphUndirected,1,7);
	addEdge(graphUndirected,2,3);
	addEdge(graphUndirected,2,6);
	addEdge(graphUndirected,2,5);
	addEdge(graphUndirected,3,4);
	addEdge(graphUndirected,3,5);
	addEdge(graphUndirected,3,6);
	addEdge(graphUndirected,4,5);
	addEdge(graphUndirected,5,6);
	//testing bfs on undirected graph
	DFS(graphUndirected);
	//testing print graph
	printGraph(stdout,graphUndirected);
	//testing get order, get finish and get discover
	for(int i=1;i<getOrder(graphUndirected);i++){
		printf("%d: disc=%d, fin=%d\n",i,getDiscover(graphUndirected,i),getFinish(graphUndirected,i));
	}
	//testing transpose
	Graph temp = transpose(graphUndirected);
	//testing print graph
	printGraph(stdout,temp);
	//testing copy
	Graph temp2 = copyGraph(temp);
	addEdge(temp2,1, 3);
	printf("\n");
	printGraph(stdout,temp);
	printf("\n");
	printGraph(stdout,temp2);
	freeGraph(&temp);
	freeGraph(&graphUndirected);
	
	
	Graph graphDirected = newGraph(7);
	//testing add arc
	addArc(graphDirected,1,2);
	addArc(graphDirected,1,7);
	addArc(graphDirected,2,3);
	addArc(graphDirected,3,4);
	addArc(graphDirected,4,5);
	addArc(graphDirected,5,3);
	addArc(graphDirected,5,2);
	addArc(graphDirected,6,5);
	addArc(graphDirected,6,2);
	addArc(graphDirected,6,3);
	printf("\n\nDirected Graph Test\n");
	printGraph(stdout,graphDirected);
	printf("\n");
	//testing bfs on directed graph
	DFS(graphDirected);
	for(int i=1;i<8;i++){
		printf("%d: disc=%d, fin=%d\n",i,getDiscover(graphUndirected,i),getFinish(graphUndirected,i));
	}
	//testing get size
	printf("The size of the undirected graph is %d.\n\n",getSize(graphDirected));
	//testing free graph
	freeGraph(&graphDirected);
	
	/*graph test from examples*/
	 int i, n=8;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
	
	
	return 0;
}