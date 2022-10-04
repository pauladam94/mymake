#ifndef __RULE_H__
#define __RULE_H__

typedef struct {
    char *target;
    char **prerequisites;
    char *commands[];
} rule_t;

rule_t *new_rule(void);
void delete_rule(rule_t *);

#endif