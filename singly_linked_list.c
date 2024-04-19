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
void list_push_back(List* self, int value);
void list_merge_to_back(List* self, List* other);
void list_merge_to_front(List* self, List* other);
void list_splice_after(List* self, struct Node* after, List* other);


void list_splice_after(List* self, struct Node* after, List* other) {
    if (self->head == NULL && other->head == NULL) {
        fputs("Can not SPLICE_AFTER: both lists are empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    if(after->next) {
        struct Node *p_node = after;

        while((p_node = p_node->next) != NULL) {
            list_push_back(other, p_node->data);
        }

        after->next = NULL;
        list_merge_to_back(self, other);
    }
    else {
        list_merge_to_back(self, other);
    }

}


void list_merge_to_front(List* self, List* other) {
    if (self->head == NULL && other->head == NULL) {
        fputs("Can not MERGE_TO_FRONT: both lists are empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    int value;
    while(other->head != NULL) {
        value = list_pop_front(other);
        list_push_front(self, value);
    }

}

void list_push_back(List* self, int value) {
    struct Node *p_new_node = (struct Node *) malloc(sizeof(struct Node));

    if (p_new_node == NULL) {
        fputs("Memory allocation failed for Node\n", stderr);
        exit(EXIT_FAILURE);
    }

    p_new_node->data = value;

    struct Node *p_node_before = self->head;
    while(p_node_before->next) {
        p_node_before = p_node_before->next;
    }

    p_node_before->next = p_new_node;

}

void list_merge_to_back(List* self, List* other) {
    if (self->head == NULL && other->head == NULL) {
        fputs("Can not MERGE_TO_BACK: both lists are empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    int value;
    while(other->head != NULL) {
        value = list_pop_front(other);
        list_push_back(self, value);
    }
}

void list_erase_after(List* self, struct Node* node) {
    if (self->head == NULL) {
        fputs("Can not ERASE_AFTER: list is empty\n", stderr);
        exit(EXIT_FAILURE);
    }
    else if(node->next == NULL) {
        fputs("Can not ERASE_AFTER: your node is the last in list\n", stderr);
        exit(EXIT_FAILURE);
    }

    struct Node *p_node_to_erase = node->next;
    node->next = p_node_to_erase->next;

    free(p_node_to_erase);

}

struct Node* list_find(List* self, int value) {
    if (self->head == NULL) {
        fputs("Can not FIND: list is empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    struct Node *p_node = self->head;

    while (p_node) {
        if (p_node->data == value) {
            return p_node;
        }
        p_node = p_node->next;
    }

    return NULL;
}

int list_pop_front(List* self) {
    if (self->head == NULL) {
        fputs("Can not POP: list is empty\n", stderr);
        exit(EXIT_FAILURE);
    }

    int head_data = self->head->data;
    struct Node *p_node_after_head = self->head->next;

    free(self->head);
    self->head = p_node_after_head;

    return head_data;
}


//Delete only Node(s) from memory
void list_free(List* self) {
    struct Node *p_node, *p_node_next;
    p_node = p_node_next = self->head;

    while (p_node) {
        p_node_next = p_node->next;
        free(p_node);
        p_node = p_node_next;
    }
}

void list_push_front(List* self, int value) {
    struct Node *p_new_node;

    if ((p_new_node = (struct Node *) malloc(sizeof(struct Node))) == NULL) {
        fputs("Memory allocation failed for Node\n", stderr);
        exit(EXIT_FAILURE);
    }

    p_new_node->data = value;
    p_new_node->next = self->head;

    self->head = p_new_node;
}

void list_print(List *self) {
    struct Node* node;

    if (self->head == NULL) {
        printf("Warning: can not PRINT: list is empty\n");
    }
    else {
        node = self->head;
        while(node) {
            printf("%d->", node->data);
            node = node->next;
        }
        printf("\n");
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
    list_push_back(&list, 1);
    list_free(&list);
    assert(list.head == NULL);
    */

    List list = list_create();
    List other_list = list_create();

    list_push_front(&list, 3);
    list_push_front(&list, 2);
    list_push_front(&list, 1);
    list_print(&list);

    list_push_front(&other_list, 6);
    list_push_front(&other_list, 5);
    list_push_front(&other_list, 4);
    list_print(&other_list);

    struct Node* p_found_node_value = list_find(&list, 1);

    list_splice_after(&list, p_found_node_value, &other_list);
    list_print(&list);

    list_merge_to_back(&list, &other_list);
    list_print(&list);

    list_merge_to_front(&list, &other_list);
    list_print(&list);

    list_erase_after(&list, p_found_node_value);
    list_print(&list);

    int i_val_1 = list_pop_front(&list);
    int i_val_2 = list_pop_front(&list);
    int i_val_3 = list_pop_front(&list);

    list_free(&list);

    return 0;
}