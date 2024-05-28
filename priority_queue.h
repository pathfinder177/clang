//Implementation based on max binary heap
#include "heap.h"

Heap p_queue_create();
void p_queue_free(Heap*);

void p_queue_print(Heap*);

void p_queue_push(Heap*, int);
int p_queue_peek(Heap*);
int p_queue_pop(Heap*);
static void p_queue_pop_order(int*, int);
