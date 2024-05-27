#include "heap.h"

int main() {

    // int heap_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18};
    int heap_values[] = {3,5,7,8,9,10};

    //[18, 14, 15, 9, 12, 13, 1, 4, 5, 7, 10, 3, 8]
    // heap_order(heap_values, sizeof(heap_values) / sizeof(heap_values[0]));

    Heap heap = heap_create();

    int i;
    for(i=0; i < (sizeof(heap_values)/sizeof(heap_values[0])); i++) {
        heap_push(&heap, heap_values[i]);
    }

    //[18, 14, 15, 9, 12, 13, 1, 4, 5, 7, 10, 3, 8]
    heap_print(&heap);

    //18
    int peek_value = heap_peek(&heap);

    //18
    int pop_value_1 = heap_pop(&heap);
    //14
    int pop_value_2 = heap_pop(&heap);
    //15
    int pop_value_3 = heap_pop(&heap);

     //[9, 12, 13, 1, 4, 5, 7, 10, 3, 8]
    heap_print(&heap);

    heap_free(&heap);

    return 0;
}
