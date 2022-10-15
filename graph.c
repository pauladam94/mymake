#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "graph.h"
#include "debug.h"

/*
new_dependency_graph : 
    - returns a new empty dependency graph
    - or NULL if there is any error
*/
dependencyGraph_t *new_dependency_graph(void) {
    dependencyGraph_t *graph = malloc(sizeof(dependencyGraph_t));

    if(!graph) {
        debug_error("new_dependency_graph", "Couldn't allocate memory for a new dependency graph\n");
        return NULL;
    }

    graph->numberOfNodes = 0;
    graph->nodes = NULL;
    graph->numberOfNeighbours = NULL;
    graph->neighbours = NULL;

    return graph;
}

/*
delete_dependency_graph : given a graph, it frees all the memory allocated previously for this graph
*/
void delete_dependency_graph(dependencyGraph_t *graph) {
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
contains_rule : checks whether a rule with target 'target' is alread a node in the dependency graph 'graph'
    - returns rule->id if found
    - -1 otherwise
*/
int contains_rule(dependencyGraph_t *graph, char *target) {
    if(target) {
        for(int i = 0; i < graph->numberOfNodes; i++) {
            if(!strcmp(graph->nodes[i]->target, target)) {
                return i; // could theoriticaly be graph->nodes[i]->id
            }
        }
    }

    return -1;
}

/*
compute_neighbours : given a dependency graph, it computes all neighbours, thus constructing the dependencies structure
    - returns EXIT_FAILURE if anything fails
    - or EXIT_SUCCESS otherwise
*/
int compute_neighbours(dependencyGraph_t *graph) {
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
        list_t *currentDependency = graph->nodes[i]->dependencies;

        while(currentDependency && currentDependency->content) {
            int rule_id;

            if((rule_id = contains_rule(graph, currentDependency->content)) != -1) {
                if(!(graph->neighbours[i] = realloc(graph->neighbours[i], (graph->numberOfNeighbours[i] + 1) * sizeof(int)))) {
                    debug_error("compute_neighbours", "Couldn't allocate memory for new neighbour for rule '%s'\n", graph->nodes[i]->target);

                    return EXIT_FAILURE;
                }

                graph->neighbours[i][(graph->numberOfNeighbours[i])++] = rule_id;
            } else {
                FILE *f;
                if(!(f = fopen(currentDependency->content, "r"))) {
                    debug_error("compute_neighbours", "Target '%s' is invalid as there is no such file\n", currentDependency->content);

                    return EXIT_FAILURE;
                } else {
                    fclose(f);
                }
            }

            currentDependency = currentDependency->next;
        }
    }

    return EXIT_SUCCESS;
}

/*
add_node : adds a new rule as a node into a dependency graph
    - returns -1 if already in the graph
*/
int add_node(dependencyGraph_t *graph, rule_t *rule) {
    graph->nodes = realloc(graph->nodes, (graph->numberOfNodes + 1) * sizeof(node_t *));

    if(!graph->nodes) {
        debug_error("add_node", "Couldn't allocate memory for new node\n");

        delete_dependency_graph(graph);

        return EXIT_FAILURE;
    }

    graph->nodes[graph->numberOfNodes++] = rule;

    return EXIT_SUCCESS;
}

void display_graph(dependencyGraph_t *graph, char option) {
    list_t *currentCommand;
    list_t *currentDependency;

    for(int i = 0; i < graph->numberOfNodes; i++) {
        printf("%s: ", graph->nodes[i]->target);

        if(!option){
            currentDependency = graph->nodes[i]->dependencies;

            while(currentDependency) {
                printf("%s ", currentDependency->content);

                currentDependency = currentDependency->next;
            }

            printf("\n");

            currentCommand = graph->nodes[i]->commands;

            while(currentCommand) {
                printf("\t%s\n", currentCommand->content);

                currentCommand = currentCommand->next;
            }
        } else {
            for(int j = 0; j < graph->numberOfNeighbours[i]; j++) {
                printf("%s ", graph->nodes[graph->neighbours[i][j]]->target);
            }

            printf("\n");

            currentCommand = graph->nodes[i]->commands;

            while(currentCommand) {
                printf("\t%s\n", currentCommand->content);

                currentCommand = currentCommand->next;
            }
        }
    }
}