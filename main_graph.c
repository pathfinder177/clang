#include "graph.h"

int main() {
    Graph graph = graph_create();
    Graph *p_graph = &graph;
    Graph **p_p_graph = &p_graph;
    int graph_size = 7;

    graph_init_vertices(p_graph, graph_size);

    //0,1,2,4,5
    graph_erase_vertice(p_graph, 3);

    graph_list(p_graph);

    //pointer to vertice with index 1
    Graph_vertice *v_1 = graph_get_vertice(p_graph, 1);

    //added 1 -> 2 with weight 4
    graph_add_edge(p_graph, 1, 2, 4);

    //abort: this graph is not a multigraph
    // graph_add_edge(p_graph, 2, 1, 4);

    //0,1,4,5
    graph_erase_vertice(p_graph, 2);

    // bool is_edge_erased = graph_erase_edge(p_graph, 1, 2);

    graph_list(p_graph);

    graph_free(p_p_graph);

    return 0;
}