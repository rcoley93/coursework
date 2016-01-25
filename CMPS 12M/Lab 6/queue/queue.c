/*Ryan Coley
  1332490
  11/24/14
  rjcoley
  lab6
  queue.c
  defines a psuedo class for a queue data structure
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf(stderr, __VA_ARGS__);

/* Internal implementation definitions */
struct queue_node {
     queue_item_t item;
     struct queue_node *link;
};

typedef struct queue_node queue_node;

struct queue {
     queue_node *front;
     queue_node *rear;
};

/* Functions */

queue *queue_new(void) {
     struct queue *q = malloc(sizeof(struct queue));
     q->front = NULL;
     q->rear = NULL;
     return q;
}

void queue_free(queue *this) {
     assert(queue_isempty(this));
     free(this);
}

void queue_insert(queue *this, queue_item_t item) {
     struct queue_node *qn = malloc(sizeof(struct queue_node));
     assert(qn!=NULL);
     qn->item = item;
     if(this->rear ==NULL){          
          this->front = qn;
          this->rear = qn;
     }else{
          this->rear->link = qn;
          this->rear = qn;
     }
}

queue_item_t queue_remove(queue *this) {
     assert(!queue_isempty(this));
     int in = 0;
     if(this->front == this->rear){
          in = 1;
     }
     struct queue_node *qn = this->front;
     queue_item_t i = this->front->item;
     this->front = this->front->link;
     free(qn);
     
     if(in==1){
          this->front = NULL;
     }
     return i;
}

bool queue_isempty(queue *this) {
     return this->front == NULL;
}
