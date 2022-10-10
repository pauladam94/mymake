#include <stdlib.h>
#include <stdio.h>

#include "graph.h"
#include "debug.h"

dependencieGraph *new_dependencie_graph(void) {
    dependencieGraph *graph = malloc(sizeof(dependencieGraph));

    if(!graph) {
        debug_error("new_dependencie_graph", "Couldn't allocate memory for 'dependencieGraph'\n");
        return NULL;
    }

    graph->rules = NULL;

    return graph;
}

