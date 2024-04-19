#include "singly_linked_list.h"

int main() {
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