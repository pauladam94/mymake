#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef struct node_t {
    rule_t rule;
    struct node_t **neighbours;
} node_t;

typedef struct dependencieGraph_t {
    int numberOfNodes;
    node_t **nodes;
} dependencieGraph_t;

#endif