//ADT implementation: https://runestone.academy/ns/books/published/pythonds3/BasicDS/TheUnorderedListAbstractDataType.html

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    struct Node* head;
} List;

List list_create(); // returns empty list
// void list_free(List* self); // deallocates list
// void list_push_front(List* self, int value);
// int list_pop_front(List* self);
// struct Node* list_find(List* self, int value); // NULL if not found
// void list_erase(List* self, struct Node* node);
// void list_merge_to_back(List* self, List* other);
// void list_merge_to_front(List* self, List* other);
// void list_splice_after(List* self, struct Node* after, List* other);


//Return structure created on the stack
List list_create(void) {
    List list;
    list.head = NULL;

    return list;
}

int main() {

    /*usage example
    List list = list_create();
    list_append(&list, 1);
    list_free(&list);
    assert(list.head == NULL);
    */

    List list = list_create();

    return 0;
}