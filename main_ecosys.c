#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

#include "ecosys.h"

#define NB_PROIES 10
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define ITERATION_MAX 200

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.4;
int temps_repousse_herbe = -15;

int main(void) {
  srand(time(NULL));

  /* A completer. Part 2:
   * exercice 4, questions 1 et 2  */
  Animal *liste = NULL;
  Animal *n = creer_animal(SIZE_X - 1, SIZE_Y - 1, 10);
  liste = ajouter_en_tete_animal(liste, n);

  afficher_ecosys(liste, NULL);
  bouger_animaux(liste);
  afficher_ecosys(liste, NULL);
  reproduce(&liste, 1);

  int a = compte_animal_it(liste);
  printf("nb animeaux apres reproduction : %d\n", a);
  reproduce(&liste, 1);
  a = compte_animal_it(liste);
  printf("nb animeaux apres reproduction : %d\n", a);

  liberer_liste_animaux(liste);

  // exercice 5/6 question 2
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie = 200;

  for (int i = 0; i < NB_PROIES; i++) {
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie, &liste_proie);
  }
  for (int i = 0; i < NB_PREDATEURS; i++) {
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie,
                   &liste_predateur);
  }

  // Initialisation du monde
  int monde[SIZE_X][SIZE_Y];
  for (int i = 0; i < SIZE_X; ++i) {
    for (int j = 0; j < SIZE_Y; ++j) {
      monde[i][j] = 0;
    }
  }

  int nbMax = ITERATION_MAX;
  int nbIt = 0;
  int nbProies;
  int nbPredateurs;
  FILE *f = fopen("Evol_Pop.txt","w+");
  // La boucle s'arrête si la liste des proies/prédateurs est vide ou qu'on
  // atteint le nombre max d'itérations
  while (liste_proie && liste_predateur && nbMax != 0) {
    rafraichir_proies(&liste_proie, monde);
    rafraichir_predateurs(&liste_predateur, &liste_proie);
    rafraichir_monde(monde);
    afficher_ecosys(liste_proie, liste_predateur);
    nbProies = compte_animal_it(liste_proie);
    nbPredateurs = compte_animal_it(liste_predateur);
    nbIt++;
    fprintf(f,"%d %d %d\n", nbIt, nbProies, nbPredateurs);
    usleep(T_WAIT);
    nbMax--;
  }
  fclose(f);
  liberer_liste_animaux(liste_proie);
  liberer_liste_animaux(liste_predateur);

  return 0;
}
