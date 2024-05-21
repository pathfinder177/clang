//Binary MAX heap implementation
#include <stdio.h>
#include <stdlib.h>


#define INIT_HEAP_SIZE 10
#define HEAP_SIZE_CHANGE 5
#define MAX_HEAP_SIZE 100

typedef struct {
    int size;
    int last_elem_pos;
    int *array;
} Heap;

Heap heap_create();
void heap_free(Heap*);
static void heap_realloc(Heap*);

void heap_push(Heap*, int);

void heap_print(Heap*);

void heap_print(Heap* heap) {
    int i;
    if(heap->last_elem_pos < 0) {
        fprintf(stderr, "Can not prinf, heap is empty\n");
        abort();
    }

    for(i = 0; i <= heap->last_elem_pos; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

Heap heap_create() {
    Heap heap;

    heap.array = (int *)calloc(heap.size, sizeof(int)); //to init with 0

    if (heap.array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        abort();
    }

    heap.size = INIT_HEAP_SIZE;
    heap.last_elem_pos = -1;

    return heap;
}

void heap_free(Heap* heap) {
    free(heap->array);

    heap->array = NULL; //avoid undefined behavior of dangling pointer
    heap->last_elem_pos = -1;
    heap->size = INIT_HEAP_SIZE;
}

static void heap_realloc(Heap* heap) {
    if (heap->size >= MAX_HEAP_SIZE) {
        fprintf(stderr, "Heap exceeds max size\n");
        abort();
    }

    int new_heap_size = heap->size + HEAP_SIZE_CHANGE;
    int *tmp = (int *)realloc(heap->array, new_heap_size*sizeof(int));

    if (tmp == NULL) {
        fprintf(stderr, "Reallocation to increase size failed\n");
        abort();
    }

    heap->size = new_heap_size;
    heap->array = tmp;
}

void heap_push(Heap* heap, int value) {
    if(heap->array[0] == 0) { //heap is empty
        heap->array[0] = value;
        heap->last_elem_pos = 0;
    }
    else {
        //TODO check whether heap is full and need additional memory

        int parent = (heap->last_elem_pos - 1) / 2;
        int left_child = 2 * parent + 1;
        int right_child = 2 * parent + 2;

        if(value <= heap->array[parent]) { //insert in the end
            if(heap->array[left_child] == 0) {
                heap->array[left_child] = value;
            }
            else if(heap->array[right_child] == 0) {
                heap->array[right_child] = value;
            }
        }
        else { //swap with parent and keep binary heap properties
            int tmp;

            if(heap->array[left_child] == 0) {
                heap->array[left_child] = heap->array[parent];
            }
            else if(heap->array[right_child] == 0) {
                heap->array[right_child] = heap->array[parent];
            }

            heap->array[parent] = value;

            heap->last_elem_pos++;
        }
    }
}

int main() {

    int heap_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18};

    Heap heap = heap_create();

    int i;
    for(i=0; i < (sizeof(heap_values)/sizeof(heap_values[0])); i++) {
        heap_push(&heap, heap_values[i]);
    }

    heap_free(&heap);

    return 0;
}
