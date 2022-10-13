#ifndef __RULE_H__
#define __RULE_H__

/*
list_t :
    - content : the content/description of the current element
    - next : the address of the next cell in the linked list (NULL if current is last)
*/
typedef struct list_t {
    char *content;

    struct list_t *next;
} list_t;

/*
rule_t :
    - id : self explanatory
    - target : self explanatory
    - dependencies : a linked list of all the dependencies required to make target
    - commands : a linked list of all the commands to execute to make target
*/
typedef struct {
    int id;

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