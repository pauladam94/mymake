#include <stdlib.h>
#include "rule.h"

rule_t *new_rule(void) {
    rule_t *rule;

    return rule;
}

void delete_rule(rule_t *rule) {
    free(rule->target);
    free(rule->prerequisites);
    free(rule->commands);
}