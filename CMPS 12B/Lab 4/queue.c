//Ryan Coley
//1332490
//rjcoley
//CMPS12B
//11/07/14
//queue.c
//queue object java class equivilant
#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"

#define MAXSIZE 100

int tests_run = 0; // keep track of number of unit tests run

typedef enum q_status {
    /* Enumerated status codes for queue operations */
    q_success = 0,
    q_failure
} q_status;

/**** Private variables for queue ****/
int intItems=-1;
int intFront = 0;
int intBack = 0;
int intQueue[MAXSIZE];


/**** Functions on queues ****/

q_status q_init(void) {
    /* Initialize the queue */
    intItems=-1;
    intFront = 0;
    intBack = 0;
    return q_success;
}

q_status q_insert(int value) {
    /* Insert an item into back of queue
    
       Returns q_success on success.*/
       
    if(intItems < 100){
     intQueue[intBack] = value;
     intItems++;
     intBack++;
     if(intBack == 100){
          intBack = 0;
     }
     return q_success;
    }
    return q_failure;
}

q_status q_remove(int *value) {
    /* Remove item from front of queue

       Stores item at front of queue into pointer
       given as argument. Removes item from queue.

       Returns qSuccess on success.
    */
    if(intItems > -1 && value != NULL){
     *value = intQueue[intFront];
     intFront++;
     if(intFront == 100){
          intFront = 0;
     }
     intItems--;
     return q_success;
    }
    return q_failure;
}

q_status q_peek(int *value) {
    /* Peek at item at front of queue

       Stores item at front of queue into pointer
       given as argument. Queue is not altered.

       Returns qSuccess on success.
    */
    if(intItems > -1 && value != NULL){
     *value = intQueue[intFront];
     return q_success;
    }
    return q_failure;
}

q_status q_destroy(void) {
    /* Destroy the queue */
    if(intItems >-1){
    for(int i = 0;i<100;i++){
        intQueue[i] = '\0';
    }
    intItems = -1;
    intFront = 0;
    intBack = 0;
    }
    return q_success;
}

int q_is_empty(void){
     if(intItems == -1){
          return 1;
     }
     return 0;
}

/**** Unit tests ****/

char * test_lifecycle(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_lifecycle\n");
    return NULL;
}

char * test_one_insert(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(7) == q_success);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_one_insert\n");
    return NULL;
}

char * test_one_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(16) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 16);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_one_insert_remove\n");
    return NULL;
}

char * test_two_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 91);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_two_insert_remove\n");
    return NULL;
}

char * test_multi_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(8) == q_success);
    mu_assert("insert", q_insert(91) == q_success);
    for(int i = 0; i < 1000; i++) {
        mu_assert("insert", q_insert(8) == q_success);
        mu_assert("insert", q_insert(91) == q_success);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 8);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == 91);
    }
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("value", v == 8);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_multi_insert_remove\n");
    return NULL;
}

char * test_indexed_insert_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_indexed_insert_remove\n");
    return NULL;
}

char * test_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("remove", q_remove(&v) == q_failure);
    printf("Finished test_too_many_remove\n");
    return NULL;
}

char * test_insert_too_many_remove(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 30; i++) {
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
    }
    mu_assert("remove", q_remove(&v) == q_failure);
    printf("Finished test_insert_too_many_remove\n");
    return NULL;
}

char * test_peek(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_peek\n");
    return NULL;
}

char * test_peek_two(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("peek", q_peek(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_peek_two\n");
    return NULL;
}

char * test_peek_deep(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    for(int i = 0; i < 30; i++) {
        mu_assert("insert", q_insert(i) == q_success);
    }
    for(int i = 0; i < 1000; i++) {
        mu_assert("peek", q_peek(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("remove", q_remove(&v) == q_success);
        mu_assert("value", v == i);
        mu_assert("insert", q_insert(30 + i) == q_success);
    }
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_peek_deep\n");
    return NULL;
}

char * test_peek_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    printf("Finished test_peek_empty\n");
    return NULL;
}

char * test_peek_two_empty(void) {
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(42) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("remove", q_remove(&v) == q_success);
    mu_assert("peek", q_peek(&v) == q_failure);
    printf("Finished test_peek_two_empty\n");
    return NULL;
}

char * test_remove_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_remove(NULL) == q_failure);
    printf("Finished test_remove_null\n");
    return NULL;
}

char * test_peek_null(void) {
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("peek", q_peek(NULL) == q_failure);
    printf("Finished test_peek_null\n");
    return NULL;
}

char * test_three_insert_remove(void){
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(24) == q_success);
    mu_assert("insert", q_insert(30) == q_success);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 24);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 30);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_three_insert_remove\n");
    return NULL;
    
}

char * test_true_empty(void){
    int v;
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(24) == q_success);
    mu_assert("insert", q_insert(30) == q_success);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 18);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 24);
    mu_assert("insert", q_remove(&v) == q_success);
    mu_assert("value", v == 30);
    mu_assert("emptyness", q_is_empty() == 1);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_true_empty\n");
    return NULL;
}

char * test_false_empty(void){
    mu_assert("init", q_init() == q_success);
    mu_assert("insert", q_insert(18) == q_success);
    mu_assert("insert", q_insert(24) == q_success);
    mu_assert("insert", q_insert(30) == q_success);
    mu_assert("emptyness", q_is_empty() == 0);
    mu_assert("destroy", q_destroy() == q_success);
    printf("Finished test_false_empty\n");
    return NULL;
}
     

char * all_tests(void) {
    /* Run all unit tests */
    mu_run_test(test_lifecycle);
    mu_run_test(test_one_insert);
    mu_run_test(test_one_insert_remove);
    mu_run_test(test_two_insert_remove);
    mu_run_test(test_multi_insert_remove);
    mu_run_test(test_indexed_insert_remove);
    mu_run_test(test_too_many_remove);
    mu_run_test(test_insert_too_many_remove);
    mu_run_test(test_peek);
    mu_run_test(test_peek_two);
    mu_run_test(test_peek_deep);
    mu_run_test(test_peek_empty);
    mu_run_test(test_peek_two_empty);
    mu_run_test(test_remove_null);
    mu_run_test(test_peek_null);
   mu_run_test(test_three_insert_remove);
   mu_run_test(test_true_empty);
   mu_run_test(test_false_empty);
    return NULL;
}

/**** Main unit test runner ****/

int main(int argc, char *argv[]) {
    printf("Queue Module unit tests\n");
    char *result = all_tests();
    if (result) {
        printf("FAILURE at %s\n", result);
    } else {
        printf("ALL TESTS PASS\n");
    }
    printf("Tests run: %d\n", tests_run);
    return EXIT_SUCCESS;
}
