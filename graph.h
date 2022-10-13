#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef rule_t node_t;

typedef struct dependencieGraph_t {
    int numberOfNodes;

    node_t **nodes;
    int *neighbours;
} dependencieGraph_t;

dependencieGraph_t *new_dependencie_graph(void);
void delete_dependencie_graph(dependencieGraph_t *);
void compute_neighbours(dependencieGraph_t *, rule_t *);
int add_node(dependencieGraph_t *, rule_t *);

#endif