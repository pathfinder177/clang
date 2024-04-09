/*
ADT implementation:
https://runestone.academy/ns/books/published/pythonds3/Trees/Implementation.html
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* l_node;
    struct Node* r_node;
};

typedef struct {
    struct Node* root;
} Tree;

Tree tree_create(); // returns empty binary tree

Tree tree_create() {
    Tree tree;
    tree.root = NULL;

    return tree;
}

int main() {
    Tree tree = tree_create();

    return 0;
}
