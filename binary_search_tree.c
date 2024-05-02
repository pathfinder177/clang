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

static void tree_rotate_left(Tree*, int);
static void tree_rotate_right(Tree*, int);

static struct Node* tree_search_parent(Tree*, struct Node*);
static struct Node* tree_search_last_right_vertice(struct Node*);

void tree_dfs_traverse(struct Node*);
void tree_bfs_traverse(struct Node*);
void tree_print(struct Node*);

static void tree_rotate_left(Tree* self, int value) {
    if(self->root->data == value && self->root->r_node) {
        struct Node* new_subtree_root = self->root->r_node;

        self->root->r_node = new_subtree_root->l_node;
        new_subtree_root->l_node = self->root;
        self->root = new_subtree_root;
    }
    else {
        struct Node* parent = self->root;
        struct Node* ex_subtree_root = NULL;
        struct Node* new_subtree_root = NULL;

        while(parent) {
            if (parent->l_node && parent->l_node->data == value) {
                ex_subtree_root = parent->l_node;

                if(ex_subtree_root->r_node) {
                    new_subtree_root = ex_subtree_root->r_node;

                    parent->l_node = new_subtree_root;
                    ex_subtree_root->r_node = new_subtree_root->l_node;
                    new_subtree_root->l_node = ex_subtree_root;
                }

                break;
            }
            if (parent->r_node && parent->r_node->data == value) {
                ex_subtree_root = parent->r_node;

                if(ex_subtree_root->r_node) {
                    new_subtree_root = ex_subtree_root->r_node;

                    parent->r_node = new_subtree_root;
                    ex_subtree_root->r_node = new_subtree_root->l_node;
                    new_subtree_root->l_node = ex_subtree_root;
                }

                break;
            }

            if(parent->data < value) {
                parent = parent->l_node;
            }
            else {
                parent = parent->r_node;
            }
        }
    }
}

static void tree_rotate_right(Tree* self, int value) {

    if(self->root->data == value && self->root->l_node) {
        struct Node* new_subtree_root = self->root->l_node;

        self->root->l_node = new_subtree_root->r_node;
        new_subtree_root->r_node = self->root;
        self->root = new_subtree_root;
    }

    else {
        struct Node* parent = self->root;
        struct Node* ex_subtree_root = NULL;
        struct Node* new_subtree_root = NULL;

        while(parent) {
            if (parent->l_node && parent->l_node->data == value) {
                ex_subtree_root = parent->l_node;

                if(ex_subtree_root->l_node) {
                    new_subtree_root = ex_subtree_root->l_node;

                    parent->l_node = new_subtree_root;
                    ex_subtree_root->l_node = new_subtree_root->r_node;
                    new_subtree_root->r_node = ex_subtree_root;
                }

                break;
            }
            if (parent->r_node && parent->r_node->data == value) {
                ex_subtree_root = parent->r_node;

                if(ex_subtree_root->l_node) {
                    new_subtree_root = ex_subtree_root->l_node;

                    parent->r_node = new_subtree_root; //5(r)->7
                    ex_subtree_root->l_node = new_subtree_root->r_node; //8(l)->N
                    new_subtree_root->r_node = ex_subtree_root; //7(r)->8
                }

                break;
            }

            if(parent->data < value) {
                parent = parent->l_node;
            }
            else {
                parent = parent->r_node;
            }
        }
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

bool tree_erase_node(Tree* self, int value) {
    /*
    node has left and right:
        left has no right child: replace with left, true
        left has right child:
            find last_right_vertice:
                l_r_v has no left child:
                    replace with l_r_v
                l_r_v has left child:
                    replaces l_r_v with left child
                    replaces node with l_r_v

    */

   struct Node* root = self->root;

   //check if root is leaf
    if ((root) && root->l_node == NULL && root->r_node == NULL) {
        if (root->data == value) {
            self->root = NULL;
            free(root);

            return true;
        }
    }

    //if root has left and right
    // if((root) && (root->l_node && root->r_node)) {
    //     if(root->data == value) {
    //         if(root->l_node->r_node) {
    //             ;
    //         }
    //         else {
    //             self->root = root->l_node;
    //             free(root);

    //             return true;
    //         }
    //     }
    //     else {
    //         Tree subtree = tree_create();

    //         if(root->data > value) {
    //             subtree.root = root->l_node;
    //             return tree_erase_node(&subtree, value);
    //         }
    //         else if(root->data < value) {
    //             subtree.root = root->l_node;
    //             return tree_erase_node(&subtree, value);
    //         }
    //     }
    // }

    //if root has only left
    else if((root) && (root->l_node && root->r_node == NULL)) {
        if(root->data == value) {
            self->root = root->l_node;
            free(root);

            return true;
        }
        else if(root->l_node->data == value) {
            struct Node* old_left = root->l_node;

            if(old_left->r_node) {
                old_left->l_node->r_node = old_left->r_node;
            }
            root->l_node = old_left->l_node;

            free(old_left);

            return true;
        }
        else {
            Tree subtree = tree_create();

            if(root->data > value && root->l_node) {
                subtree.root = root->l_node;

                return tree_erase_node(&subtree, value);
            }
        }
    }

    //if root has only right
    else if((root) && (root->r_node && root->l_node == NULL)) {
        if(root->data == value) {
            self->root = root->r_node;
            free(root);

            return true;
        }
        else if(root->r_node->data == value) {
            struct Node* old_right = root->r_node;

            if(old_right->r_node) {
                old_right->l_node->r_node = old_right->r_node;
            }
            root->r_node = old_right->l_node;

            free(old_right);

            return true;
        }
        else {
            Tree subtree = tree_create();

            if(root->data < value && root->l_node) {
                subtree.root = root->l_node;

                return tree_erase_node(&subtree, value);
            }
        }
    }

    // else if((root) && root->l_node && root->r_node) {
    //     ;
    // }

    return false;
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

int main() {
    //    10
    //   /  \
    //  5    15
    // / \  / \
//    3   7 12 18
//   / \
//  1   4
    // int tree_values[] = {10,5,3,7,1,4,15,12,18}; //full
    // int tree_values[] = {10,5,3,1,4}; //left
    int tree_values[] = {10,15,12,18}; //right
    Tree tree = tree_create();

    //FIXME make as test function to provide filled tree
    for (int i = 0; i<(sizeof(tree_values)/sizeof(int)); i++) {
        tree_insert_node(&tree.root, tree_values[i]);
    }

    // struct Node* found_node = tree_find(tree.root, 3); FIXME
    // struct Node* parent_found_node = tree_find_parent(tree.root, 4);

    bool is_erased = tree_erase_node(&tree, 15);

    // tree_print(tree.root);
    // tree_dfs_traverse(tree.root);
    // tree_bfs_traverse(tree.root);

    tree_free(tree.root);

    return 0;
}
