#include <stdlib.h>

#include "rule.h"
#include "debug.h"

static int ruleNumber = 0;
/*
new_list : allocates a new list_t
*/
list_t *new_list(void) {
    list_t *list = malloc(sizeof(list_t));

    if(!list) {
        debug_error("new_list", "Couldn't allocate memory for 'list'\n");
        return NULL;
    }

    list->content = NULL;
    list->next = NULL;

    return list;
}

/*
delete_list : frees every element of the list and then frees the list
*/
void delete_list(list_t *list) {
    while(list->next) {
        delete_list(list->next);

        free(list->next);
    }

    free(list);
}

/*
add_element_in_list : adds a new element at the end of a chained list
*/
int add_element_in_list(list_t *list, char *content) {
    list_t *elem = new_list();

    if(!elem) {
        return EXIT_FAILURE;
    }

    list_t *current = list;

    elem->content = content;

    while(current->next) {
        current = current->next;
    }

    current->next = elem;

    return EXIT_SUCCESS;
}

rule_t *new_rule(void) {
    rule_t *rule = malloc(sizeof(rule_t));

    if(!rule) {
        debug_error("new_rule", "Couldn't allocate memory for 'rule'\n");
        return NULL;
    }

    rule->target = NULL;
    rule->dependencies = new_list();

    if(!rule->dependencies) {
        delete_rule(rule);
        return NULL;
    }

    rule->commands = new_list();

    if(!rule->commands) {
        delete_rule(rule);
        return NULL;
    }

    rule->id = ruleNumber++;

    return rule;
}

void delete_rule(rule_t *rule) {
    free(rule->target);
    delete_list(rule->dependencies);
    delete_list(rule->commands);

    free(rule);

    ruleNumber--;
}

void add_dependencie(rule_t *rule, char *dependencie) {
    add_element_in_list(rule->dependencies, dependencie);
}

void add_command(rule_t *rule, char *command) {
    add_element_in_list(rule->commands, command);
}