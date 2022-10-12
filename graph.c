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

    graph->nodes = NULL;

    return graph;
}

void delete_dependencie_graph(dependencieGraph_t *graph) {
    
}

node_t *new_node(void) {
    node_t *node;
    
    if(!(node = malloc(sizeof(node_t)))) {
        debug_error("new_node", "Couldn't allocate memory for new node\n");
        return NULL;
    }

    node->rule = NULL;
    
    if(!(node->neighbours = malloc(sizeof(nl_t))))
}

int compute_neighbours(node_t *node, rule_t *rule) {
    list_t *currentDependencie = rule->dependencies;
    while(rule->dependencies)

    return EXIT_SUCCESS;
}

/*
add_rule : adds a new rule into a dependencie graph
    - returns -1 if already in the graph
*/
int add_rule(dependencieGraph_t *graph, rule_t *rule) {
    node_list_t *currentNodes = graph->nodes;

    while(currentNodes->next) { // check wheter 'rule' already exists in the dependencie graph
        if(!strcmp(currentNodes->current->target, rule->target)) {
            return -1;
        }

        currentNodes = currentNodes->next;
    }

    node_t *newNode = malloc(sizeof(node_t));
    
    if(!newNode) {
        debug_error("add_rule", "Couldn't allocate memory for 'newNode'\n");
        return EXIT_FAILURE;
    }

    newNode->rule = rule;
    if(compute_neighbours(currentNodes, rule)) {
        debug_error("add_rule", "Couldn't compute neighbours for rule '%s'\n", rule->target);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

