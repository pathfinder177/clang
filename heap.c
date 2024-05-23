//Binary MAX heap implementation
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

void heap_print(Heap* self) {
    int i;
    if (self->rear < 0) {
        fprintf(stderr, "Can not prinf, heap is empty\n");
        abort();
    }

    for(i = self->front; i <= self->rear; i++) {
        printf("%d ", self->array[i]);
    }
    printf("\n");
}

Heap heap_create() {
    Heap self;
    self.front = 0;
    self.rear = -1;

    self.array = (int *)calloc(INIT_HEAP_SIZE, sizeof(int)); //to init with 0

    if (self.array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        abort();
    }

    return self;
}

void heap_free(Heap* self) {
    free(self->array);

    self->array = NULL; //avoid undefined behavior of dangling pointer
    self->front = 0;
    self->rear = -1;
}

static void heap_realloc(Heap* self) {
    int new_heap_size = self->rear + HEAP_SIZE_CHANGE;

    if (new_heap_size > MAX_HEAP_SIZE) {
        fprintf(stderr, "Heap exceeds max size\n");
        abort();
    }

    int *tmp = (int *)realloc(self->array, new_heap_size*sizeof(int));

    if (tmp == NULL) {
        fprintf(stderr, "Reallocation to increase size failed\n");
        abort();
    }

    self->array = tmp;
}

void heap_push(Heap* self, int value) {
        if((self->rear + 1) >= (self->rear + HEAP_SIZE_CHANGE)) {
            fprintf(stdout, "Heap reallocation occurs\n");
            heap_realloc(self);
        }

        self->rear++;
        self->array[self->rear] = value;

        heap_order(self->array, self->rear);
}

static void heap_order(int* heap_values, int heap_size) { //took from Stevens book and analyzed
    int i, index, parent, tmp;

    for(i = 0; i <= heap_size; i++) {
        index = i;

        while (index != 0) {
            parent = (index - 1) / 2;

            if (heap_values[index] <= heap_values[parent]) {
                break;
            }

            tmp = heap_values[index];
            heap_values[index] = heap_values[parent];
            heap_values[parent] = tmp;

            index = parent;
        }
    }
}

int heap_peek(Heap* self) {
    if (self->rear >= 0) {
        return self->array[self->front];
    }

    fprintf(stderr, "Heap is empty\n");
    abort();
}

int heap_pop(Heap* self) {
    if (self->rear >= 0) {
        int top_elem = self->array[self->front];

        self->array[self->front] = 0;
        self->front++;

        return top_elem;
    }

    fprintf(stderr, "Heap is empty\n");
    abort();
}

int main() {

    int heap_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18};

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
