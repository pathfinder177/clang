#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "graph_hash_table.c"

#define GRAPH_NODES_TABLE_SIZE 20
// #define NEIGHBORS_TABLE_SIZE 20


// typedef struct {
//     struct Neigbor *next;
//     char *name;
//     int *weight;
//     struct Graph_node *node;
// } Neigbor;

typedef struct {
    struct Graph_node *next;
    struct Graph_node **p_node;
    char* name;
    // struct Neigbor *neighbors_tab[NEIGHBORS_TABLE_SIZE];
} Graph_node;


typedef struct {
    Graph_node *nodes_table[GRAPH_NODES_TABLE_SIZE];
} Graph;

Graph graph_create();
void graph_free(Graph *);

Graph_node* graph_get_node(char *);
void graph_set_node(Graph*, char *);
// void graph_erase_node(Graph *);

// void graph_list(Graph *);

unsigned hash(char *);

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % GRAPH_NODES_TABLE_SIZE;
}

void graph_set_node(Graph* self, char *name) {
    Graph_node *new_node;
    unsigned hashval;

    // if((new_node = graph_get_node(self, name)) == NULL) {

    new_node = (Graph_node *) malloc(sizeof(*new_node));
    // if (new_node == NULL) {
        //     fprintf(stderr, "memalloc for Graph_node failed");
        //     abort();
        // }

    hashval = hash(name);

    new_node->name = name;
    new_node->p_node = &new_node; //pointer to pointer
    new_node->next = self->nodes_table[hashval];

    self->nodes_table[hashval] = new_node;

    // }


}


Graph graph_create() {
    Graph graph;

    return graph;
}

int main() {
    char* node_names[] = {"n0", "n1", "n2", "n3", "n4"};
    printf("%s\n", node_names[0]);

    Graph graph = graph_create();

    int i;
    for (i = 0; i < 5; i++) {
        graph_set_node(&graph, node_names[i]);
    }

    return 0;
}