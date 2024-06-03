//idea: https://runestone.academy/ns/books/published/pythonds3/Graphs/AnAdjacencyList.html
//Implementation of simple directed cycled weighted graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "graph_hash_table.c"

#define GRAPH_VERTICES_TABLE_SIZE 10

typedef struct {
    struct Graph_vertice_neighbor *next;
    char *name;
    int weight;
} Graph_vertice_neighbor;

typedef struct {
    struct Graph_vertice_neighbor *next;
    char* name;
} Graph_vertice;


typedef struct {
    Graph_vertice *vertices_table[GRAPH_VERTICES_TABLE_SIZE];
} Graph;

Graph graph_create();
void graph_free(Graph *);
void graph_list(Graph *);

void graph_add_vertice(Graph*, char *);
void graph_erase_vertice(Graph*, char *);
Graph_vertice* graph_get_vertice(char *);
Graph_vertice** graph_get_vertices(Graph *);

void graph_add_edge(Graph*, char *, char *, int);
void graph_erase_edge(Graph*, char *, char *);

unsigned hash(char *); //FIXME define in other file

unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

    return hashval % GRAPH_VERTICES_TABLE_SIZE;
}

/*print all vertices names in graph*/
void graph_list(Graph *self) {
    ;
}

/*
    add a new weighted directed edge to the graph that connects two vertices
    list of neighbors for any vertice should be ordered, e.g.: n2, n4, n5
    thus the function takes it into account as well
    if there is already an edge between from_v1&to_v2: show warning about change and set new weight
    if there is an edge from to_v2 to from_v1: error as the graph is simple
*/
void graph_add_edge(Graph* self, char *from_v1, char *to_v2, int weight) {
    ;
}

/*
    erase edge from_v1 to_v2 if there is an edge
    namely delete neighbor of from_v1 vertice and keep list of neighbors in order
*/
void graph_erase_edge(Graph *self, char *from_v1, char *to_v2) {
    ;
}

/*
    return array of pointers to all vertices in Graph
*/
Graph_vertice** graph_get_vertices(Graph *self) {
    ;
}

/*
    return vertice name from graph_vertices_table if there is a vertice
*/
Graph_vertice* graph_get_vertice(char *name) {
    ;
}

/*
    erase vertice from graph_vertices_table
    if vertice has neighbors:
        keep neighbor list ordered for other vertices
        e.g. erase n3 and n2 has neighbors list n1->n3->n5 then n2 has n1->n5 after erasing n3
*/
void graph_erase_vertice(Graph* self, char *name) {
    ;
}

/*
    add a new vertice without neighbors to graph_vertices_table
*/
void graph_add_vertice(Graph* self, char *name) {
    Graph_vertice *new_vertice;
    unsigned hashval;

    // if((new_vertice = graph_get_vertice(self, name)) == NULL) {

    new_vertice = (Graph_vertice *) malloc(sizeof(*new_vertice));
    if (new_vertice == NULL) {
            fprintf(stderr, "memalloc for Graph_vertice failed");
            abort();
        }

    hashval = hash(name);

    new_vertice->name = name;
    new_vertice->next = NULL;

    self->vertices_table[hashval] = new_vertice;
    // }


}

/*
Create a new empty graph on stack
Empty graph keeps empty vertices_table
*/
Graph graph_create() {
    Graph graph;

    return graph;
}

int main() {
    char* vertice_names[] = {"n0", "n1", "n2", "n3", "n4"};
    Graph graph = graph_create();

    int i;
    for (i = 0; i < 5; i++) {
        graph_add_vertice(&graph, vertice_names[i]);
    }

    return 0;
}