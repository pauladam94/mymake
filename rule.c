#include <stdlib.h>

#include "rule.h"
#include "debug.h"

static int ruleNumber = 0;
/*
new_list :
    - returns the address of the newly allocated list_t object
*/
list_t *new_list(void) {
    list_t *list = malloc(sizeof(list_t));

    if(!list) {
        debug_error("new_list", "Couldn't allocate memory for a new list\n");

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
    if(list) {
        list_t *current = list->next;
        
        if(current) {
            delete_list(current);
        }

        free(list->content);
        free(list);
    }
}

/*
add_element_in_list : adds a new element at the end of a linked list
    - returns EXIT_FAILURE if anything failed
    - EXIT_SUCCESS otherwise
*/
int add_element_in_list(list_t *list, char *content) {
    if(list->next) { // if not the last element
        return add_element_in_list(list->next, content);
    } else {
        list_t *newElement = list;

        if(list->content) { // if the first element is not the last one
            if(!(newElement = new_list())) {
                return EXIT_FAILURE;
            }

            list->next = newElement;
        }

        newElement->content = content;
    }

    return EXIT_SUCCESS;
}

/*
new_rule : 
    - returns the address of the newly allocated rule
    - or NULL if anything failed
*/
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

/*
delete_rule : deallocate memory for a given rule
*/
void delete_rule(rule_t *rule) {
    delete_list(rule->dependencies);
    delete_list(rule->commands);

    free(rule->target);
    free(rule);

    ruleNumber--;
}

/*
add_dependency : abstraction of adding a dependency in the linked list of dependencies in a rule
*/
void add_dependency(rule_t *rule, char *dependency) {
    add_element_in_list(rule->dependencies, dependency);
}

/*
add_command : abstraction of adding a command in the linked list of commands in a rule
*/
void add_command(rule_t *rule, char *command) {
    add_element_in_list(rule->commands, command);
}