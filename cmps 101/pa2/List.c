//Ryan Coley
//rjcoley
//pa2
//List.c
//List datastruture implementation

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// structs-------------------------------------------------------------

//define node object
typedef struct NodeObj{
	int intData;
	struct NodeObj* nodePrevious;
	struct NodeObj* nodeNext;
} NodeObj;

//define node type
typedef NodeObj* Node;

//define list object
typedef struct ListObj{
	Node nodeFront;
	Node nodeBack;
	Node nodeCurrent;
	int intLength;
	int intIndex;
} ListObj;

// constructors-deconstructors-----------------------------------------

//create a new node
Node newNode(int intData){
	Node nodeN = malloc(sizeof(NodeObj));
	nodeN->intData = intData;
	nodeN->nodePrevious = NULL;
	nodeN->nodeNext = NULL;
	return nodeN;
}

//free the memory asscociated with a node
void freeNode(Node* pN){
	if(pN!=NULL && *pN!=NULL){
		free(*pN);
		*pN = NULL;
	}
}

//create a new list
List newList(void){
	List listL;
	listL = malloc(sizeof(ListObj));
	listL->nodeFront = listL->nodeBack = NULL;
	listL->intLength = 0;
	listL->intIndex = -1;
	return listL;
}

//free the memory asscociated with a list
void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		if(length(*pL)!=0){
			clear(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

//access functions --------------------------------------------------

//return the length of the node
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on NULL List reference!\n");
		exit(1);
	}
	return(L->intLength);
}

//return the index of the list
int getIndex(List L){
	if(L == NULL){
		printf("List Error: calling getIndex() on NULL List reference!\n");
		exit(1);
	}
	return(L->intIndex);
}

//return the value of the front of the list
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List reference!\n");
		exit(1);
	}else if(length(L) > 0){
		return L->nodeFront->intData;
	}else{
		printf("List Error: calling front() on empty List!\n");
		exit(1);
	}
}

//return the value of the back of the list
int back(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List reference!\n");
		exit(1);
	}else if(length(L) > 0){
		return L->nodeBack->intData;
	}else{
		printf("List Error: calling back() on empty List!\n");
		exit(1);
	}
}

//return the value of the current position of the list
int getElement(List L){
	if(L == NULL){
		printf("List Error: calling getElement() on NULL List reference!\n");
		exit(1);
	}else if(length(L) > 0 && getIndex(L) >=0){
		return L->nodeCurrent->intData;
	}else if(length(L) == 0){
		printf("List Error: calling getElement() on empty List!\n");
		exit(1);
	}else{
		printf("List Error: calling getElement() on undefined index!\n");
		exit(1);
	}
}

//determines whether the two lists are the same
int equals(List A, List B){
	if(A == NULL || B == NULL){
		printf("List Error: calling equals() on NULL List reference!\n");
		exit(1);
	}else if(length(A) != length(B)){
		return 0;
	}else{
		int intTempIndexA = getIndex(A);
		int intTempIndexB = getIndex(B);
		int i;
		for(i=0;i<length(A);i++){
			moveTo(A,i);
			moveTo(B,i);
			if(getElement(A)!= getElement(B)){
				return 0;
			}
		}
		moveTo(A,intTempIndexA);
		moveTo(B,intTempIndexB);
		return 1;
	}
}

// manipulation functions -------------------------------------------

//clears the list
void clear(List L){
	if(L == NULL){
		printf("List Error: calling clear() on NULL List reference!\n");
		exit(1);
	}else if(length(L) > 0){
		int i;
		for(i = length(L)-1;i>=0;i--){
			moveTo(L,i);
			delete(L);
		}
	}
}

//move to a specific place in the list
void moveTo(List L, int i){
	if(L == NULL){
		printf("List Error: calling moveTo() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling moveTo() on empty List!\n");
		exit(1);
	}else if(0<=i && i<=length(L)-1){
		L->intIndex = i;
		L->nodeCurrent = L->nodeFront;
		int j;
		for(j = 0;j<i;j++){
			L->nodeCurrent = L->nodeCurrent->nodeNext;
		}
	}else{
		L->intIndex = -1;
		L->nodeCurrent = NULL;
	}
}

//move to the previous node
void movePrev(List L){
	if(L == NULL){
		printf("List Error: calling movePrev() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling movePrev() on empty List!\n");
		exit(1);
	}else if(0 < getIndex(L) && getIndex(L) <= length(L)-1) moveTo(L,getIndex(L)-1);
	else moveTo(L,-1);
}

//move to the next node
void moveNext(List L){
	if(L == NULL){
		printf("List Error: calling moveNext() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling moveNext() on empty List!\n");
		exit(1);
	}else if(0<=getIndex(L) && getIndex(L)<length(L)-1) moveTo(L,getIndex(L)+1);
	else moveTo(L,-1);
}

//add node to begining of the list
void prepend(List L,int data){
		Node nodeNew = newNode(data);
		if(length(L) == 0){
			nodeNew->nodeNext = NULL;
			L->nodeBack = nodeNew;
			L->nodeFront = nodeNew;
		}else{
			nodeNew->nodeNext = L->nodeFront;
			L->nodeFront->nodePrevious = nodeNew;
			L->nodeFront = nodeNew;
		}
		if(getIndex(L) != -1){
				L->intIndex++;
		}
		L->intLength++;
}

//add a node to the end of the list
void append(List L, int data){
	Node nodeNew = newNode(data);
		if(length(L) != 0){
			nodeNew->nodePrevious = L->nodeBack;
			L->nodeBack->nodeNext = nodeNew;
			L->nodeBack = nodeNew;
		}else{
			nodeNew->nodePrevious = NULL;
			L->nodeBack = nodeNew;
			L->nodeFront = nodeNew;
		}
		L->intLength++;
}

//add a node to before the current element
void insertBefore(List L,int data){
	if(L == NULL){
		printf("List Error: calling insertBefore() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling insertBefore() on empty List!\n");
		exit(1);
	}else if(getIndex(L) == -1){
		printf("List Error: calling insertBefore() on undefined index!\n");
		exit(1);
	}else{
		Node nodeNew = newNode(data);
		
		Node nodePrev = L->nodeCurrent->nodePrevious;
		Node nodeNext = L->nodeCurrent;
		
		nodePrev->nodeNext = nodeNew;
		nodeNext->nodePrevious = nodeNew;
		
		nodeNew->nodePrevious = nodePrev;
		nodeNew->nodeNext = nodeNext;
		
		L->intIndex++;
	}
	L->intLength++;
}

//add a node to after the current element
void insertAfter(List L, int data){
	if(L == NULL){
		printf("List Error: calling insertAfter() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling insertAfter() on empty List!\n");
		exit(1);
	}else if(getIndex(L) == -1){
		printf("List Error: calling insertAfter() on undefined index!\n");
		exit(1);
	}else{
		Node nodeNew = newNode(data);
		
		Node nodePrev = L->nodeCurrent;
		Node nodeNext = L->nodeCurrent->nodeNext;
		
		nodePrev->nodeNext = nodeNew;
		nodeNext->nodePrevious = nodeNew;
		
		nodeNew->nodePrevious = nodePrev;
		nodeNew->nodeNext = nodeNext;
	}
	L->intLength++;
}

//delete the front element
void deleteFront(List L){
	if(L == NULL){
		printf("List Error: calling deleteFront() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling deleteFront() on empty List!\n");
		exit(1);
	}else{
		int intTempIndex = getIndex(L);
		moveTo(L,0);
		delete(L);
		moveTo(L,intTempIndex-1);
	}
}

//delete the rear element
void deleteBack(List L){
	if(L == NULL){
		printf("List Error: calling deleteBack() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling deleteBack() on empty List!\n");
		exit(1);
	}else{
		int intTempIndex = getIndex(L);
		moveTo(L,length(L)-1);
		delete(L);
		moveTo(L,intTempIndex);
	}
}

//delete the current element
void delete(List L){
	if(L == NULL){
		printf("List Error: calling delete() on NULL List reference!\n");
		exit(1);
	}else if(length(L) == 0){
		printf("List Error: calling delete() on empty List!\n");
		exit(1);
	}else if(getIndex(L)==-1){
		printf("List Error: calling delete() on undefined index!\n");
		exit(1);
	}else{
		Node nodeDelete = L->nodeCurrent;
		Node nodePrev = L->nodeCurrent->nodePrevious;
		Node nodeNext = L->nodeCurrent->nodeNext;
		int intMaxNode = length(L)-1;
		if(length(L)>1){
			if(getIndex(L) == 0){
				nodeNext->nodePrevious = NULL;
				L->nodeFront = nodeNext;
			}else if(getIndex(L) == intMaxNode){
				nodePrev->nodeNext = NULL;
				L->nodeBack = nodePrev;
			}else{
				nodePrev->nodeNext = nodeNext;
				nodeNext->nodePrevious = nodePrev;
			}
		}else{
			L->nodeFront = L->nodeBack = L->nodeCurrent = NULL;
			L->intIndex = -1;
		}
		L->intLength--;
		freeNode(&nodeDelete);
	}
}

// other functions --------------------------------------------------

//prints the list to file
void printList(FILE* out, List L){
	if(L == NULL){
		printf("List Error: calling printList() on NULL List reference!\n");
		exit(1);
	}else if(out == NULL){
		printf("List Error: calling printList() on NULL FILE reference!\n");
		exit(1);
	}else{
		int i,intTempIndex = getIndex(L);
		for(i=0;i<length(L);i++){
			moveTo(L,i);
			fprintf(out,"%d ",getElement(L));
		}
		moveTo(L,intTempIndex);
	}
}

//makes a copy of the list
List copyList(List L){
	List listNew = newList();
	int i,intTempIndex = getIndex(L);
	for(i=0;i<length(L);i++){
		moveTo(L,i);
		append(listNew,getElement(L));
	}
	moveTo(L,intTempIndex);
	return listNew;
}






