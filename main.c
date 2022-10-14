#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "rule.h"

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

int main(int argc, char *argv[]) {
  // 1. étape création du graphe

  // 2. étape vétification de cycle

  // 3. étape exécution des lignes en fonction des dates de sauvegardes

}
