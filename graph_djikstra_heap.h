#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE 100
#define HEAP_INIT_SIZE 10
#define P_QUEUE_ELEMENT_SIZE 2

/*
pq based on min binary heap, e.g. 10,20,50,30,40,60,70
heap keeps array of arrays where each element is int* array[2] = [priority, key]
*/

typedef struct {
    int **p_queue;
    int size;
} Heap;

Heap* heap_create();
void heap_free(Heap *);

void heap_push(Heap *, int *);
int* heap_peek(Heap *);
int* heap_pop(Heap *);
void heap_print(Heap *);

static void heap_realloc(Heap *);
static void heap_heapify(Heap *);