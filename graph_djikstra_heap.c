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
        heap_print(self);
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

    // // Allocate memory for each inner array FIXME
    // for (int i = 0; i < HEAP_INIT_SIZE; i++) {
    //     p_queue[i] = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int));

    //     if (p_queue[i] == NULL) {
    //         perror("Failed to allocate memory for heap inner array");
    //         abort();
    //     }
    // }

    heap->p_queue = p_queue;
    heap->size = 0;

    return heap;
}

int main() {
    Heap *heap = heap_create();

    //emulate djikstra's interaction with heap
    //start vertice
    int* start = (int *) malloc(P_QUEUE_ELEMENT_SIZE * sizeof(int)); //TODO make macro
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

    heap_print(heap);

    //step 4: pop the closest vertice, if identical - by number of key
    int *popped_closest = heap_pop(heap);

    // step 5: repeat step 2. Continue while heap is not empty

    heap_print(heap);

    return 0;
}