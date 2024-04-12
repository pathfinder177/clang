#include <stdio.h>
#include <stdlib.h>
#include "bfs_queue.h"

struct Node {
    int data;
    struct Node* l_node;
    struct Node* r_node;
};


typedef struct {
    struct Node* root;
} Tree;


Tree tree_create(); // returns empty binary tree
struct Node* tree_create_node(int);
void tree_free(Tree* self); // deallocates tree

int tree_get_node_val(struct Node*);
void tree_set_node_val(struct Node*, int);

struct Node* tree_get_left_child(struct Node*);
void tree_insert_left(struct Node*, int);

struct Node* tree_get_right_child(struct Node*);
void tree_insert_right(struct Node*, int);


//actually not the part of the interface, part of learning
void tree_inorder_traverse(struct Node*);
void tree_preorder_traverse(struct Node*);
void tree_postorder_traverse(struct Node*);

struct Node* tree_dfs_search(struct Node*, int);
struct Node* tree_bfs_search(struct Node*, int);

struct Node* tree_bfs_search(struct Node* self, int value) {
    enQueue(self);

    while(items) {
        struct Node *n = deQueue();

        if(n->data==value) {
            return n;
        }
        if(n->l_node) {
            enQueue(n->l_node);
        }
        if(n->r_node) {
            enQueue(n->r_node);
        }
    }

}

struct Node* tree_dfs_search(struct Node* self, int value) {
    /*
    base case: value is found OR not
    rec. step:
        1. explore current node
            if found: return value
        2. if value is not in current node
            a. recursive exploration of left subtree
                if found: return value
        3. if value is not in left subtree
            a. recursive exploration of right subtree
                if found: return value

        if not found: return NULL
    final state:
        1. value is returned. algorithm is stopped.
        2. NULL is returned. all nodes are visited
    */

   struct Node* n = NULL;

    if(self->data == value) {
        n = self;
        return n;
    }

    if(self->l_node) {
        n = tree_dfs_search(self->l_node, value);
        if((n) && n->data == value) {
            return n;
        }
    }

    if(self->r_node) {
        n = tree_dfs_search(self->r_node, value);
        if((n) && n->data == value) {
            return n;
        }
    }

    return NULL;
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

struct Node* tree_create_node(int value) {
    struct Node* new_node;

    if ((new_node = (struct Node*)malloc(sizeof(struct Node))) == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = value;
    new_node->l_node = NULL;
    new_node->r_node = NULL;

    return new_node;
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

    //use DFS
    //backtracking problem
    // struct Node* n = tree_dfs_search(tree.root, 7);
    struct Node* n = tree_bfs_search(tree.root, 7);

    // 4,2,5,1,6,3,7,
    // tree_inorder_traverse(tree.root);

    // 1,2,4,5,3,6,7
    // tree_preorder_traverse(tree.root);

    // 4,5,2,6,7,3,1
    // tree_postorder_traverse(tree.root);

    return 0;
}
