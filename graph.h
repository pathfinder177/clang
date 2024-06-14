//Implementation of simple directed regular cycled weighted graph

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#define GRAPH_SIZE 5

typedef struct {
    int index;
    int weight;
} Graph_vertice_neighbor;

typedef struct {
    int index;
    GPtrArray *neighbors;
} Graph_vertice;

typedef struct {
    GHashTable *vertices_table;
} Graph;

int* graph_init_vertices_indexes();
Graph graph_create();
void graph_free(Graph **);
void graph_list(Graph *);

void graph_add_vertice(Graph *, int *);
bool graph_erase_vertice(Graph *, int);
Graph_vertice* graph_get_vertice(Graph *, int);

void graph_add_edge(Graph *, int, int, int);
bool graph_erase_edge(Graph *, int, int);
static void graph_edge_function_check_pararameters(Graph *, Graph_vertice *, Graph_vertice *, int, int, int);
static Graph_vertice_neighbor* graph_find_neighbor(GPtrArray *, int);
static void graph_add_neighbors_table(Graph_vertice *);
static void graph_add_new_neighbor(GPtrArray *, int, int);