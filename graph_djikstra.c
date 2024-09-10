#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "graph_djikstra_heap.h"

#define INIT_DISTANCE 100

void graph_djikstra_set_weights(Graph *);
static int** graph_djikstra_init_distance_vector(Graph *, Graph_vertice *);
static gint compare_ints(gconstpointer, gconstpointer);

int** graph_djikstra(Graph*, Graph_vertice *);
static bool graph_djikstra_update_distance_vector(int **, int *);
static int graph_djikstra_get_weight_distance_vector(int **, int);

void graph_djikstra_backtrack(Graph *, int **, Graph_vertice *, Graph_vertice *);
static bool graph_djikstra_backtrack_func(Graph *, Graph_vertice *, int, int);
static Graph_vertice_neighbor* graph_djikstra_backtrack_func_get_neighbor(GPtrArray *, int *, int);

static Graph_vertice_neighbor* graph_djikstra_backtrack_func_get_neighbor(GPtrArray *neighbors, int *visited_neighbors, int visited_neighbors_size) {
    Graph_vertice_neighbor* self;

    for (guint n = 0; n < neighbors->len; n++) {
        self = g_ptr_array_index(neighbors, n);
        for (int v_n = 0; v_n < visited_neighbors_size; v_n++) {
            if(self == NULL) {
                break;
            }
            if(visited_neighbors[v_n] == self->index) {
                self = NULL;
            }
        }
        if(self != NULL) {
            return self;
        }
    }

    return NULL;

}

static bool graph_djikstra_backtrack_func(Graph *self, Graph_vertice *start, int finish_index, int distance) {
    printf("%d -> \n", start->index);

    // int visited_neighbors[(finish_index - (start->index))];
    int* visited_neighbors = (int *) calloc(start->neighbors->len, sizeof(int));
    if (visited_neighbors == NULL) {
        perror("visited_neighbors memory allocation failed\n");
        abort();
    }

    Graph_vertice_neighbor *neighbor;
    for (int i = 0; i < start->neighbors->len; i++) {
        neighbor = graph_djikstra_backtrack_func_get_neighbor(start->neighbors, visited_neighbors, start->neighbors->len);
        if(neighbor == NULL) {
            return false;
       }

        int distance_neighbor_to_finish = distance - (neighbor->weight);

        if ((distance_neighbor_to_finish == 0) && (neighbor->index == finish_index)) {
            printf("%d\n", neighbor->index);
            return true;
        }
        else if(distance_neighbor_to_finish < 0) {
            visited_neighbors[i] = neighbor->index;
            printf("v%d: distance is exceeded, trying other neighbors\n", neighbor->index);
        }
        else {
            Graph_vertice *neighbor_vertice = graph_get_vertice(self, neighbor->index);

            visited_neighbors[i] = neighbor->index;
            bool is_path_found = graph_djikstra_backtrack_func(self, neighbor_vertice, finish_index, distance_neighbor_to_finish);

            if(is_path_found) {
                return true;
            }
        }

    }
    free(visited_neighbors);

    return false;
}

void graph_djikstra_backtrack(Graph *self, int **distance_vector, Graph_vertice *start, Graph_vertice *finish) {
    int distance = distance_vector[finish->index][0] - distance_vector[start->index][0];

    printf("From v%d to v%d the shortest path is: \n", start->index, finish->index);

    graph_djikstra_backtrack_func(self, start, finish->index, distance);
}

void graph_djikstra_set_weights(Graph *self) {
    //0 -(4)> 1
    graph_add_edge(self, 0, 1, 4);
    //0 -(4)> 2
    graph_add_edge(self, 0, 2, 4);
    //1 -(2)> 2
    graph_add_edge(self, 1, 2, 2);
    //2 -(3)> 3
    graph_add_edge(self, 2, 3, 3);
    //2 -(1)> 4
    graph_add_edge(self, 2, 4, 1);
    //2 -(6)> 5
    graph_add_edge(self, 2, 5, 6);
    //3 -(2)> 5
    graph_add_edge(self, 3, 5, 2);
    //4 -(3)> 5
    graph_add_edge(self, 4, 5, 3);
}

static gint compare_ints(gconstpointer a, gconstpointer b) {
    gint int_a = *(gint*)a;
    gint int_b = *(gint*)b;

    return (int_a > int_b) - (int_a < int_b);
}

static int** graph_djikstra_init_distance_vector(Graph *self, Graph_vertice *start) {
    int priority_key_size = 2; // Fixed size of each inner array FIXME
    int key = start->index;

    GList* indexes = g_hash_table_get_keys(self->vertices_table);
    indexes = g_list_sort(indexes, compare_ints);
    int indexes_number = g_list_length(indexes); //external array

    // Allocate memory for the external array
    int **distance_vector = malloc(indexes_number * sizeof(int *));
    if (distance_vector == NULL) {
        perror("Failed to allocate memory for external array");
        abort();
    }

    // Allocate memory for each inner array
    for (int i = 0; i < indexes_number; i++) {
        distance_vector[i] = malloc(priority_key_size * sizeof(int));

        if (distance_vector[i] == NULL) {
            perror("Failed to allocate memory for inner array");
            abort();
        }
    }

    distance_vector[0][0] = 0;
    distance_vector[0][1] = key;

    //FIXME traverse indexes
    indexes = indexes->next;

    for (int i = 1; i < indexes_number; i++) {
        key = *((int *)(indexes->data));
        if (key != start->index) {
            // Initialize the inner array
            distance_vector[i][0] = INIT_DISTANCE;
            distance_vector[i][1] = key;
        }
        indexes = indexes->next;
    }

    // print FIXME to apart function
    // for (int i = 0; i < indexes_number; i++) {
    //     printf("Priority and key %d: ", i);
    //     for (int j = 0; j < priority_key_size; j++) {
    //         printf("%d ", distance_vector[i][j]);
    //     }
    //     printf("\n");
    // }

    return distance_vector;
}

static bool graph_djikstra_update_distance_vector(int **distance_vector, int *current_neighbor) {
    int weight = current_neighbor[0];
    int index = current_neighbor[1];

    //#FIXME
    for (int i = 0; i < 6; i++) {
        if((distance_vector[i][1] == index) && (distance_vector[i][0] > weight)) {
                distance_vector[i][0] = weight;
                return true;
        }
    }

    return false;
}

static int graph_djikstra_get_weight_distance_vector(int **distance_vector, int current_vertice_index) {

    //#FIXME
    for (int i = 0; i < 6; i++) {
        if(distance_vector[i][1] == current_vertice_index) {
            int weight = distance_vector[i][0];
            return weight;
        }
    }

    return 0;
}

int** graph_djikstra(Graph* self, Graph_vertice* start) {
    /*
    the shortest path to node 5 is 8 in this example:
    0 -(4)> 2 -(1)> 4 -(3)> 5 = 4+1+3 = 8
    */

   //FIXME make distance vector a struct

    if(start->neighbors->len <= 0) {
        printf("Start node with index %d has no neighbors \n", start->index);
        abort();
    }

    int **distance_vector = graph_djikstra_init_distance_vector(self, start);
    int *start_vertice = distance_vector[0];

    Heap *heap = heap_create();
    heap_push(heap, start_vertice);

    while(heap->size > 0) {
        int *current_node = heap_pop(heap);
        int current_node_index = current_node[1];
        Graph_vertice* current_vertice = graph_get_vertice(self, current_node_index);
        GPtrArray *neighbors = current_vertice->neighbors;

        if(neighbors == NULL || neighbors->len <= 0) {
            printf("Node with index %d has no neighbors \n", current_node_index);
            break;
        }

        for (guint i = 0; i < neighbors->len; i++) {
            Graph_vertice_neighbor* curr_vertice_neighbor = g_ptr_array_index(neighbors, i);

            //FIXME
            int *current_neighbor = (int *) malloc(2 * sizeof(int));
            current_neighbor[0] = curr_vertice_neighbor->weight;
            current_neighbor[1] = curr_vertice_neighbor->index;

            if (current_vertice->index == start->index) {
                graph_djikstra_update_distance_vector(distance_vector, current_neighbor);
                heap_push(heap, current_neighbor);
            }
            else {
                /*
                get weight of current vertice by index
                add this weight to the neigbor weight
                see whether path is shorter from start
                */
                int current_vertice_weight = graph_djikstra_get_weight_distance_vector(distance_vector, current_vertice->index);
                if(current_vertice_weight == 0) {
                    perror("Current vertice weight");
                    abort();
                }

                current_neighbor[0] += current_vertice_weight;

                bool is_updated = graph_djikstra_update_distance_vector(distance_vector, current_neighbor);

                if(is_updated) {
                    heap_push(heap, current_neighbor);
                }
            }

            //FIXME
            // heap_print(heap);
        }

    //FIXME
    }

    // for (int i = 0; i < 6; i++) {
    //     printf("Distance index %d: ", i);
    //     for (int j = 0; j < 2; j++) {
    //         printf("%d ", distance_vector[i][j]);
    //     }
    //     printf("\n");
    // }

    return distance_vector;
}

int main() {

    Graph graph = graph_create();
    Graph *p_graph = &graph;
    Graph **p_p_graph = &p_graph;
    int graph_size = 6;

    graph_init_vertices(p_graph, graph_size);
    graph_djikstra_set_weights(p_graph);

    Graph_vertice *start = graph_get_vertice(p_graph, 0);
    int **distance_vector = graph_djikstra(p_graph, start);

    //get shortest path from node 0 to node 5
    Graph_vertice *finish = graph_get_vertice(p_graph, 5);

    graph_djikstra_backtrack(p_graph, distance_vector, start, finish);

    graph_free(p_p_graph);

    return 0;
}

/*
TODO
cleaning up
*/