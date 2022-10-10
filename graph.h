#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "rule.h"

typedef struct dependencieGraph {
    rule_t **rules;
} dependencieGraph;

#endif