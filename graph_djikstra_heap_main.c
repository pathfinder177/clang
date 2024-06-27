#include "graph_djikstra_heap.h"

int main() {
    Heap *heap = heap_create();

    //emulate djikstra's interaction with heap
    //start vertice
    int* start = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int));
    start[0] = 0; //priority(distance)
    start[1] = 0; //key

    //step 1: push start vertice
    heap_push(heap, start);

    //step 2: pop vertice
    int *popped_start = heap_pop(heap);

    //step 3: get start neighbors and push them to heap
    int* v2 = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int));
    v2[0] = 4;
    v2[1] = 2;
    heap_push(heap, v2);

    int* v1 = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int));
    v1[0] = 3;
    v1[1] = 1;
    heap_push(heap, v1);

    int* v3 = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int)); //FIXME
    v3[0] = 2;
    v3[1] = 3;
    heap_push(heap, v3);

    // heap_print(heap);

    //step 4: pop the closest vertice, if identical - by number of key
    int *popped_closest = heap_pop(heap);

    // step 5: repeat step 2. Continue while heap is not empty

    heap_print(heap);

    return 0;
}