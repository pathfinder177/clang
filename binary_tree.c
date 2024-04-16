#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "bfs_queue.h"

typedef struct {
    struct Node* root;
} Tree;


Tree tree_create(); // returns empty binary tree
// void tree_free(Tree* self); // deallocates tree

struct Node* tree_create_node(int);
void tree_delete_node(Tree*, struct Node*);

int tree_get_node_val(struct Node*);
void tree_set_node_val(struct Node*, int);

struct Node* tree_get_left_child(struct Node*);
struct Node* tree_get_right_child(struct Node*);

void tree_insert_left(struct Node*, int);
void tree_insert_right(struct Node*, int);

//actually not the part of the interface, part of learning
void tree_inorder_traverse(struct Node*);
void tree_preorder_traverse(struct Node*);
void tree_postorder_traverse(struct Node*);

struct Node* tree_search_parent(Tree*, struct Node*);
struct Node* tree_dfs_search(struct Node*, int); //inorder traversal
struct Node* tree_bfs_search(struct Node*, int);

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

struct Node* tree_bfs_search(struct Node* self, int value) {
    struct Node *n = NULL;
    enQueue(self);

    while((n = deQueue()) != NULL) {

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
    return n;
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

void tree_delete_node(Tree* tree, struct Node* self) {
    //if duplicate is encountered: delete first found node
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
        free((void*) self);
    }
    else if(parent->r_node && parent->l_node == NULL) {
        if(tree->root == self) {
            tree->root = self->r_node;
        }
        else {
            parent->r_node = self->r_node;
        }
        free((void*) self);
    }
    // else {
        // if (self->l_node->r_node) {
            //find last right vertice(where r_node==NULL)
            //if l_r_v->left
                //l_r_v=l_r_v->left;
                //self=l_r_v;
                //free(self);
            //else
            //self=l_r_v;
            //free(self);
        // }
        // else {
            ////change self in node_before by l_node
        // }
    // }
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

    // root -> 1 -> 9(l) -> 2(l) -> 4(l), 5(r)
    //           -> 0(r) -> 3(l) -> 6(l), 7(r)
    //left subtree
    struct Node* node_9 = tree_dfs_search(tree.root, 9);
    tree_insert_left(node_9, 2);
    struct Node* node_2 = tree_dfs_search(tree.root, 2);
    tree_insert_left(node_2, 4);
    tree_insert_right(node_2, 5);
    //right subtree
    struct Node* node_0 = tree_dfs_search(tree.root, 0);
    tree_insert_right(node_0, 3);
    struct Node* node_3 = tree_dfs_search(tree.root, 3);
    tree_insert_left(node_3, 6);
    tree_insert_right(node_3, 7);

    //n_parent_2 = node_9
    struct Node* n_parent_2 = tree_search_parent(&tree, node_2);
    //n_parent_3 = node_0
    struct Node* n_parent_3 = tree_search_parent(&tree, node_3);

    // root -> 1 -> 9(l) -> 4(l), 5(r)
    //           -> 0(r) -> 6(l), 7(r)
    // tree_delete_node(&tree, node_2);
    // tree_delete_node(&tree, node_3);

    //
    // tree_inorder_traverse(tree.root);

    //
    // tree_preorder_traverse(tree.root);

    //
    // tree_postorder_traverse(tree.root);

    // struct Node* n = tree_bfs_search(tree.root, 7);


    return 0;
}
