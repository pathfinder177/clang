//ADT implementation: https://runestone.academy/ns/books/published/pythonds3/BasicDS/TheUnorderedListAbstractDataType.html
//except for add_item as it copying append

#include <stdio.h>
#include <stdlib.h>

//define MAX_SIZE; not handled but keep in mind

struct Node
{
    int data;
    struct Node *next;
};

static struct Node *head;


struct Node *List(void) {
    struct Node *p = (struct Node *) malloc(sizeof(struct Node));
    p -> data = -1;
    p -> next = NULL;
    return p;
}

int is_empty() {
    if(head -> data == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int size() {
    if(is_empty()) {
        return 0;
    }

    int size = 1;
    struct Node *node = head;

    while(node -> next != NULL) {
        size++;
        node = node -> next;
    }
    return size;
}

static struct Node *add_node() {
    return (struct Node *) malloc(sizeof(struct Node));
}

void append(int item) {
    if(is_empty()) {
        head -> data = item;
    }
    else {
        struct Node *node = head;

        while(node -> next) {
            node = node -> next;
        }

        struct Node *new_node = add_node();
        new_node -> data = item;
        new_node -> next = NULL;

        node -> next = new_node;

    }
}

void free_mem(struct Node *node) {
    if(node -> data || node -> next) {
        free(node);
    }
}

void remove_item(int item) {
    if(is_empty()) {
        printf("list is empty, exit...\n"); //actually raise ERROR makes more sense here
    }
    else if (head -> data == item) {
        if (head -> next != NULL) {
            head = head -> next;
        }
        else {
            free_mem(head);
        }
    }
    else {
        struct Node *node = head;

        while(node -> next) {
            if (node -> next -> data == item) {
                struct Node *p = node -> next -> next;
                free_mem(node -> next);
                node -> next = p;
                return;
            }
            node = node -> next;
        }

        if(node -> data == item) {
            free_mem(node);
        }
        else {
            printf("No %d in the list!\n", item);
        }
    }
}


int search(int item) {
    if(is_empty()) {
        printf("list is empty, exit...\n");
        return 0;
    }
    else {
        struct Node *node = head;

        while(node -> next) {
            if(node -> data == item) {
                return 1;
            }
            node = node -> next;
        }

        if(node -> data == item) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

int my_index(int item) {
    if(is_empty()) {
        printf("list is empty, exit...\n");
        return -1;
    }
    else {
        struct Node *node = head;

        int index_pos = 0;
        while(node -> next) {
            if(node -> data == item) {
                return index_pos;
            }
            index_pos++;
            node = node -> next;
        }

        if(node -> data == item) {
            return index_pos;
        }
        else {
            return -1;
        }
    }
}

int my_pop() {
    if(is_empty()) {
        printf("list is empty, exit...\n");
        return -1;
    }
    else {
        struct Node *node = head;

        while(node -> next -> next) {
            node = node -> next;
        }

        int last_node_data = node -> next -> data;

        free_mem(node -> next);
        node -> next = NULL;

        return last_node_data;
    }
}

int my_pop_pos(int item) {
    if(is_empty()) {
        printf("list is empty, exit...\n"); //actually raise ERROR makes more sense here

        return -1;
    }
    else if (head -> data == item) {
        if (head -> next != NULL) {
            int head_data = head -> data;
            head = head -> next;

            return head_data;
        }
        else {
            int head_data = head -> data;
            free_mem(head);

            return head_data;
        }
    }
    else {
        struct Node *node = head;

        while(node -> next) { //change format of dereferencing
            if (node -> next -> data == item) {
                struct Node *p = node -> next -> next;
                int node_data = node -> next -> data;

                free_mem(node -> next);
                node -> next = p;

                return node_data;
            }
            node = node -> next;
        }

        if(node -> data == item) {
            int node_data = node -> data;
            free_mem(node);

            return node_data;
        }
        else {
            printf("No %d in the list!\n", item);

            return -1;
        }
    }
}

void insert_item(int pos, int item) {
    int l_size = size(); //if there is the only node that has data then size = 1

    if (l_size < pos) {
        printf("Can not insert item at pos %d, list size is %d\n", pos, l_size);
    }

    if (head -> next == NULL) {
        head -> data = item;
    }
    else if (head -> next){
        struct Node *new_node = add_node();
        new_node -> data = item;
        new_node -> next = head;

        head = new_node;
    }
    else {
        struct Node *node = head;
        int current_pos = 0;

        while(current_pos != (pos-1)) {
            current_pos++;
            node = node -> next;
        }

        if (node -> next) {
            struct Node *new_node = add_node();
            new_node -> data = item;
            new_node -> next = node -> next;

            node -> next = new_node;
        }
        else {
            struct Node *new_node = add_node();
            new_node -> data = item;
            new_node -> next = NULL;

            node -> next = new_node;
        }
    }
}

int main() {
    head = List();

    int empty = is_empty();
    int l_size = size();

    int item = 1;
    int item2 = 2;
    int item3 = 3;

    append(item);
    append(item2);
    append(item3);
    // //head(1)->Node(2)->Node(3)->NULL

    int is_in_list = search(item2);
    is_in_list = search(item3);

    int index_pos = my_index(item2);
    index_pos = my_index(item3);

    int pop_elem = my_pop();
    // //head(1)->Node(2)->NULL

    int pos = 0;
    int item4 = 4;
    insert_item(pos, item4);
    //head(4)->Node(1)->Node(2)->Node(3)->NULL

    int pop_elem_pos = my_pop_pos(item);
    pop_elem_pos = my_pop_pos(item3);
    //head(4)->Node(2)->NULL

    remove_item(2);
    //head(4)->NULL
    remove_item(111);

    free_mem(head); // maybe it makes sense to go from head to end and free each node mem apartly
    return 0;
}
