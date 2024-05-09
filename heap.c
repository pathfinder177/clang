#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"

//Binary MAX heap implementation

// typedef struct {
    // int values[];
// } Heap;

void heap_make_from_array(int[], int); //fill heap with array's values
bool heap_erase_value_from_array(int[], int, int); //fill heap with array's values

// void heap_push(int[], int);
// int heap_pop(int[]);
// int heap_peek(int[]);

void heap_make_from_array(int heap_values[], int heap_size) {
    int i, index, parent, tmp;

    for(i = 0; i < heap_size; i++) {
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

bool heap_erase_value_from_array(int heap_values[], int heap_size, int value) {
    int i, left_child, right_child, parent, tmp;

    for (i = 0; i < heap_size; i++) {
        if(heap_values[i] == value) {
            parent = i;
            break;
        }
    }

    if (parent < 0 || parent >= heap_size || heap_values[parent] != value) {
        printf("No %d in heap\n", value);
        return false;
    }

    heap_values[parent] = heap_values[heap_size-1];

    left_child = 2 * parent + 1;
    right_child = 2 * parent + 2;

    while(left_child < heap_size - 1) {
        if(heap_values[left_child] < heap_values[parent] && heap_values[right_child] < heap_values[parent]) {
            break;
        }

        if(heap_values[left_child] > heap_values[right_child]) {
            tmp = heap_values[parent];
            heap_values[parent] = heap_values[left_child];
            heap_values[left_child] = tmp;

            parent = left_child;
        }
        else {
            tmp = heap_values[parent];
            heap_values[parent] = heap_values[right_child];
            heap_values[right_child] = tmp;

            parent = right_child;
        }

        left_child = 2 * parent + 1;
        right_child = 2 * parent + 2;
    }

    return true;
}

int main() {

    // int heap_values[] = {15,11,10,7,5,9,2,6,4,3,1,8,12}; //FIXME data from Stevens book

    int heap_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18}; //data from binary_search_tree.c
    int heap_size = (sizeof(heap_values))/(sizeof(heap_values[0]));

    heap_make_from_array(heap_values, heap_size);
    bool is_erased = heap_erase_value_from_array(heap_values, heap_size, 14);

    return 0;
}
