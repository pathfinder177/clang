//idea: https://runestone.academy/ns/books/published/pythonds3/Graphs/AnAdjacencyList.html
//Implementation of simple directed cycled weighted graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#define GRAPH_SIZE 5
#define GRAPH_NEIGHBORS_TABLE_SIZE 5

typedef struct {
    int index;
    int weight;
} Graph_vertice_neighbor;

typedef struct {
    int index;
    GArray *neigbors;
} Graph_vertice;


typedef struct {
    GHashTable *vertices_table;
} Graph;

Graph graph_create();
void graph_free(Graph *);
void graph_list(Graph *);
static void print_key(gpointer, gpointer, gpointer);

void graph_add_vertice(Graph *, int);
bool graph_erase_vertice(Graph *, int);
Graph_vertice* graph_get_vertice(int);

void graph_add_edge(Graph *, int, int, int);
void graph_erase_edge(Graph *, int, int);

static void print_key(gpointer key, gpointer value, gpointer user_data) {
    printf("Key: %d\n", GPOINTER_TO_INT(key));
}

/*print all vertices indexes in graph*/
void graph_list(Graph *self) {
    g_hash_table_foreach(self->vertices_table, print_key, NULL);
}

/*
    add a new weighted directed edge to the graph that connects two vertices
    list of neighbors for any vertice should be ordered, e.g.: n2, n4, n5
    thus the function takes it into account as well
    if there is already an edge between from_v1&to_v2: show warning about change and set new weight
    if there is an edge from to_v2 to from_v1: error as the graph is simple
*/
void graph_add_edge(Graph* self, int from_v1, int to_v2, int weight) {
    ;
}

/*
    erase edge from_v1 to_v2 if there is an edge
    namely delete neighbor of from_v1 vertice
*/
void graph_erase_edge(Graph *self, int from_v1, int to_v2) {
    ;
}


/*
    return pointer to vertice from graph_vertices_table if there is a vertice
*/
Graph_vertice* graph_get_vertice(int index) {
    ;
}

/*
    erase vertice from neigbors table of other vertices, then
    erase vertice from graph_vertices_table
*/
bool graph_erase_vertice(Graph* self, int index) {
    int* p_index = &index;

    //TODO: remove vertice from neighbors tables

    return g_hash_table_remove(self->vertices_table, p_index);
}

/*
    add a new vertice without neighbors to graph_vertices_table
*/
void graph_add_vertice(Graph* self, int index) {
    bool is_in_table;
    int* p_index = &index;
    Graph_vertice *new_vertice;

    if((is_in_table = g_hash_table_contains(self->vertices_table, p_index)) == FALSE) {

        new_vertice = (Graph_vertice *) malloc(sizeof(*new_vertice));
        if (new_vertice == NULL) {
                fprintf(stderr, "memalloc for Graph_vertice failed");
                abort();
        }

        new_vertice->index = index;
        new_vertice->neigbors = NULL;

        g_hash_table_insert(self->vertices_table, p_index, new_vertice);
    }

}

/*
Create a new empty graph on stack
Graph keeps empty vertices_table
*/
Graph graph_create() {
    Graph graph;
    graph.vertices_table = g_hash_table_new(g_int_hash, g_int_equal);

    return graph;
}

int main() {
    Graph graph = graph_create();
    Graph* p_graph = &graph;

    //vertices with indexes from 0 to 5
    int i;
    for (i = 1; i <= GRAPH_SIZE+1; i++) {
        graph_add_vertice(p_graph, i);
    }

    // graph_list(p_graph);

    //0,1,2,4,5
    graph_erase_vertice(p_graph, 3);

    // graph_list(p_graph);
    g_hash_table_foreach(p_graph->vertices_table, print_key, NULL);

    g_hash_table_destroy(p_graph->vertices_table);
    // graph_free(p_graph);

    return 0;
}