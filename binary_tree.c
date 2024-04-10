/*
ADT implementation:
https://runestone.academy/ns/books/published/pythonds3/Trees/Implementation.html
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* l_node;
    struct Node* r_node;
};

typedef struct {
    struct Node* root;
} Tree;

Tree tree_create(); // returns empty binary tree
// void tree_free(Tree* self); deallocates tree
void tree_inorder_traverse(struct Node*);
void tree_preorder_traverse(struct Node*);
void tree_postorder_traverse(struct Node*);
struct Node* tree_create_node(int);

struct Node* tree_create_node(int value) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

  newNode->data = value;
  newNode->l_node = NULL;
  newNode->r_node = NULL;

  return newNode;
}

void tree_postorder_traverse(struct Node* self) {

    if (self->l_node) {
        tree_postorder_traverse(self->l_node);
    }

    if (self->r_node) {
        tree_postorder_traverse(self->r_node);
    }

    printf("%d\n", self->data);
}

void tree_preorder_traverse(struct Node* self) {
    printf("%d\n", self->data);

    if (self->l_node) {
        tree_preorder_traverse(self->l_node);
    }

    if (self->r_node) {
        tree_preorder_traverse(self->r_node);
    }

}

void tree_inorder_traverse(struct Node* self) {
    /*
    base case:
        all nodes in subtree are visited
    rec. step:
        if l_node
            rec(l_node)
        else
            print data
        print data
        if r_node
            rec(r_node)
        else
            print data
    final state:
        all nodes are visited
    */

    if (self->l_node) {
        tree_inorder_traverse(self->l_node);
    }

    printf("%d\n", self->data);

    if (self->r_node) {
        tree_inorder_traverse(self->r_node);
    }
}

Tree tree_create() {
    Tree tree;
    tree.root = NULL;

    return tree;
}

int main() {
    Tree tree = tree_create();

    struct Node node_6 = {6, NULL, NULL};
    struct Node node_7 = {7, NULL, NULL};
    struct Node node_3 = {3, &node_6, &node_7};

    struct Node node_4 = {4, NULL, NULL};
    struct Node node_5 = {5, NULL, NULL};
    struct Node node_2 = {2, &node_4, &node_5};

    struct Node node_1 = {1, &node_2, &node_3};

    tree.root = &node_1;

    // 4,2,5,1,6,3,7,
    // tree_inorder_traverse(tree.root);

    // 1,2,4,5,3,6,7
    // tree_preorder_traverse(tree.root);

    // 4,5,2,6,7,3,1
    // tree_postorder_traverse(tree.root);

    return 0;
}
