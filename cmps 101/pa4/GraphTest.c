//Ryan Coley
//rjcoley
//pa4
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
	BFS(graphUndirected,7);
	printf("\n\nUndirected Graph Test\n");
	printf("The graph should look like:\n1: 2 7\n2: 1 3 5 6\n3: 2 4 5 6\n4: 3 5\n5: 2 3 4 6\n6: 2 3 5\n7: 1\n\nThe Results:\n");
	//testing print graph
	printGraph(stdout,graphUndirected);
	//testing get source
	printf("BFS(%d) was performed and the following distances and paths should be:\nnode,distance,path\n1,1,7 1\n2,2,7 1 2\n3,3,7 1 2 3\n4,4,7 1 2 3 4\n5,3,7 1 2 5\n6,3,7 1 2 6\n7,0,1\n\n",getSource(graphUndirected));
	printf("The Results:\nnode,distance,path\n");
	//testing get order
	for(int i=1;i<getOrder(graphUndirected);i++){
		List tempList = newList();
		if(getDist(graphUndirected,i) == INF) printf("%d,INFINITY,",i);
		//testing get distance
		else printf("%d,%d,",i,getDist(graphUndirected,i));
		//testing get path/get parent
		getPath(tempList,graphUndirected,i);
		printList(stdout,tempList);
		freeList(&tempList);
		printf("\n");
	}
	//testing make null
	makeNull(graphUndirected);
	BFS(graphUndirected,2);
	printf("\n\nmakeNull was performed\n");
	//testing print graph
	printGraph(stdout,graphUndirected);
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
	BFS(graphDirected,1);
	for(int i=1;i<8;i++){
		List tempList = newList();
		//testing distance on no way to get to node
		if(getDist(graphDirected,i) == INF) printf("%d,INFINITY,No Path Exists",i);
		else {
			printf("%d,%d,",i,getDist(graphDirected,i));
			getPath(tempList,graphDirected,i);
			printList(stdout,tempList);
		}
		freeList(&tempList);
		printf("\n");
	}
	//testing get size
	printf("The size of the undirected graph is %d.\n\n",getSize(graphDirected));
	//testing free graph
	freeGraph(&graphDirected);
	
	/*TEST CLIENT FROM EXAMPLES*/
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveTo(E,0);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = getElement(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);
	
	return 0;
}