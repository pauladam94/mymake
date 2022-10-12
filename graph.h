#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef struct node_t {
    rule_t *rule;
    struct nl_t {
        struct node_t *node;
        struct nl_t *next;
    } *neighbours;
} node_t;

typedef struct node_list_t {
    node_t *current;
    struct node_list_t *next;
} node_list_t;

typedef struct dependencieGraph_t {
    int numberOfNodes;
    node_list_t *nodes;
} dependencieGraph_t;

#endif