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
static Graph_vertice_neighbor* graph_find_neighbor(GArray *, int);
static void graph_add_neighbors_table(Graph_vertice *);

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

static void graph_add_neighbors_table (Graph_vertice *self) {
    bool is_zero_terminated = FALSE;
    bool is_clear = TRUE;
    guint size = (guint) sizeof(Graph_vertice_neighbor);

    self->neigbors = g_array_new(is_zero_terminated, is_clear, size);
    g_array_set_size(self->neigbors, (guint) GRAPH_NEIGHBORS_TABLE_SIZE);

    if(self->neigbors == NULL) {
        fprintf(stderr, "Failure neighbors allocation");
        abort();
    }
}

static Graph_vertice_neighbor* graph_find_neighbor(GArray *neighbors, int index) {
    if (neighbors == NULL) {
        fprintf(stderr, "neighbors pointer is equal to NULL");
        abort();
    }

    for(guint i = 0; i < neighbors->len; i++) {
        Graph_vertice_neighbor *n = neighbors->data[i];
        if (n->index == index) {
            return n;
        }
    }

    return NULL;
}

/*
    add a new weighted directed edge to the graph that connects two vertices
    if there is already an edge between from_vertice&to_vertice: update weight
    if there is an edge from to_vertice to from_vertice: error as the graph is simple
*/
void graph_add_edge(Graph* self, int from_vertice, int to_vertice, int weight) {
    Graph_vertice* src;
    Graph_vertice* dest;

    if (graph_is_null_pointer(self)) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    if (weight <= 0) {
        fprintf(stderr, "Weight should be > 0");
        abort();
    }

    src = graph_get_vertice(self, from_vertice);
    dest = graph_get_vertice(self, to_vertice);

    if((src == NULL) || dest == NULL ) {
        fprintf(stderr, "Src or dest vertice does not exist");
        abort();
    }

    if (dest->neigbors != NULL) {
        if (dest->neigbors->len > 0) {
            Graph_vertice_neighbor* n;
            GArray *dest_neighbors = dest->neigbors;

            if((n = graph_find_neighbor(dest_neighbors, from_vertice)) != NULL) {
                n = NULL;
                dest_neighbors = NULL;
                free(src);
                free(dest);

                fprintf(stderr, "Reverse path is found in dest vertice");
                abort();
            }

            n = NULL;
            dest_neighbors = NULL;
        }
    }

    if (src->neigbors != NULL) {
        if (src->neigbors->len > 0) {
            Graph_vertice_neighbor* n;
            GArray *src_neighbors = src->neigbors;

            if((n = graph_find_neighbor(src_neighbors, to_vertice)) != NULL) {
                n->weight = weight;

                free(src);
                free(dest);
                src_neighbors = NULL;
                n = NULL;

                return;
            }
        }
    }
    else {
        graph_add_neighbors_table(src);
    }

    //TODO to function
    Graph_vertice_neighbor* new_neighbor;
    if ((new_neighbor = (Graph_vertice_neighbor *) malloc(sizeof(*new_neighbor))) == NULL) {
        fprintf(stderr, "memalloc for Graph_vertice_neighbor failed");
        abort();
    }

    new_neighbor->index = to_vertice;
    new_neighbor->weight = weight;

    g_array_append_val(src->neigbors, new_neighbor);

}

/*
    erase edge from_vertice to_vertice if there is an edge
    namely delete neighbor of from_vertice vertice
*/
void graph_erase_edge(Graph *self, int from_vertice, int to_vertice) {
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
    erase vertice from neigbors table of other vertices, then
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

    graph_add_edge(p_graph, 1, 2, 4);

    graph_list(p_graph);



    // graph_free(p_graph);

    return 0;
}