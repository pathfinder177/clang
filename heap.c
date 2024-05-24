//Binary MAX heap implementation based on regular queue
#include "heap.h"

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