//Ryan Coley
//12/12/14
//rjcoley
//1332490
//lab8
//heap.c
//basic heap data structure

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/** Heap type **/

/* Heaps contain size information which is updated as elements are
   inserted and deleted. maxSize is the size of the array, which is
   allocated dynamically when the heap is created.
*/
struct heap {
    int size;
    int maxSize;
    int *array;
};
typedef struct heap heap;

/** Helper functions **/

int parent(int x) {
    if(x%2==0) return (x-2)/2;
    return (x - 1) / 2;
}

int lchild(int x) {
    return 2 * x + 1;
}

int rchild(int x) {
    return 2 * x + 2;
}

/** Heap operations **/

/*  Print heap for debugging */
void printHeap(heap *aHeap) {
    assert(aHeap != NULL);
    for(int i = 0; i < aHeap->size; i++) {
        printf("%d ", aHeap->array[i]);
    }
    printf("\n");
}

/*  Create new heap dynamically
    Returns pointer to new heap object.
*/
heap *newHeap(int maxSize) {
    assert(maxSize > 0);
    heap *tmp = malloc(sizeof(heap));
    tmp->size = 0;
    tmp->maxSize = maxSize;
    tmp->array = malloc(sizeof(int) * tmp->maxSize);
    return tmp;
}

/*  Delete previously created heap
*/
void deleteHeap(heap *aHeap) {
    assert(aHeap != NULL);
    assert(aHeap->array != NULL);
    free(aHeap->array);
    free(aHeap);
}

/*  Check if heap is full */
bool isFullHeap(heap *aHeap) {
    assert(aHeap != NULL);
    if(aHeap->size == aHeap->maxSize) return 1;
    return 0;
}

/*  Check if heap is empty */
bool isEmptyHeap(heap *aHeap) {
    assert(aHeap != NULL);
    if(aHeap->size == 0) return 1;
    return 0;
}

/*  Insert number into heap
    Unspecified behavior if heap is full before insert
*/

void insertHeap(heap *aHeap, int value) {
    assert(aHeap != NULL);
    assert(aHeap->size < aHeap->maxSize);
    aHeap->size++;
    aHeap->array[aHeap->size-1] = value;
    
    int position = aHeap->size-1;
    while(true){
	if(aHeap->array[position] > aHeap->array[parent(position)] && position != 0){
		int intParentValue = aHeap->array[parent(position)];
		int intChildValue = aHeap->array[position];
		if(intParentValue == 0 && position == 0) break;
		aHeap->array[parent(position)] = intChildValue;
		aHeap->array[position] = intParentValue;
		position = parent(position);
	}else break;
    }
}

/*  Remove number from heap
    Unspecified behavior if heap is empty
*/
int removeHeap(heap *aHeap) {
    assert(aHeap != NULL);
    assert(aHeap->size > 0);
    aHeap->size--;
    int retVal = aHeap->array[0];
    aHeap->array[0] = aHeap->array[aHeap->size];
    // Trickle down
    int position = 0;
    while (true) {
        int left = lchild(position);
        int right = rchild(position);
        int largest = position;
        if (left < aHeap->size && aHeap->array[left] > aHeap->array[largest]) {
            largest = left;
        }
        if (right < aHeap->size && aHeap->array[right] > aHeap->array[largest]) {
            largest = right;
        }
        if (largest == position) {
            break;
        } else {
            int tmp = aHeap->array[position];
            aHeap->array[position] = aHeap->array[largest];
            aHeap->array[largest] = tmp;
            position = largest;
        }
    }
    return retVal;
}

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc < 2) {
        printf("Wrong arguments\n");
        return EXIT_FAILURE;
    }
    int maxnum = atoi(argv[1]);
    char *filename = argv[2];

    // Create new heap
    heap *theHeap = newHeap(maxnum);

    // Read lines of file
    FILE *fp = fopen(filename, "rt");
    while(!feof(fp)) {
        char buffer[256];
        fgets(buffer, 256, fp);
        if (feof(fp)) break;
        int value = atoi(buffer);
        insertHeap(theHeap, value);
        if (isFullHeap(theHeap)) {
            removeHeap(theHeap);
        }
    }

    // Show contents
    while(!isEmptyHeap(theHeap)) {
        int value = removeHeap(theHeap);
        printf("%d\n", value);
    }
    
    // Delete heap
    deleteHeap(theHeap);

    return EXIT_SUCCESS;
}
