#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "debug.h"

/*
new_dependencie_graph : 
    - returns a new empty dependencie graph
    - or NULL if there is any error
*/
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

/*
delete_dependencie_graph : given a graph, it frees all the memory allocated previously for this graph
*/
void delete_dependencie_graph(dependencieGraph_t *graph) {
    for(int i = 0; i < graph->numberOfNodes; i++) {
        delete_rule(graph->nodes[graph->numberOfNodes - i - 1]); // not the other way around for logical purposes

        free(graph->neighbours[i]);
    }

    free(graph->nodes);
    free(graph->neighbours);
    free(graph->numberOfNeighbours);
    free(graph);
}

/*
contains_rule : checks whether a rule with target 'target' is alread a node in the dependencie graph 'graph'
    - returns rule->id if found
    - -1 otherwise
*/
int contains_rule(dependencieGraph_t *graph, char *target) {
    for(int i = 0; i < graph->numberOfNodes; i++) {
        if(!strcmp(graph->nodes[i]->target, target)) {
            return graph->nodes[i]->id;
        }
    }

    return -1;
}

/*
compute_neighbours : given a dependencie graph, it computes all neighbours, thus constructing the dependencie structure
    - returns EXIT_FAILURE if anything fails
    - or EXIT_SUCCESS otherwise
*/
int compute_neighbours(dependencieGraph_t *graph) {
    if(!(graph->numberOfNeighbours = malloc(graph->numberOfNodes * sizeof(int)))) {
        debug_error("compute_neighbours", "Couldn't allocate memory for 'graph->numberOfNeighbours'\n");

        return EXIT_FAILURE;
    }

    memset(graph->numberOfNeighbours, 0, graph->numberOfNodes);

    if(!(graph->neighbours = malloc(graph->numberOfNodes * sizeof(int *)))) {
        debug_error("compute_neighbours", "Couldn't allocate memory for 'graph->neighbours'\n");

        return EXIT_FAILURE;
    }

    for(int i = 0; i < graph->numberOfNodes; i++) {
        list_t *currentDependencie = graph->nodes[i]->dependencies;

        while(currentDependencie) {
            int rule_id;

            if((rule_id = contains_rule(graph, currentDependencie->content)) != -1) {
                if(!(graph->neighbours[i] = realloc(graph->neighbours[i], (graph->numberOfNeighbours[i] + 1) * sizeof(int)))) {
                    debug_error("compute_neighbours", "Couldn't allocate memory for new neighbour for rule '%s'\n", graph->nodes[i]->target);

                    return EXIT_FAILURE;
                }

                graph->neighbours[i][(graph->numberOfNeighbours[i])++] = rule_id;
            } else {
                FILE *f;
                if(!(f = fopen(currentDependencie->content, "r"))) {
                    debug_error("compute_neighbours", "Target '%s' is invalid as there is no such file\n", currentDependencie->content);

                    return EXIT_FAILURE;
                } else {
                    fclose(f);
                }
            }

            currentDependencie = currentDependencie->next;
        }
    }

    return EXIT_SUCCESS;
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

