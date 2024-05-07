#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "node.h"
#include "bfs_queue.h"

typedef struct {
    struct Node* root;
} Tree;


Tree tree_create(); // returns empty binary tree
void tree_free(struct Node*); // deallocates tree

void tree_insert_node(struct Node**, int);
static struct Node* tree_create_node(int);

struct Node* tree_find(struct Node*, int);
static struct Node* tree_find_parent(struct Node*, int);

bool tree_erase_node(Tree*, int);
static struct Node* tree_swap_nodes(Tree*);

static void tree_rotate_left(Tree*, struct Node**);
static void tree_rotate_right(Tree*, struct Node**);

// static struct Node* tree_search_parent(Tree*, struct Node*);
static struct Node* tree_find_last_right_vertice(struct Node*);

void tree_dfs_traverse(struct Node*);
void tree_bfs_traverse(struct Node*);
void tree_print(struct Node*);

static void tree_rotate_left(Tree* self, struct Node** old_left) {
    if((*old_left)->r_node) {
        struct Node* p_new_root = tree_create_node((*old_left)->r_node->data);

        p_new_root->r_node = (*old_left)->r_node->r_node;
        (*old_left)->r_node = (*old_left)->r_node->l_node;
        p_new_root->l_node = (*old_left);

        (*old_left) = p_new_root;
    }
    else {
        printf("No right child: node can not be left rotated\n");
        abort();
    }
}

static void tree_rotate_right(Tree* self, struct Node** old_right) {
    if((*old_right)->l_node) {
        struct Node* p_new_root = tree_create_node((*old_right)->l_node->data); //5

        p_new_root->l_node = (*old_right)->l_node->l_node;
        (*old_right)->l_node = (*old_right)->l_node->r_node;
        p_new_root->r_node = (*old_right); //5->10

        (*old_right) = p_new_root;
    }
    else {
        printf("No left child: node can not be right rotated\n");
        abort();
    }
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


// struct Node* tree_search_parent(Tree* tree, struct Node* self) {
//     struct Node* parent = NULL;

//     if(tree->root == self) {
//         parent = self;
//         return parent;
//     }
//     else if(tree->root->l_node && tree->root->l_node == self) {
//         parent = tree->root;
//         return parent;
//     }
//     else if(tree->root->r_node && tree->root->r_node == self) {
//         parent = tree->root;
//         return parent;
//     }
//     else {
//         if(tree->root->l_node) {
//             Tree left_tree = tree_create();
//             left_tree.root = tree->root->l_node;
//             parent = tree_search_parent(&left_tree, self);

//             if((parent) && parent->l_node == self) {
//                 return parent;
//             }
//         }

//         if(tree->root->r_node) {
//             Tree right_tree = tree_create();
//             right_tree.root = tree->root->r_node;
//             parent = tree_search_parent(&right_tree, self);

//             if((parent) && parent->r_node == self) {
//                 return parent;
//             }
//         }

//         return parent;
//     }
// }

struct Node* tree_find_last_right_vertice(struct Node* left_child) {
    struct Node* l_r_v = left_child->r_node;

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

static struct Node* tree_find_parent(struct Node* self, int value) {
    if ((self) && value < self->data && self->l_node) {
        if(self->l_node->data == value) {
            return self;
        }
        return tree_find_parent(self->l_node, value);
    }
    if ((self) && value > self->data && self->r_node) {
        if(self->r_node->data == value) {
            return self;
        }
        return tree_find_parent(self->r_node, value);
    }

    return NULL;
}

struct Node* tree_find(struct Node* self, int value) {
    if (self) {
        if(self->data == value) {
            return self;
        }
        if(value < self->data) {
            return tree_find(self->l_node, value);
        }
        else if(value > self->data) {
            return tree_find(self->r_node, value);
        }
    }

    return NULL;
}


void tree_insert_node(struct Node** self, int value) {
    if(*self == NULL) {
       *self = tree_create_node(value);
    }

    if(value < (*self)->data) {
        tree_insert_node(&((*self)->l_node), value);
    }
    else if(value > (*self)->data) {
        tree_insert_node(&((*self)->r_node), value);
    }
}

static struct Node* tree_create_node(int value) {
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
    if(self) {
        if(self->l_node) {
            tree_free(self->l_node);
        }
        if(self->r_node) {
            tree_free(self->r_node);
        }
        free(self);
    }
}

Tree tree_create() {
    Tree tree;
    tree.root = NULL;

    return tree;
}

// /*
// node has left and right:
//     left has no right child: replace with left, true
//     left has right child:
//         find last_right_vertice:
//             l_r_v has no left child:
//                 replace with l_r_v
//             l_r_v has left child:
//                 replaces l_r_v with left child
//                 replaces node with l_r_v
// */

bool tree_erase_node(Tree* self, int value) {
    struct Node* root = self->root;

    if(root == NULL) {
        return false;
    }

    else if(root->l_node == NULL && root->r_node == NULL) {
        self->root = NULL;
        free(root);
    }

    else if(root->data == value) {
        struct Node* new_root = tree_swap_nodes(self);
    }

    else if(root->l_node && value < root->data) {
        Tree l_subtree = tree_create();
        l_subtree.root = root->l_node;

        if(root->l_node->data == value) {
            struct Node* new_left_node = tree_swap_nodes(&l_subtree);
            free(self->root->l_node);
            self->root->l_node = new_left_node;

            return true;
        }

        return tree_erase_node(&l_subtree, value);
    }

    else if(root->r_node && value > root->data) {
        Tree r_subtree = tree_create();
        r_subtree.root = root->r_node;

        if(root->r_node->data == value) {
            struct Node* new_right_node = tree_swap_nodes(&r_subtree);
            free(self->root->r_node);
            self->root->r_node = new_right_node;

            return true;
        }


        return tree_erase_node(&r_subtree, value);
    }
}

static struct Node* tree_swap_nodes(Tree* self) {
    struct Node* root = self->root;

    //left
    if(root->r_node == NULL) {
        self->root = root->l_node;
    }
    //right
    else if(root->l_node == NULL) {
        self->root = root->r_node;
    }
    //left and right
    else if(root->l_node && root->r_node) {
        if(root->l_node->r_node) {
            struct Node* last_right_vertice = tree_find_last_right_vertice(root->l_node);

            if(last_right_vertice->l_node) {
                struct Node* l_r_v_left_node = last_right_vertice->l_node;

                last_right_vertice->l_node = root->l_node;
                last_right_vertice->r_node = root->r_node;
                last_right_vertice->l_node->r_node = l_r_v_left_node;

                self->root = last_right_vertice;
            }
            else {
                last_right_vertice->l_node = root->l_node;
                last_right_vertice->r_node = root->r_node;
                last_right_vertice->l_node->r_node = NULL;

                self->root = last_right_vertice;
            }
        }
        else {
            root->l_node->r_node = root->r_node;
            self->root = root->l_node;
        }
    }

    return self->root;
}

int main() {
    //    10
    //   /     \
    //  5       15
    // /  \     / \
//    3    9   12 18
//   /\   /     \
//  1 4  7      14
//       \      /
//       8     13

    int tree_values[] = {10,5,3,9,7,8,1,4,15,12,14,13,18};
    // int tree_values[] = {10,5,15,3,1,4,9}; //last data
    Tree tree = tree_create();

    //FIXME make as test function to provide filled tree
    for (int i = 0; i<(sizeof(tree_values)/sizeof(tree_values[0])); i++) {
        tree_insert_node(&tree.root, tree_values[i]);
    }

    struct Node* node_5 = tree_find(tree.root, 5);

    //    5
    //   /       \
//      3        10
//     / \       /   \
//    1  4      9    15
//            /    / \
//           7    12 18
//           \    /
//           8  14
//              /
//             13
    tree_rotate_left(&tree, &node_5);
    //after right rotation the state as depicted in the beginning of main
    tree_rotate_right(&tree, &node_5);
    // struct Node* parent_found_node = tree_find_parent(tree.root, 4);

    // bool is_erased;
    // is_erased = tree_erase_node(&tree, 10);
    // is_erased = tree_erase_node(&tree, 5);
    // is_erased = tree_erase_node(&tree, 15);

    // tree_print(tree.root);
    // tree_dfs_traverse(tree.root);
    // tree_bfs_traverse(tree.root);

    tree_free(tree.root);

    return 0;
}
