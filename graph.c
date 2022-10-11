#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "debug.h"

dependencieGraph_t *new_dependencie_graph(void) {
    dependencieGraph_t *graph = malloc(sizeof(dependencieGraph_t));

    if(!graph) {
        debug_error("new_dependencie_graph", "Couldn't allocate memory for 'dependencieGraph'\n");
        return NULL;
    }

    graph->nodes = NULL;

    return graph;
}

void delete_dependencie_graph(dependencieGraph_t *graph) {
    
}

int add_rule(dependencieGraph_t *graph, rule_t *rule) {
    
}

