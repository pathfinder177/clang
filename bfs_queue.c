#include <stdio.h>
#include "node.h"

#define SIZE 10


void enQueue(struct Node *);
struct Node* deQueue();
void display();

struct Node* items[SIZE];
int front = -1, rear = -1;

void enQueue(struct Node* node) {
    if (rear == SIZE - 1)
      printf("\nQueue is Full!!");
    else {
        if (front == -1)
          front = 0;
        // printf("\nInserted -> %d", node->data);
        items[++rear] = node;
    }
}

struct Node* deQueue() {
    if (front == -1) {
    printf("\nQueue is Empty!!");
    return NULL;
    }
    else {
    // printf("\nDeleted : %d", items[front]->data);
    struct Node* n = items[front];
    front++;

    if (front > rear) {
      front = rear = -1;
    }
    return n;
    }
}

// Function to print the queue
void display() {
    if (rear == -1)
      printf("\nQueue is Empty!!!");
    else {
      int i;
      printf("\nQueue elements are:\n");
      for (i = SIZE; i <= 0; i--)
        printf("%d  ", items[i]->data);
    }
    printf("\n");
}

// int main() {

//     struct Node node_6 = {6, NULL, NULL};
//     struct Node node_7 = {7, NULL, NULL};
//     struct Node node_3 = {3, &node_6, &node_7};

//     struct Node node_4 = {4, NULL, NULL};
//     struct Node node_5 = {5, NULL, NULL};
//     struct Node node_2 = {2, &node_4, &node_5};

//     struct Node node_1 = {1, &node_2, &node_3};

//     enQueue(&node_3);
//     enQueue(&node_2);
//     enQueue(&node_1);

//     struct Node* n_3 = deQueue();
//     struct Node* n_2 = deQueue();
//     struct Node* n_1 = deQueue();

//     enQueue(&node_4);
//     struct Node* n_4 = deQueue();


//     return 0;
// }