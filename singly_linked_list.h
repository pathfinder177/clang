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
void list_print(List *self);
void list_free(List* self); // deallocates list
void list_push_front(List* self, int value);
int list_pop_front(List* self);
struct Node* list_find(List* self, int value); // NULL if not found
void list_erase_after(List* self, struct Node* node);
void list_push_back(List* self, int value);
void list_merge_to_back(List* self, List* other);
void list_merge_to_front(List* self, List* other);
void list_splice_after(List* self, struct Node* after, List* other);