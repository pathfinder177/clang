#include <stdio.h>
#include <stdlib.h>

#define INIT_HEAP_SIZE 10
#define HEAP_SIZE_CHANGE 5
#define MAX_HEAP_SIZE 100

typedef struct {
    int front, rear;
    int *array;
} Heap;

Heap heap_create();
void heap_free(Heap*);

void heap_push(Heap*, int);
int heap_peek(Heap*);
int heap_pop(Heap*);
void heap_print(Heap*);

static void heap_realloc(Heap*);
static void heap_order(int*, int);