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

Graph graph_create();
void graph_free(Graph *);
void graph_list(Graph *);
static bool graph_is_null_pointer(Graph *);

void graph_add_vertice(Graph *, int);
bool graph_erase_vertice(Graph *, int);
Graph_vertice* graph_get_vertice(Graph *, int);

void graph_add_edge(Graph *, int, int, int);
bool graph_erase_edge(Graph *, int, int);
static void graph_edge_function_check_pararameters(Graph*, Graph_vertice*, Graph_vertice*, int, int, int);
static Graph_vertice_neighbor* graph_find_neighbor(GPtrArray *, int);
static void graph_add_neighbors_table(Graph_vertice *);
static void graph_add_new_neighbor(GPtrArray *, int, int);

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

static void graph_edge_function_check_pararameters(Graph* self, Graph_vertice* src, Graph_vertice* dest, int from_vertice, int to_vertice, int weight) {
    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    if((src == NULL) || dest == NULL ) {
        fprintf(stderr, "from_vertice or to_vertice does not exist in graph");
        abort();
    }

    if (from_vertice == to_vertice) {
        fprintf(stderr, "Self loops in graph is not allowed");
        abort();
    }

    if(from_vertice < 0 || to_vertice < 0) {
        fprintf(stderr, "Vertices indexes should be >= 0");
        abort();
    }

    if (weight <= 0) {
        fprintf(stderr, "Weight should be > 0");
        abort();
    }
}

static void graph_add_new_neighbor(GPtrArray *neighbors, int to_vertice, int weight) {
    Graph_vertice_neighbor* new_neighbor;

    if ((new_neighbor = (Graph_vertice_neighbor *) malloc(sizeof(*new_neighbor))) == NULL) {
        fprintf(stderr, "memalloc for Graph_vertice_neighbor failed");
        abort();
    }

    new_neighbor->index = to_vertice;
    new_neighbor->weight = weight;

    g_ptr_array_add(neighbors, new_neighbor);
}

static void graph_add_neighbors_table(Graph_vertice *self) {
    GPtrArray *ptr_array = g_ptr_array_new_with_free_func(g_free);

    self->neighbors = ptr_array;
}

static Graph_vertice_neighbor* graph_find_neighbor(GPtrArray *neighbors, int index) {
    guint i;
    Graph_vertice_neighbor* self;

    for (i = 0; i < neighbors->len; i++) {
        self = g_ptr_array_index(neighbors, i);
        if(self->index == index) {
            return self;
        }
    }

    return NULL;
}


//add a new weighted directed edge to the graph that connects two vertices
void graph_add_edge(Graph* self, int from_vertice, int to_vertice, int weight) {
    Graph_vertice* src;
    Graph_vertice* dest;

    src = graph_get_vertice(self, from_vertice);
    dest = graph_get_vertice(self, to_vertice);

    graph_edge_function_check_pararameters(self, src, dest, from_vertice, to_vertice, weight);

    if (dest->neighbors != NULL) {
        if (dest->neighbors->len > 0) {
            Graph_vertice_neighbor* n;

            if((n = graph_find_neighbor(dest->neighbors, from_vertice)) != NULL) {
                n = NULL;

                fprintf(stderr, "Reverse path is found in to_vertice");
                abort();
            }

            n = NULL;
        }
    }

    if (src->neighbors != NULL) {
        if (src->neighbors->len > 0) {
            Graph_vertice_neighbor* n;

            if((n = graph_find_neighbor(src->neighbors, to_vertice)) != NULL) {
                n->weight = weight;
                n = NULL;

                return;
            }
        }
    }
    else {
        graph_add_neighbors_table(src);
    }

    graph_add_new_neighbor(src->neighbors, to_vertice, weight);

}

/*
    erase edge from_vertice to_vertice if there is an edge
    namely delete neighbor of from_vertice vertice
*/
bool graph_erase_edge(Graph *self, int from_vertice, int to_vertice) {
    Graph_vertice* src;
    Graph_vertice* dest;
    int stub_weight = 1;

    src = graph_get_vertice(self, from_vertice);
    dest = graph_get_vertice(self, to_vertice);

    graph_edge_function_check_pararameters(self, src, dest, from_vertice, to_vertice, stub_weight);


    if (dest->neighbors != NULL) {
        if (dest->neighbors->len > 0) {
            Graph_vertice_neighbor* n;

            if((n = graph_find_neighbor(dest->neighbors, from_vertice)) != NULL) {
                n = NULL;

                fprintf(stderr, "Path is found in to_vertice. Are index positions correct?");
                abort();
            }
            n = NULL;
        }
    }

    if (src->neighbors != NULL) {
        if (src->neighbors->len > 0) {
            Graph_vertice_neighbor* n;

            if((n = graph_find_neighbor(src->neighbors, to_vertice)) != NULL) {
                return g_ptr_array_remove(src->neighbors, n);
            }
            return FALSE;
        }
        return FALSE;
    }
    return FALSE;
}

static bool graph_is_null_pointer(Graph *self) {
    return self == NULL;
}

/*
    return pointer to vertice from graph_vertices_table if there is a vertice
*/
Graph_vertice* graph_get_vertice(Graph* self, int index) {
    int* p_index;

    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

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
    erase vertice from neighbors table of other vertices, then
    erase vertice from graph_vertices_table
*/
bool graph_erase_vertice(Graph* self, int index) {
    int* p_index;

    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

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
    bool is_in_table;
    int* p_index;
    Graph_vertice *new_vertice;

    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

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
        new_vertice->neighbors = NULL;

        g_hash_table_insert(self->vertices_table, p_index, new_vertice);
    }
}

/*
Create a new empty graph on stack
Graph keeps empty vertices_table
*/
Graph graph_create() {
    Graph graph;
    graph.vertices_table = g_hash_table_new_full(g_int_hash, g_int_equal, free, free);

    return graph;
}

void graph_free(Graph *self) {
    if (graph_is_null_pointer(self)) {
        fprintf(stdout, "graph pointer is equal to NULL");
        return;
    }

    GList* vertices = g_hash_table_get_keys(self->vertices_table);
    Graph_vertice* vertice;

    while(vertices != NULL) {
        vertice = (Graph_vertice*)(vertices->data);
        g_ptr_array_free(vertice->neighbors, TRUE);

        vertices = vertices->next;
    }

    g_list_free(vertices);

    g_hash_table_destroy(self->vertices_table);
    g_hash_table_unref(self->vertices_table);
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

    //added
    graph_add_edge(p_graph, 1, 2, 4);
    //abort as graph is not a multigraph
    // graph_add_edge(p_graph, 2, 1, 4);

    bool is_edge_erased = graph_erase_edge(p_graph, 1, 2);

    graph_list(p_graph);

    graph_free(p_graph);

    return 0;
}