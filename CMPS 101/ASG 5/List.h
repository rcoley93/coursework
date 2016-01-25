//Ryan Coley
//rjcoley
//pa5
//List.h
//Header file for List.c


#include<stdio.h>

//define list node
typedef struct ListObj* List;

//constructer and deconstructer
List newList(void);
void freeList(List* pL);

//access functions
int length(List L);
int getIndex(List L);
int front(List L);
int back(List L);
int getElement(List L);
int equals(List A, List B);

//manipulation procedures
void clear(List L);
void moveTo(List L, int i);
void movePrev(List L);
void moveNext(List L);
void prepend(List L,int i);
void append(List L,int i);
void insertBefore(List L,int i);
void insertAfter(List L,int i);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//other operations
void printList(FILE* out, List L);
List copyList(List L);
