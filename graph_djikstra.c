#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define INIT_DISTANCE 100

void graph_djikstra_set_weights(Graph*);
static int** graph_djikstra_init_distance_vector(Graph*, Graph_vertice*);
int graph_djikstra(Graph*, Graph_vertice*); //FIXME to return the length of shortest path and shortest path in itself


void graph_djikstra_set_weights(Graph* self) {
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

static int** graph_djikstra_init_distance_vector(Graph* self, Graph_vertice* start) {
    int key = start->index;
    GList* indexes = g_hash_table_get_keys(self->vertices_table);

    int indexes_number = g_list_length(indexes); //external array
    int priority_key_size = 2; // Fixed size of each inner array

    // Allocate memory for the outer array
    int **distance_vector = malloc(indexes_number * sizeof(int *));
    if (distance_vector == NULL) {
        perror("Failed to allocate memory for outer array");
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

    // Example usage: print the contents of the dynamic array
    for (int i = 0; i < indexes_number; i++) {
        printf("Priority key %d: ", i);
        for (int j = 0; j < priority_key_size; j++) {
            printf("%d ", distance_vector[i][j]);
        }
        printf("\n");
    }

    return distance_vector;
}


int graph_djikstra(Graph* self, Graph_vertice* start) {
    /*
    the shortest path to node 5 is 8 in this example:
    0 -(4)> 2 -(1)> 4 -(3)> 5 = 4+1+3 = 8
    */

    int **distance_vector = graph_djikstra_init_distance_vector(self, start);

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
