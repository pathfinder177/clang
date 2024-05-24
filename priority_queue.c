//Implementation based on max binary heap
#include "priority_queue.h"

Heap p_queue_create() {
    Heap self = heap_create();
    return self;
};

void p_queue_free(Heap* self) {
    heap_free(self);
}

void p_queue_print(Heap* self) {
    heap_print(self);
}

void p_queue_push(Heap* self, int value) {
    heap_push(self, value);
}

int p_queue_peek(Heap* self) {
    return heap_peek(self);
}

int p_queue_pop(Heap* self) {
    if (self->rear < 0) {
        fprintf(stderr, "Heap is empty\n");
        abort();
    }

    int top_elem = self->array[self->front];
    int last_elem = self->array[self->rear];

    self->array[self->front] = last_elem;
    self->array[self->rear] = top_elem;
    self->array[self->rear--] = 0;

    p_queue_pop_order(self->array, self->rear);

    return top_elem;

}

static void p_queue_pop_order(int* p_queue_values, int p_queue_size) {
    int parent = 0;
    int l_child, r_child, swap_child, tmp;

    while(1) {
        l_child = 2 * parent + 1;
        r_child = 2 * parent + 2;

        if(l_child >= p_queue_size) {
            l_child = parent;
        }
        if(r_child >= p_queue_size) {
            r_child = parent;
        }

        if(p_queue_values[parent] >= p_queue_values[l_child] && p_queue_values[parent] >= p_queue_values[r_child]) {
            break;
        }

        if (p_queue_values[l_child] > p_queue_values[r_child]) {
            swap_child = l_child;
        }
        else {
            swap_child = r_child;
        }

        tmp = p_queue_values[parent];
        p_queue_values[parent] = p_queue_values[swap_child];
        p_queue_values[swap_child] = tmp;

        parent = swap_child;

    }
}