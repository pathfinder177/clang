//Implementation of simple directed regular cycled weighted graph

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
static bool graph_is_null_pointer(Graph *);

void graph_add_vertice(Graph *, int);
bool graph_erase_vertice(Graph *, int);
Graph_vertice* graph_get_vertice(Graph *, int);

void graph_add_edge(Graph *, int, int, int);
void graph_erase_edge(Graph *, int, int);


/*print all vertices indexes in graph*/
void graph_list(Graph *self) {
    //allocate mem
    GList* glist = g_hash_table_get_keys(self->vertices_table);

    while(glist != NULL) {
        printf("%d\n", *((int *)(glist->data)));
        glist = glist->next;
    }

    //dellocate mem
    g_list_free(glist);
}

/*
    add a new weighted directed edge to the graph that connects two vertices
    if there is already an edge between from_v1&to_v2: update weight
    if there is an edge from to_v2 to from_v1: error as the graph is simple
*/
void graph_add_edge(Graph* self, int from_v1, int to_v2, int weight) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }
}

/*
    erase edge from_v1 to_v2 if there is an edge
    namely delete neighbor of from_v1 vertice
*/
void graph_erase_edge(Graph *self, int from_v1, int to_v2) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }
}

static bool graph_is_null_pointer(Graph *self) {
    return self == NULL;
}

/*
    return pointer to vertice from graph_vertices_table if there is a vertice
*/
Graph_vertice* graph_get_vertice(Graph* self, int index) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    int* p_index;

    if ((p_index = (int *) malloc(sizeof(index))) == NULL) {
        fprintf(stderr, "memalloc for index failed");
        abort();
    }
    *p_index = index;

    Graph_vertice* p_vertice = g_hash_table_lookup(self->vertices_table, p_index);
    free(p_index);

    return p_vertice;
}

/*
    erase vertice from neigbors table of other vertices, then
    erase vertice from graph_vertices_table
*/
bool graph_erase_vertice(Graph* self, int index) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    int* p_index;

    if ((p_index = (int *) malloc(sizeof(index))) == NULL) {
        fprintf(stderr, "memalloc for index failed");
        abort();
    }
    *p_index = index;

    bool is_deleted = g_hash_table_remove(self->vertices_table, p_index);
    free(p_index);

    return is_deleted;
}

/*
    add a new vertice without neighbors to graph_vertices_table
*/
void graph_add_vertice(Graph* self, int index) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    bool is_in_table;
    int* p_index;
    Graph_vertice *new_vertice;

    if ((p_index = (int *) malloc(sizeof(index))) == NULL) {
        fprintf(stderr, "memalloc for index failed");
        abort();
    }
    *p_index = index;

    if((is_in_table = g_hash_table_contains(self->vertices_table, p_index)) == FALSE) {
        if ((new_vertice = (Graph_vertice *) malloc(sizeof(*new_vertice))) == NULL) {
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

void graph_free(Graph *self) {
    if (graph_is_null_pointer(self)) {
        fprintf(stdout, "graph pointer is equal to NULL");
        return;
    }

    g_hash_table_destroy(self->vertices_table);
}

int main() {
    Graph graph = graph_create();
    Graph* p_graph = &graph;

    //vertices with indexes from 1 to 5
    int i;
    for (i = 0; i <= GRAPH_SIZE; i++) {
        graph_add_vertice(p_graph, i);
    }

    //0,1,2,4,5
    graph_erase_vertice(p_graph, 3);

    graph_list(p_graph);

    //pointer to vertice with index 1
    Graph_vertice *v_1 = graph_get_vertice(p_graph, 1);

    // graph_add_edge(p_graph, 1, 2, 4);

    graph_list(p_graph);



    // graph_free(p_graph);

    return 0;
}