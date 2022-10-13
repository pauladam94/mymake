#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "debug.h"

dependencieGraph_t *new_dependencie_graph(void) {
    dependencieGraph_t *graph = malloc(sizeof(dependencieGraph_t));

    if(!graph) {
        debug_error("new_dependencie_graph", "Couldn't allocate memory for 'dependencieGraph'\n");
        return NULL;
    }

    graph->numberOfNodes = 0;
    graph->nodes = NULL;
    graph->neighbours = NULL;

    return graph;
}

void delete_dependencie_graph(dependencieGraph_t *graph) {
    for(int i = 0; i < graph->numberOfNodes; i++) {
        delete_rule(graph->nodes[i]);
    }

    free(graph->nodes);
    free(graph->neighbours);
    free(graph);
}

void compute_neighbours(dependencieGraph_t *graph, rule_t *rule) {
    for(int i = 0; i < graph->numberOfNodes; i++) {
        
    }
}

/*
add_node : adds a new rule as a node into a dependencie graph
    - returns -1 if already in the graph
*/
int add_node(dependencieGraph_t *graph, rule_t *rule) {
    graph->nodes = realloc(graph->nodes, (graph->numberOfNodes + 1) * sizeof(node_t *));

    if(!graph->nodes) {
        debug_error("add_node", "Couldn't allocate memory for new node\n");

        delete_dependencie_graph(graph);

        return EXIT_FAILURE;
    }

    graph->nodes[graph->numberOfNodes++] = rule;

    return EXIT_SUCCESS;
}

