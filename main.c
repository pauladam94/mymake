#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "graph.h"
#include "rule.h"

dependencyGraph_t *create_graph() {
  int cpt;
  char file_name[] = "Makefile";
  char *line;
  size_t len = 0;

  rule_t *rule;
  char *token, *target, *dependency, *command;
  dependencyGraph_t *g = new_dependency_graph();

  if(!g) {
    debug_error("create_graph", "Couldn't create new graph\n");

    return NULL;
  }

  FILE *makefile = fopen(file_name, "r");

  if (makefile == NULL) {
    debug_error("create_graph", "Le fichier '%s' n'a pas pu s'ouvrir \n", file_name);

    delete_dependency_graph(g);

    return NULL;
  } else {

    // go through the lines of the Makefile
    while (getline(&line, &len, makefile) != EOF) {

      if (line[0] == '\t') {
        // '\t' at the beginning of the line the we add a command to the current
        // rule

        int i = 0;
        while(line[++i] == '\t'); // skips every tab

        if(!(command = malloc((len - i) * sizeof(char)))) {
          debug_error("create_graph", "Couldn't allocate memory for a new command\n(Command : %s)\n", line + i);

          delete_dependency_graph(g);

          return NULL;
        }

        strcpy(command, line + i);

        printf("\t'%s'\n", command);

        add_command(rule, command);

      } else if (line[0] != '\n') {
        // not '\t' at the beginning of the line the we add a new rule
        rule = new_rule();

        // store in the graph the new rule
        if(add_node(g, rule) == -1) {
          debug_error("create_graph", "Ambiguous rule for target '%s'. Rule already defined before in Makefile\n", rule->target);

          delete_dependency_graph(g);
          delete_rule(rule);

          return NULL;
        }

        // split the line to access the target and the dependancies
        cpt = 0;
        token = strtok(line, " :\t\n");

        while (token != NULL) {
          if (cpt == 0) {
            // set the target
            if(!(target = malloc((strlen(token) + 1) * sizeof(char)))) {
              debug_error("create_graph", "Couldn't allocate memory for a new target\n");

              delete_dependency_graph(g);

              return NULL;
            }

            strcpy(target, token);
            
            printf("'%s': ", target);

            rule->target = target;
          } else {
            // set the dependencies
            if(!(dependency = malloc((strlen(token) + 1) * sizeof(char)))) {
              debug_error("create_graph", "Couldn't allocate memory for a new dependecy");

              delete_dependency_graph(g);

              return NULL;
            }

            strcpy(dependency, token);

            printf("'%s' ", dependency);

            add_dependency(rule, dependency);
          }

          token = strtok(NULL, " :\t\n");

          cpt++;
        }

        printf("\n");
      }
    }
  }

  return g;
}

/*
is_cyclic : checks wheter the sub-graph accessible from node with id 'id' contains a cycle
  - returns 1 if it does
  - 0 otherwise
*/
char is_cyclic(dependencyGraph_t *graph, int id, char *checked, char *stack) {
  if(!checked[id]) {
    checked[id] = 1;
    stack[id] = 1;

    for(int i = 0; i < graph->numberOfNeighbours[id]; i++) {
      int currentId = graph->neighbours[id][i];

      if(!checked[currentId] && is_cyclic(graph, currentId, checked, stack)) {
        return 1;
      } else if(stack[currentId]) {
        return 1;
      }
    }
  }

  stack[id] = 0;

  return 0;
}

/*
neighbours_checked : checks whether all neighbours have been checked thus the corresponding rule has already bean made
  - returns EXIT_SUCCESS if all neighbours of node 'id' were checked
  - EXIT_FAILURE otherwise
*/
int neighbours_checked(dependencyGraph_t *graph, char *checked, int id) {
  for(int i = 0; i < graph->numberOfNeighbours[id]; i++) {
    if(!checked[graph->neighbours[id][i]])
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
make : makes a target depending on the parameter passed into target. If target
is NULL it takes the first rule it encountered as the target to make
  - returns EXIT_FAILURE if anything went wrong
  - EXIT_SUCCESS otherwise, meaning the rule has been made and everything went well
*/
int make_naive(dependencyGraph_t *graph, char *target, char *checked) {
  int id = 0;

  if (target) {
    id = contains_rule(graph, target);

    if (id == -1) {
      debug_error("make", "Couldn't find rule for target '%s'\n", target);

      return EXIT_FAILURE;
    }
  }

  if (neighbours_checked(graph, checked, id)) {
    for (int i = 0; i < graph->numberOfNeighbours[id]; i++) {
      int currentNeighbour = graph->neighbours[id][i];

      if(!checked[currentNeighbour]) {
        if(make_naive(graph, graph->nodes[currentNeighbour]->target, checked)) {
          return EXIT_FAILURE;
        }

        checked[currentNeighbour] = 1;
      }
    }
  }

  list_t *currentCommand = graph->nodes[id]->commands;

  while (currentCommand) {
    // system(currentCommand->content);
    printf(" - %s\n", currentCommand->content);

    currentCommand = currentCommand->next;
  }

  return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
  dependencyGraph_t *graph = create_graph();
  
  if(!graph) {
    debug_error("main", "create_graph returned with error(s)\n");

    return EXIT_FAILURE;
  }

  display_graph(graph);

  if(compute_neighbours(graph)) {
    debug_error("main", "compute_neighbours was aborted\n");

    delete_dependency_graph(graph);

    return EXIT_FAILURE;
  }
  /*
  char *checked;
  char *stack;

  if(!(checked = malloc(graph->numberOfNodes * sizeof(char)))) {
    debug_error("main", "Couldn't allocate memory for 'checked'\n");

    delete_dependency_graph(graph);

    return EXIT_FAILURE;
  }

  if(!(stack = malloc(graph->numberOfNodes * sizeof(char)))) {
    debug_error("main", "Couldn't allocate memory for 'stack'\n");

    delete_dependency_graph(graph);

    free(checked);

    return EXIT_FAILURE;
  }

  // we're supposing there are no options to our mymake tool
  if(argc > 1) { // if one (or more) target(s) is(are) specified
    for(int i = 1; i < argc; i++) {
      if(contains_rule(graph, argv[i]) == -1) {
        debug_error("main", "Warning : the target '%s' doesn't exist\n", argv[i]);
      } else {
        memset(checked, 0, graph->numberOfNodes);
        memset(stack, 0, graph->numberOfNodes);

        if(is_cyclic(graph, contains_rule(graph, argv[i]), checked, stack)) {
          debug_error("main", "Couldn't make target '%s' as the corresponding dependency graph contains a cycle\n", argv[i]);

          delete_dependency_graph(graph);

          free(checked);
          free(stack);

          return EXIT_FAILURE;
        }

        memset(checked, 0, graph->numberOfNodes);

        make_naive(graph, argv[i], checked);
      }
    }
  } else {
    memset(checked, 0, graph->numberOfNodes);
    memset(stack, 0, graph->numberOfNodes);

    if(is_cyclic(graph, 0, checked, stack)) {
      debug_error("main", "Couldn't make target '%s' as the corresponding dependency graph contains a cycle\n", graph->nodes[0]->target);

      delete_dependency_graph(graph);

      free(checked);
      free(stack);

      return EXIT_FAILURE;
    }

    make_naive(graph, NULL, checked);
  }*/

  delete_dependency_graph(graph);
  /*
  free(checked);
  free(stack);
  */
  return EXIT_SUCCESS;
}
