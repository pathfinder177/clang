#include "priority_queue.h"

int main() {
    int p_queue_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18};

    Heap p_queue = p_queue_create();

    int i;
    for(i=0; i < (sizeof(p_queue_values)/sizeof(p_queue_values[0])); i++) {
        heap_push(&p_queue, p_queue_values[i]);
    }

    //[18, 14, 15, 9, 12, 13, 1, 4, 5, 7, 10, 3, 8]
    p_queue_print(&p_queue);

    int peek_val = p_queue_peek(&p_queue);

    //18
    int pop_val1 = p_queue_pop(&p_queue);
    //[15, 14, 13, 9, 12, 8, 1, 4, 5, 7, 10, 3]
    p_queue_print(&p_queue);

    //15
    int pop_val2 = p_queue_pop(&p_queue);
    //[14, 12, 13, 9, 7, 8, 1, 4, 5, 3, 10]
    p_queue_print(&p_queue);

    //14
    int pop_val3 = p_queue_pop(&p_queue);
    //[13, 12, 10, 9, 7, 8, 1, 4, 5, 3]
    p_queue_print(&p_queue);

    p_queue_free(&p_queue);
}