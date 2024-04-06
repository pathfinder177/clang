//ADT implementation: https://runestone.academy/ns/books/published/pythonds3/BasicDS/TheUnorderedListAbstractDataType.html

#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

typedef struct
{
    struct Node* head;
} List;

List list_create(); // returns empty list
void list_free(List* self); // deallocates list
void list_push_front(List* self, int value);
int list_pop_front(List* self);
struct Node* list_find(List* self, int value); // NULL if not found
void list_erase_after(List* self, struct Node* node);
void list_append(List* self, int value);
void list_merge_to_back(List* self, List* other);
// void list_merge_to_front(List* self, List* other);
// void list_splice_after(List* self, struct Node* after, List* other);

void list_append(List* self, int value) {
    struct Node *p_new_node = (struct Node *) malloc(sizeof(struct Node));

    if (p_new_node == NULL) {
        printf("Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }

    p_new_node -> data = value;

    struct Node *p_node_before = self -> head;
    while(p_node_before -> next) {
        p_node_before = p_node_before -> next;
    }

    p_node_before -> next = p_new_node;

}

// void list_merge_to_back(List* self, List* other) {
//     if (self -> head == NULL && other -> head == NULL) {
//         printf("Can not MERGE_TO_BACK: both lists are empty\n");
//         exit(EXIT_FAILURE);
//     }



// }

void list_erase_after(List* self, struct Node* node) {
    if (self -> head == NULL) {
        printf("Can not ERASE_AFTER: list is empty\n");
        exit(EXIT_FAILURE);
    }
    else if(node -> next == NULL) {
        printf("Can not ERASE_AFTER: your node is the last in list\n");
        exit(EXIT_FAILURE);
    }

    struct Node *p_node_to_erase = node -> next;
    node -> next = p_node_to_erase -> next;

    free((void *) p_node_to_erase);

}

struct Node* list_find(List* self, int value) {
    if (self -> head == NULL) {
        printf("Can not FIND: list is empty\n");
        exit(EXIT_FAILURE);
    }

    struct Node *p_node = self -> head;

    while (p_node) {
        if (p_node -> data == value) {
            return p_node;
        }
        p_node = p_node -> next;
    }

    return NULL;
}

int list_pop_front(List* self) {
    int head_data;
    struct Node *p_node_after_head;

    if (self -> head == NULL) {
        printf("Can not POP: list is empty\n");
        exit(EXIT_FAILURE);
    }

    head_data = self -> head -> data;
    p_node_after_head = self -> head -> next;

    free((void *) self -> head);
    self -> head = p_node_after_head;

    return head_data;
}


//Delete only Node(s) from memory
void list_free(List* self) {

    struct Node *p_node, *p_node_next;
    p_node = p_node_next = self -> head;

    while (p_node) {
        p_node_next = p_node -> next;
        free((void *) p_node);
        p_node = p_node_next;
    }
}

void list_push_front(List* self, int value) {
    struct Node *p_new_node = (struct Node *) malloc(sizeof(struct Node));

    if (p_new_node == NULL) {
        printf("Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }

    p_new_node -> data = value;
    p_new_node -> next = self -> head;

    self -> head = p_new_node;
}

//Return structure created on the stack
List list_create(void) {
    List list;
    list.head = NULL;

    return list;
}

int main() {
    /*
    List list = list_create();
    list_append(&list, 1);
    list_free(&list);
    assert(list.head == NULL);
    */

    List list = list_create();
    List other_list = list_create();

    list_push_front(&list, 3);
    list_push_front(&list, 2);
    list_push_front(&list, 1);
    list_append(&list, 4);

    list_push_front(&other_list, 6);
    list_push_front(&other_list, 5);
    list_push_front(&other_list, 4);

    struct Node* p_found_node_value = list_find(&list, 1);

    list_erase_after(&list, p_found_node_value);

    int i_val_1 = list_pop_front(&list);
    int i_val_2 = list_pop_front(&list);
    int i_val_3 = list_pop_front(&list);

    list_free(&list);

    return 0;
}