#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "bfs_queue.h"

typedef struct {
    struct Node* root;
} Tree;


Tree tree_create(); // returns empty binary tree
void tree_free(struct Node*); // deallocates tree
void tree_print(struct Node*);

struct Node* tree_create_node(int);
void tree_delete_node(Tree*, struct Node*);

int tree_get_node_val(struct Node*);
void tree_set_node_val(struct Node*, int);

struct Node* tree_get_left_child(struct Node*);
struct Node* tree_get_right_child(struct Node*);

void tree_insert_left(struct Node*, int);
void tree_insert_right(struct Node*, int);

static struct Node* tree_search_parent(Tree*, struct Node*);
static struct Node* tree_search_last_right_vertice(struct Node*);

void tree_dfs_traverse(struct Node*);
void tree_bfs_traverse(struct Node*);

int tree_get_node_val(struct Node* self) {
    if (self->data) {
        return self->data;
    }
    else {
        printf("Node has no data.\n");
        exit(EXIT_FAILURE);
    }
}

void tree_set_node_val(struct Node* self, int value) {
    if (self) {
        self->data = value;
    }
    else {
        printf("Node pointer is NULL\n");
        exit(EXIT_FAILURE);
    }
}

struct Node* tree_get_left_child(struct Node* self) {
    if (self->l_node) {
        return self->l_node;
    }
    else {
        return NULL;
    }
}

struct Node* tree_get_right_child(struct Node* self) {
    if (self->r_node) {
        return self->r_node;
    }
    else {
        return NULL;
    }
}

void tree_insert_left(struct Node* self, int value) {
    struct Node* new_node = tree_create_node(value);

    if(self->l_node) {
        new_node->l_node=self->l_node;
    }
    self->l_node=new_node;
}

void tree_insert_right(struct Node* self, int value) {
    struct Node* new_node = tree_create_node(value);

    if(self->r_node) {
        new_node->r_node=self->r_node;
    }

    self->r_node=new_node;
}

void tree_bfs_traverse(struct Node* self) {
    enQueue(self);

    while((self = deQueue()) != NULL) {

        if(self->data) {
            printf("Node data: %d\n", self->data);
        }
        if(self->l_node) {
            enQueue(self->l_node);
            printf("Left node in queue:\n");
        }
        if(self->r_node) {
            printf("Right node in queue:\n");
            enQueue(self->r_node);
        }
    }
}

void tree_dfs_traverse(struct Node* self) {
    if (self->l_node) {
        printf("Left node:\n");
        tree_dfs_traverse(self->l_node);
    }
    if (self->data) {
        printf("Node data: %d\n", self->data);
    }
    if (self->r_node) {
        printf("Right node:\n");
        tree_dfs_traverse(self->r_node);
    }
}


void tree_delete_node(Tree* tree, struct Node* self) {
    struct Node* parent = tree_search_parent(tree, self);

    if(self->l_node == NULL && self->r_node == NULL) {
        free((void*) self);
    }
    else if(parent->l_node && parent->r_node == NULL) {
        if(tree->root == self) {
            tree->root = self->l_node;
        }
        else {
            parent->l_node = self->l_node;
        }
    }
    else if(parent->r_node && parent->l_node == NULL) {
        if(tree->root == self) {
            tree->root = self->r_node;
        }
        else {
            parent->r_node = self->r_node;
        }
    }
    else {
        if (self->l_node->r_node) {
            // find last right vertice(where node->r_node==NULL)
            struct Node* last_right_vertice = tree_search_last_right_vertice(self->l_node);

            if(last_right_vertice->l_node) {
                self->l_node->r_node = last_right_vertice->l_node;

                if(self->r_node) {
                    last_right_vertice->r_node = self->r_node;
                }
                else {
                    last_right_vertice->l_node = NULL;
                }
            }

            last_right_vertice->l_node = self->l_node;
            parent->l_node = last_right_vertice;

            if(tree->root==self) {
                tree->root = last_right_vertice;
            }
        }
        else {
            if(tree->root==self && tree->root->r_node) {
                self->l_node->r_node = self->r_node;
                tree->root = tree->root->l_node;
            }
            else if(parent->r_node)
            {
                self->l_node->r_node = self->r_node;
                parent->l_node = self->l_node;
            }
        }
    }
    free((void*) self);
}

struct Node* tree_search_parent(Tree* tree, struct Node* self) {
    struct Node* parent = NULL;

    if(tree->root == self) {
        parent = self;
        return parent;
    }
    else if(tree->root->l_node && tree->root->l_node == self) {
        parent = tree->root;
        return parent;
    }
    else if(tree->root->r_node && tree->root->r_node == self) {
        parent = tree->root;
        return parent;
    }
    else {
        if(tree->root->l_node) {
            Tree left_tree = tree_create();
            left_tree.root = tree->root->l_node;
            parent = tree_search_parent(&left_tree, self);

            if((parent) && parent->l_node == self) {
                return parent;
            }
        }

        if(tree->root->r_node) {
            Tree right_tree = tree_create();
            right_tree.root = tree->root->r_node;
            parent = tree_search_parent(&right_tree, self);

            if((parent) && parent->r_node == self) {
                return parent;
            }
        }

        return parent;
    }
}

struct Node* tree_search_last_right_vertice(struct Node* left_child) {
    struct Node* l_r_v = left_child;

    while(l_r_v->r_node) {
        l_r_v = l_r_v->r_node;
    }

    return l_r_v;
}

//print tree using preorder way
void tree_print(struct Node* self) {
    if (self) {
        tree_dfs_traverse(self);
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

void tree_free(struct Node* self) {
    if(self->l_node) {
        tree_free(self->l_node);
    }
    if(self->r_node) {
        tree_free(self->r_node);
    }

    free(self);
}

Tree tree_create() {
    Tree tree;
    tree.root = NULL;

    return tree;
}

int main() {
    // Unordered Binary Tree
    Tree tree = tree_create();

    //Have doubts where is the best place to create root node
    tree.root = tree_create_node(9);

    //node_val = 9
    int node_val = tree_get_node_val(tree.root);

    tree_set_node_val(tree.root, 1);
    //node_val = 1
    int node_val_after_set = tree_get_node_val(tree.root);

    // root -> 1 -> 9
    tree_insert_left(tree.root, 9);

    // root -> 1 -> 9
    //           -> 0
    tree_insert_right(tree.root, 0);

    //l_node = node_9
    struct Node* l_node = tree_get_left_child(tree.root);
    //r_node = node_0
    struct Node* r_node = tree_get_right_child(tree.root);

    // root -> 9 -> 0(r)
    tree_delete_node(&tree, tree.root);

    // root -> 1 -> 9(l) -> 2(l) -> 4(l), 5(r) -> 8(l)
    //           -> 0(r) -> 3(l) -> 6(l), 7(r)
    //left subtree
    tree_insert_left(l_node, 2);
    tree_insert_left(l_node->l_node, 4);
    tree_insert_right(l_node->l_node, 5);
    tree_insert_left(l_node->l_node->r_node, 8);

    //right subtree
    tree_insert_left(r_node, 3);
    tree_insert_left(r_node->l_node, 6);
    tree_insert_right(r_node->l_node, 7);

    // root -> 5 -> 2(l) -> 4(l), 8(r)
    //           -> 0(r) -> 3(r) -> 6(l), 7(r)
    tree_delete_node(&tree, l_node);

    tree_print(tree.root);

    // tree_bfs_traverse(tree.root);

    tree_free(tree.root);

    return 0;
}
