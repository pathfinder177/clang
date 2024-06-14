#include "graph.h"

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

static void graph_edge_function_check_pararameters(Graph *self, Graph_vertice *src, Graph_vertice *dest, int from_vertice, int to_vertice, int weight) {
    if (self == NULL) {
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
    Graph_vertice_neighbor* self;

    for (guint i = 0; i < neighbors->len; i++) {
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
            if(graph_find_neighbor(dest->neighbors, from_vertice) != NULL) {
                fprintf(stderr, "Reverse path is found in to_vertice");
                abort();
            }
        }
    }

    if (src->neighbors != NULL) {
        if (src->neighbors->len > 0) {
            Graph_vertice_neighbor* n = NULL;

            if((n = graph_find_neighbor(src->neighbors, to_vertice)) != NULL) {
                n->weight = weight;

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
            if(graph_find_neighbor(dest->neighbors, from_vertice) != NULL) {
                fprintf(stderr, "Path is found in to_vertice. Are index positions correct?");
                abort();
            }
        }
    }

    if (src->neighbors != NULL) {
        if (src->neighbors->len > 0) {
            Graph_vertice_neighbor* n = NULL;

            if((n = graph_find_neighbor(src->neighbors, to_vertice)) != NULL) {
                return g_ptr_array_remove(src->neighbors, n);
            }
            return false;
        }
        return false;
    }
    return false;
}

/*
    return pointer to vertice from graph_vertices_table if there is a vertice
*/
Graph_vertice* graph_get_vertice(Graph* self, int index) {
    if (self == NULL) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    return g_hash_table_lookup(self->vertices_table, (gconstpointer) &index);
}

/*
    erase vertice from neighbors table of other vertices, then
    erase vertice from graph_vertices_table
*/
bool graph_erase_vertice(Graph* self, int index) {
    if (self == NULL) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    //erase vertice from neighbors table of other vertices
    GList* glist = g_hash_table_get_keys(self->vertices_table);

    while(glist != NULL) {
        int from_vertice = *((int *)(glist->data));

        if(from_vertice != index) {
            graph_erase_edge(self, from_vertice, index);
        }

        glist = glist->next;
    }

    if (self->vertices_table != NULL) {
        return g_hash_table_remove(self->vertices_table, (gconstpointer) &index);
    }

    fprintf(stderr, "graph pointer is equal to NULL");
    abort();
}

/*
    add a new vertice without neighbors to graph_vertices_table
*/
void graph_add_vertice(Graph* self, int* index) {
    bool is_in_table;
    Graph_vertice *new_vertice;

    if (self == NULL) {
        fprintf(stderr, "graph pointer is equal to NULL");
        abort();
    }

    if((is_in_table = g_hash_table_contains(self->vertices_table, index)) == FALSE) {
        if ((new_vertice = (Graph_vertice *) malloc(sizeof(*new_vertice))) == NULL) {
                fprintf(stderr, "memalloc for Graph_vertice failed");
                abort();
        }

        new_vertice->index = *index;
        new_vertice->neighbors = NULL;

        g_hash_table_insert(self->vertices_table, index, new_vertice);
    }
}

/*
Create a new empty graph on stack
Graph keeps empty vertices_table
*/
Graph graph_create() {
    Graph graph;
    graph.vertices_table = g_hash_table_new_full(g_int_hash, g_int_equal, NULL, free);

    return graph;
}

void graph_free(Graph **self) {
    if ((*self) == NULL) {
        fprintf(stdout, "graph pointer is equal to NULL");
        return;
    }

    Graph_vertice* vertice;
    GList* vertices = g_hash_table_get_values((*self)->vertices_table);

    while(vertices != NULL) {
        vertice = vertices->data;

        if(vertice->neighbors != NULL) {
            g_ptr_array_free(vertice->neighbors, TRUE);
            vertice->neighbors = NULL;
        }

        vertices = vertices->next;
    }

    g_hash_table_destroy((*self)->vertices_table);
    (*self)->vertices_table = NULL;
    *self = NULL;
}

int* graph_init_vertices_indexes() {
    //static arr also can be used but not so explicit
    static int vertices_indexes[GRAPH_SIZE];

    for (int i = 0; i <= GRAPH_SIZE; i++) {
        vertices_indexes[i] = i;
    }

    return vertices_indexes;
}