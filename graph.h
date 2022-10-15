#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef rule_t node_t; // alias for understanding purposes

/*
dependencyGraph_t :
    - numberOfNodes : the number of nodes the graph contains
    - nodes : an array containing the address of every node
    - numberOfNeighbour : an array containing the number of neighbours for each node
    - neighbours : neighbours[i] contains an array of id of all the neighbours of node[i]
*/
typedef struct dependencyGraph_t {
    int numberOfNodes;
    node_t **nodes;

    int *numberOfNeighbours;
    int **neighbours;
} dependencyGraph_t;

dependencyGraph_t *new_dependency_graph(void);
void delete_dependency_graph(dependencyGraph_t *);
int contains_rule(dependencyGraph_t *, char *);
int compute_neighbours(dependencyGraph_t *);
int add_node(dependencyGraph_t *, rule_t *);
void display_graph(dependencyGraph_t *, char);

#endif