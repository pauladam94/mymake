#ifndef __RULE_H__
#define __RULE_H__

typedef struct list_t {
    char *content;

    struct list_t *next;
} list_t;

typedef struct {
    char *target;
    list_t *dependencies;
    list_t *commands;
} rule_t;

list_t *new_list(void);
void delete_list(list_t *);
int add_element_in_list(list_t *, char *);
rule_t *new_rule(void);
void delete_rule(rule_t *);
void add_dependencie(rule_t *, char *);
void add_command(rule_t *, char *);

#endif