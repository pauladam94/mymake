#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef rule_t node_t; // alias for understanding purposes

/*
dependencieGraph_t :
    - numberOfNodes : the number of node the graph contains
    - nodes : an array containing the address of every node
    - numberOfNeighbour : an array containing the number of neighbour for each node
    - neighbours : neighbours[i] contains an array of id of all the neighbours of node[i]
*/
typedef struct dependencieGraph_t {
    int numberOfNodes;
    node_t **nodes;

    int *numberOfNeighbours;
    int **neighbours;
} dependencieGraph_t;

dependencieGraph_t *new_dependencie_graph(void);
void delete_dependencie_graph(dependencieGraph_t *);
int compute_neighbours(dependencieGraph_t *);
int add_node(dependencieGraph_t *, rule_t *);

#endif