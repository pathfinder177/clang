#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graph.h"
#include "graph_djikstra_heap.h"

#define INIT_DISTANCE 100

void graph_djikstra_set_weights(Graph *);
static int** graph_djikstra_init_distance_vector(Graph *, Graph_vertice *);
static bool graph_djikstra_update_distance_vector(int **, int *);
static int graph_djikstra_get_weight_distance_vector(int **, int);
int graph_djikstra(Graph*, Graph_vertice *); //FIXME to return the length of shortest path and shortest path in itself


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

static int** graph_djikstra_init_distance_vector(Graph *self, Graph_vertice *start) {
    int priority_key_size = 2; // Fixed size of each inner array FIXME
    int key = start->index;

    GList* indexes = g_hash_table_get_keys(self->vertices_table);
    int indexes_number = g_list_length(indexes); //external array

    // Allocate memory for the outer array
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
    for (int i = 0; i < indexes_number; i++) {
        printf("Priority key %d: ", i);
        for (int j = 0; j < priority_key_size; j++) {
            printf("%d ", distance_vector[i][j]);
        }
        printf("\n");
    }

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

int graph_djikstra(Graph* self, Graph_vertice* start) {
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

    for (int i = 0; i < 6; i++) {
        printf("Distance index %d: ", i);
        for (int j = 0; j < 2; j++) {
            printf("%d ", distance_vector[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main() {

    Graph graph = graph_create();
    Graph *p_graph = &graph;
    Graph **p_p_graph = &p_graph;
    int graph_size = 6;

    graph_init_vertices(p_graph, graph_size);
    graph_djikstra_set_weights(p_graph);

    Graph_vertice *start = graph_get_vertice(p_graph, 0);
    graph_djikstra(p_graph, start);

    // graph_list(p_graph);

    graph_free(p_p_graph);

    return 0;
}
