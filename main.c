#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "rule.h"

dependencieGraph_t *create_graph() {
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
        // '\t' alors traitement de la commande pour la règle en cours
        char *command = malloc((strlen(line + 1) + 1) * sizeof(char));
        strcpy(command, line + 1);
        add_command(rule, command);

      } else if (line[0] != '\n'){
        // pas de '\t' en début de ligne
        // nouvelle règle
        rule = new_rule();

        // stocke dans le graphe la nouvelle règle
        add_node(g, rule);

        // séparation par ' : ' pour avoir le nom de la règle
        token1 = strtok(line, " ");
        while (token1 != NULL) {
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
  // 1er étape création du graphe

  // 2eme étape vétification de cycle

  // 3eme étape exécution des lignes en fonction des dates de sauvegardes
  // paramétres ou pas à l'éxécution
}
