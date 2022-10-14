#include <stdio.h>
#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
#include "debug.h"
#include "graph.h"
#include "rule.h"

dependencieGraph_t *create_graph(void);

/*
neighbours_checked : checks whether all neighbours have been checked thus the corresponding rule has already bean made
  - returns EXIT_SUCCESS if all neighbours of node 'id' were checked
  - EXIT_FAILURE otherwise
*/
int neighbours_checked(dependencieGraph_t *graph, char *checked, int id) {
  for(int i = 0; i < graph->numberOfNeighbours[id]; i++) {
    if(!checked[graph->neighbours[id][i]])
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

/*
make : makes a target depending on the parameter passed into target. If target is NULL it takes the first rule it encountered as the target to make
  - returns EXIT_FAILURE if anything went wrong
  - EXIT_SUCCESS otherwise, meaning the rule as been made and everything went fine
*/
int make(dependencieGraph_t *graph, char *target, char *checked) {
  int id = 0;
=======
#include "graph.h"
#include "rule.h"

dependencieGraph_t *create_graph() {
  int cpt;
  char file_name[] = "Makefile";
  char *line;
  char *token1;
  char *token2;
  char *target;

  rule_t *rule;
  size_t len = 0;
  dependencieGraph_t *g = new_dependencie_graph();

  FILE *makefile = fopen(file_name, "r");
  if (makefile == NULL) {
    printf("le fichier %s n'a pas pu s'ouvrir \n", file_name);
  } else {

    // parcours des lignes
    while (getline(&line, &len, makefile) != EOF) {

      if (line[0] == '\t') {
        // '\t' en début de ligne alors traitement de la commande pour la règle
        // en cours
        char *command = malloc((strlen(line + 1) + 1) * sizeof(char));
        strcpy(command, line + 1);
        add_command(rule, command);

      } else if (line[0] != '\n') {
        // pas de '\t' en début de ligne
        // nouvelle règle
        rule = new_rule();

        // stocke dans le graphe la nouvelle règle
        add_node(g, rule);

        // séparation par ' : ' pour avoir le nom de la règle
        cpt = 0;
        token1 = strtok(line, " ");
        while (token1 != NULL) {
          if (cpt == 0) {
            // alors on définit le nom de la target
            rule->target = token1;
          } else {

            // la suite sont les dépendances
            token2 = strtok(line + 1, " ");
            while (token2 != NULL) {
              // ajoute la dépendance à la règle
              add_dependencie(rule, token2);
              token2 = strtok(line, " ");
            }
          }
          token1 = strtok(NULL, " ");
        }
        // séparation par ' ' pour avoir les dépendances
      }

      // stocke rule
    }
    printf("\n");
  }
  return g;
}

// Pseudo Code Vérification de cycle naïve
/*
// renvoie false si le parcours à partir de init ne repasse pas par init
let parcours_profondeur (init:sommet) : bool =
  file vu =[s];
  while (vu != 0){
  }
>>>>>>> 4116890943256601bd7663be26baa4d44a7bc616

  if(target) {
    id = contains_rule(graph, target);

    if(id == -1) {
      debug_error("make", "Couldn't find rule for target '%s'\n", target);

      return EXIT_FAILURE;
    }
  }

  if(neighbours_checked(graph, checked, id)) {
    for(int i = 0; i < graph->numberOfNeighbours[id]; i++) {
      int currentNeighbour = graph->neighbours[id][i];

      if(!checked[currentNeighbour]) {
        make(graph, graph->nodes[currentNeighbour]->target, checked);

        checked[currentNeighbour] = 1;
      }
    }
  }

  list_t *currentCommand = graph->nodes[id]->commands;

  while(currentCommand) {
    // system(currentCommand->content);
    printf(" - %s\n", currentCommand->content);

    currentCommand = currentCommand->next;
  }

  return EXIT_SUCCESS;
}

let verif_cycle (g : graph) : bool =
  (g = (S,A))
  bool TEST;
  for s dans S
    bool = bool && parcours_profondeur(s)
  return bool

graphe définit par liste d'adjacence
parcours_profondeur est O(|S| + |A|)
verif_cycle est en O(|S| . (|S| + |A|))
il existe de meilleur solution mais ici les graphes ne seront jamais très
grand de facon générale
*/

int main(int argc, char *argv[]) {
  dependencieGraph_t *graph = create_graph();
  compute_neighbours(graph);

  char *checked;

<<<<<<< HEAD
  if(!(checked = malloc(graph->numberOfNodes * sizeof(char)))) {
    debug_error("main", "Couldn't allocate memory for checked\n");

    delete_dependencie_graph(graph);

    return EXIT_FAILURE;
  }
  
  // we're supposing there are no options to our mymake tool
  if(argc > 1) { // if one (or more) target(s) is(are) specified
    for(int i = 1; i < argc; i++) {
      memset(checked, 0, graph->numberOfNodes);
      make(graph, argv[i], checked);
    }
  } else {
    make(graph, NULL, checked);
  }

  return EXIT_SUCCESS;
=======
  // 3eme étape exécution des lignes en fonction des dates de sauvegardes
  // paramétres ou pas à l'éxécution
>>>>>>> 4116890943256601bd7663be26baa4d44a7bc616
}


