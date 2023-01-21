#include <stdio.h>
#include <stdlib.h>

#include "ecosys.h"

float p_ch_dir = 0.01;
float p_reproduce_proie = 0.4;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

int main() {
  Animal *liste_proie = NULL;
  Animal *liste_predateur = NULL;
  int energie = 10;

  for (int i = 0; i < 20; i++) {
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie,
                   &liste_proie);
    ajouter_animal(rand() % (SIZE_X), rand() % (SIZE_Y), energie,
                   &liste_predateur);
  }

  printf("Nombre de prédateurs : %d, Nombre de proies : %d\n",
         compte_animal_rec(liste_predateur), compte_animal_rec(liste_proie));
  afficher_ecosys(liste_proie, liste_predateur);

  ecrire_ecosys("test", liste_predateur, liste_proie);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  liste_predateur = NULL;
  liste_proie = NULL;

  lire_ecosys("test", &liste_predateur, &liste_proie);
  afficher_ecosys(liste_proie, liste_predateur);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  return 0;
}
