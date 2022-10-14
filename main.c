#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "graph.h"
#include "rule.h"

// this function creates the graph by reading the Makefile
dependencieGraph_t *create_graph() {
  int cpt;
  char file_name[] = "Makefile";
  char *line;

  rule_t *rule;
  char *token, *target, *dependancie;
  dependencieGraph_t *g = new_dependencie_graph();
  size_t len = 0;

  FILE *makefile = fopen(file_name, "r");
  if (makefile == NULL) {
    printf("le fichier %s n'a pas pu s'ouvrir \n", file_name);
  } else {

    // go through the lines of the Makefile
    while (getline(&line, &len, makefile) != EOF) {

      if (line[0] == '\t') {
        // '\t' at the beginning of the line the we add a command to the current
        // rule
        char *command = malloc((strlen(line + 1) + 1) * sizeof(char));
        strcpy(command, line + 1);
        add_command(rule, command);

      } else if (line[0] != '\n') {
        // not '\t' at the beginning of the line the we add a new rule
        rule = new_rule();

        // store in the graph the new rule
        add_node(g, rule);

        // split the line to access the target and the dependancies
        cpt = 0;
        token = strtok(line, " :\t");
        while (token != NULL) {
          if (cpt == 0) {
            // set the target
            char *target = malloc((strlen(token) + 1) * sizeof(char));
            strcpy(target, token);
            rule->target = token;
          } else {
            // set the dependencies
            char *dependancie = malloc((strlen(token) + 1) * sizeof(char));
            strcpy(dependancie, token);
            add_dependencie(rule, token);
          }
          token = strtok(NULL, " :\t");
          cpt++;
        }
      }
    }
    printf("\n");
  }
  return g;
}

/*
neighbours_checked : checks whether all neighbours have been checked thus the
corresponding rule has already bean made
  - returns EXIT_SUCCESS if all neighbours of node 'id' were checked
  - EXIT_FAILURE otherwise
*/
int neighbours_checked(dependencieGraph_t *graph, char *checked, int id) {
  for (int i = 0; i < graph->numberOfNeighbours[id]; i++) {
    if (!checked[graph->neighbours[id][i]])
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
make : makes a target depending on the parameter passed into target. If target
is NULL it takes the first rule it encountered as the target to make
  - returns EXIT_FAILURE if anything went wrong
  - EXIT_SUCCESS otherwise, meaning the rule as been made and everything went
fine
*/
int make(dependencieGraph_t *graph, char *target, char *checked) {
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

      if (!checked[currentNeighbour]) {
        make(graph, graph->nodes[currentNeighbour]->target, checked);

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
  dependencieGraph_t *graph = create_graph();
  compute_neighbours(graph);

  char *checked;

  if (!(checked = malloc(graph->numberOfNodes * sizeof(char)))) {
    debug_error("main", "Couldn't allocate memory for checked\n");

    delete_dependencie_graph(graph);

    return EXIT_FAILURE;
  }

  // we're supposing there are no options to our mymake tool
  if (argc > 1) { // if one (or more) target(s) is(are) specified
    for (int i = 1; i < argc; i++) {
      memset(checked, 0, graph->numberOfNodes);
      make(graph, argv[i], checked);
    }
  } else {
    make(graph, NULL, checked);
  }

  return EXIT_SUCCESS;
}
