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
// void list_erase(List* self, struct Node* node);
// void list_merge_to_back(List* self, List* other);
// void list_merge_to_front(List* self, List* other);
// void list_splice_after(List* self, struct Node* after, List* other);

struct Node* list_find(List* self, int value) {
    if (self -> head == NULL) {
        printf("Can not FIND: list is empty\n");
        exit(EXIT_FAILURE);
    }

    struct Node *node = self -> head;

    while (node) {
        if (node -> data == value) {
            return node;
        }
        node = node -> next;
    }

    return NULL;
}

int list_pop_front(List* self) {
    if (self -> head == NULL) {
        printf("Can not POP: list is empty\n");
        exit(EXIT_FAILURE);
    }

    int head_data = self -> head -> data;

    if(self -> head -> next == NULL) {
        free((void *) self -> head);

        return head_data;
    }
    else {
        struct Node *after_head = self -> head -> next;
        free((void *) self -> head);
        self -> head = after_head;

        return head_data;
    }
}

//Delete only Node(s) from memory
void list_free(List* self) {
    struct Node *node, *node_next;
    node = node_next = self -> head;

    while (node) {
        node_next = node -> next;
        free((void *) node);
        node = node_next;
    }
}

void list_push_front(List* self, int value) {
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Memory allocation failed for Node\n");
        exit(EXIT_FAILURE);
    }

    new_node -> data = value;

    if (self -> head == NULL) {
        self -> head = new_node;
    }
    else {
        new_node -> next = self -> head;
        self -> head = new_node;
    }

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

    list_push_front(&list, 3);
    list_push_front(&list, 2);
    list_push_front(&list, 1);

    struct Node* p_found_node_value = list_find(&list, 3);

    int i_val_1 = list_pop_front(&list);
    int i_val_2 = list_pop_front(&list);
    int i_val_3 = list_pop_front(&list);

    list_free(&list);

    return 0;
}