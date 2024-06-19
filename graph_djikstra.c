#include <stdio.h>
#include "graph.h"

#define INIT_DISTANCE 100

void graph_djikstra_set_weights(Graph*);
static int*** graph_djikstra_init_distance_vector(Graph*, Graph_vertice*, int);
int graph_djikstra(Graph*, Graph_vertice*, int); //FIXME to return the length of shortest path and shortest path in itself


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

static int*** graph_djikstra_init_distance_vector(Graph* self, Graph_vertice* start, int graph_size) {
    int ROWS = 1;
    int COLS = graph_size;
    int INNER_ARRAY_SIZE = 2;

    int ***distance_vector = (int ***)malloc(ROWS * sizeof(int **));
    for (int i = 0; i < ROWS; i++) {
        distance_vector[i] = (int **)malloc(COLS * sizeof(int *));
        for (int j = 0; j < COLS; j++) {
            distance_vector[i][j] = (int *)malloc(INNER_ARRAY_SIZE * sizeof(int));
        }
    }

    // Initialize the distance_vector with some values
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            for (int k = 0; k < INNER_ARRAY_SIZE; k++) {
                distance_vector[i][j][k] = i * COLS * INNER_ARRAY_SIZE + j * INNER_ARRAY_SIZE + k;
            }
        }
    }

    // Print the distance_vector
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("distance_vector[%d][%d]: ", i, j);
            for (int k = 0; k < INNER_ARRAY_SIZE; k++) {
                printf("%d ", distance_vector[i][j][k]);
            }
            printf("\n");
        }
    }

    return distance_vector;
}

int graph_djikstra(Graph* self, Graph_vertice* start, int graph_size) {
    /*
    the shortest path to node 5 is 8 in this example:
    0 -(4)> 2 -(1)> 4 -(3)> 5 = 4+1+3 = 8
    */

    int ***distance_vector = graph_djikstra_init_distance_vector(self, start, graph_size);

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
    graph_djikstra(p_graph, start, graph_size);

    // graph_list(p_graph);

    graph_free(p_p_graph);

    return 0;
}
