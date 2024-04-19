#include "singly_linked_list.h"


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
    self->head = self->head->next;

    return head_data;
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