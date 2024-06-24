#include <stdio.h>
#include <stdlib.h>

#define HEAP_MAX_SIZE 100

/*
pq based on min binary heap, e.g. 10,20,50,30,40,60,70
pq and heap keeps arrays where element is array[2] = [priority, key]
*/

typedef struct {
    int *array;
    int size;
} Heap;

Heap* heap_create(int *, int);
void heap_free(Heap *);

void heap_push(Heap *, int);
int heap_peek(Heap *);
int heap_pop(Heap *);
void heap_print(Heap *);

static void heap_realloc(Heap *);
static void heap_pop_order(Heap *self);
static void heap_heapify(Heap *);

void heap_print(Heap* self) {
    for(int i = 0; i < self->size ; i++) {
        printf("%d ", self->array[i]);
    }
    printf("\n");
}

int heap_peek(Heap *self) {
    return self->array[0];
}

static void heap_pop_order(Heap *self) {
    int heap_size = self->size;
    int* heap_values = self->array;

    int i, index, left, right, smallest, tmp;

    for(i = 0; i <= (heap_size - 1) / 2; i++) {
        index = i;

        while(1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            smallest = index;

            if (left < heap_size && heap_values[left] < heap_values[smallest]) {
                smallest = left;
            }

            if (right < heap_size && heap_values[right] < heap_values[smallest]) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            tmp = heap_values[index];
            heap_values[index] = heap_values[smallest];
            heap_values[smallest] = tmp;

            index = smallest;

        }
    }
}

int heap_pop(Heap *self) {
    int popped_val = self->array[0];
    self->array[0] = self->array[self->size-1];
    self->size--;

    heap_pop_order(self);

    return popped_val;
}

// static void heap_realloc(Heap *self) {
//     int *tmp = (int *)realloc(self->array, 10 * sizeof(int)); //FIXME

//     if (tmp == NULL) {
//         fprintf(stderr, "Reallocation to increase size failed\n");
//         abort();
//     }

//     self->array = tmp;
// }

void heap_push(Heap *self, int value) {
    // heap_realloc(self); //FIXME

    //push
    // self->size++;
    self->array[(self->size)-1] = value; //FIXME

    heap_print(self); //FIXME
    heap_heapify(self);
}

void heap_heapify(Heap *self) {
    int heap_size = self->size;
    int* heap_values = self->array;

    int i, index, left, right, smallest, tmp;

    // Start from the last non-leaf node to compare it to it's child(ren) and move upwards
    for (i = (heap_size - 1) / 2; i >= 0; i--) {
        index = i;
        printf("index val = %d\n", heap_values[index]);

        while (1) {
            left = 2 * index + 1;
            right = 2 * index + 2;
            //suppose that current element is the smallest between parent node value and left/right child
            smallest = index;

            printf("smallest val = %d\n", heap_values[smallest]);

            // Compare with left child
            if (left < heap_size && heap_values[left] < heap_values[smallest]) {
                smallest = left;
            }

            // Compare with right child: if smaller than left child than replace the left child
            if (right < heap_size && heap_values[right] < heap_values[smallest]) {
                smallest = right;
            }

            printf("smallest val = %d\n", heap_values[smallest]);

            //smallest is parent: at this iteration step heap property is restored
            if (smallest == index) {
                break;
            }
            //the smallest is not the parent, swap index(current element) and smallest
            tmp = heap_values[index];
            heap_values[index] = heap_values[smallest];
            heap_values[smallest] = tmp;

            index = smallest;  // Move down: there may be elements smaller than swapped value
        }
    }
}

Heap* heap_create(int* heap_values, int size) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));

    heap->size = size;
    heap->array = (int*) malloc(heap->size * sizeof(int));

    for(int i = 0; i <= heap->size; i++) {
        heap->array[i] = heap_values[i];
    }

    return heap;
}

int main() {
    int heap_values[] = {3,9,2,1,4,5};
    int size = sizeof(heap_values)/sizeof(heap_values[0]);

    Heap *heap = heap_create(heap_values, size);
    heap_heapify(heap);

    heap_print(heap);

    heap_push(heap, 0);

    heap_print(heap);

    int popped_val = heap_pop(heap);

    heap_print(heap);

     return 0;
}