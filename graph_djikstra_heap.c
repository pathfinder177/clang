#include "graph_djikstra_heap.h"

void heap_print(Heap* self) {
    for(int i = 0; i < self->size; i++) {
        printf("%d ", self->p_queue[i][0]);
        printf("%d\n", self->p_queue[i][1]);
    }
}

int* heap_peek(Heap *self) {
    return self->p_queue[0];
}

int* heap_pop(Heap *self) {
    if (self->size <=0) {
        perror("Heap is empty");
        abort();
    }

    int* popped_arr = self->p_queue[0];
    self->p_queue[0] = self->p_queue[self->size - 1];
    self->size--;

    if (self->size <= 0) {
        return popped_arr;
    }

    int heap_size = self->size;
    int** heap_values = self->p_queue;

    int index, left, right, smallest;
    index = 0;

    //As only one node may be move down, the only cycle is sufficient
    //downsift
    while(1) {
        // heap_print(self);
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap_size && heap_values[left][0] < heap_values[smallest][0]) {
            smallest = left;
        }

        if (right < heap_size && heap_values[right][0] < heap_values[smallest][0]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        int *tmp = heap_values[index];
        heap_values[index] = heap_values[smallest];
        heap_values[smallest] = tmp;

        index = smallest;
        }

    return popped_arr;
}

static void heap_realloc(Heap *self) {
    int new_heap_size = self->size * 2;

    if(new_heap_size > 100) {
        new_heap_size = HEAP_MAX_SIZE;
    }

    int **tmp = realloc(self->p_queue, new_heap_size * sizeof(int *));

    if (tmp == NULL) {
        perror("Reallocation to increase size failed\n");
        abort();
    }

    self->p_queue = tmp;

}

void heap_push(Heap *self, int* priority_key_arr) {
    if(self->size >= HEAP_MAX_SIZE) {
        perror("Heap is full\n");
        abort();
    }

    if((self->size > 0) && (self->size % HEAP_INIT_SIZE == 0)) {
        heap_realloc(self);
    }

    self->size++;
    self->p_queue[self->size-1] = priority_key_arr;

    int heap_size = self->size;
    int** heap_values = self->p_queue;

    int index, left, right, smallest;
    index = (heap_size - 2) / 2;

    //As only one node may be move down, the only cycle is sufficient
    //upsift
    while(1) {
        // heap_print(self);
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < heap_size && heap_values[left][0] < heap_values[smallest][0]) {
            smallest = left;
        }

        if (right < heap_size && heap_values[right][0] < heap_values[smallest][0]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        int *tmp = heap_values[index];
        heap_values[index] = heap_values[smallest];
        heap_values[smallest] = tmp;

        index = smallest;
    }

}

static void heap_heapify(Heap *self) {
    int heap_size = self->size;
    int** heap_values = self->p_queue;

    int i, index, left, right, smallest;

    // Start from the last non-leaf node to compare it to it's child(ren) and move upwards
    // upsift
    for (i = (heap_size - 1) / 2; i >= 0; i--) {
        index = i;
        // printf("parent index distance val = %d\n", heap_values[index][0]);

        while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            //suppose that current element is the smallest between parent node value and left/right child
            smallest = index;

            // Compare with left child
            if (left < heap_size && heap_values[left][0] < heap_values[smallest][0]) {
                smallest = left;
            }

            // Compare with right child: if smaller than left child than replace the left child
            if (right < heap_size && heap_values[right][0] < heap_values[smallest][0]) {
                smallest = right;
            }

            // printf("smallest distance val = %d\n", heap_values[smallest][0]);

            //smallest is parent: at this iteration step heap property is restored
            if (smallest == index) {
                break;
            }
            //the smallest is not the parent, swap index pointer and smallest
            int *tmp = heap_values[index];
            heap_values[index] = heap_values[smallest];
            heap_values[smallest] = tmp;

            index = smallest;  // Move down: there may be elements smaller than swapped value
        }
    }
}

Heap* heap_create() {
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    if(heap == NULL) {
        perror("Failed to allocate memory for heap");
        abort();
    }

    //Allocate memory in heap for array keeps 10 pointers to int arrays
    int **p_queue = malloc(HEAP_INIT_SIZE * sizeof(int *));
    if(p_queue == NULL) {
        perror("Failed to allocate memory for heap external array");
        abort();
    }

    heap->p_queue = p_queue;
    heap->size = 0;

    return heap;
}