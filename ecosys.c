#include "ecosys.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
  assert(x >= 0 && x < SIZE_X);
  assert(y >= 0 && y < SIZE_Y);
  Animal *n =
      ajouter_en_tete_animal(*liste_animal, creer_animal(x, y, energie));
  *liste_animal = n;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  Animal *pa;

  assert(liste);
  pa = *liste;
  if (*liste == animal) {  // si c'est la tete qu'il faut supprimer
    *liste = (*liste)->suivant;
    free(pa);
  } else {  // si c'est au milieu on se place juste avant
            // l'element à supprimer
    while (pa->suivant && pa->suivant != animal) {
      pa = pa->suivant;
    }
    if (pa->suivant) {
      Animal *la = pa->suivant;
      pa->suivant = la->suivant;
      free(la);
    }
  }
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal *liberer_liste_animaux(Animal *liste) {
  Animal *tmp = NULL;
  while (liste) {
    tmp = liste;

    liste = liste->suivant;
    free(tmp);
  }

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt = 0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de
 * contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa = NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j] = ' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa = pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
    if ((ecosys[pa->x][pa->y] == '@') ||
        (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
      ecosys[pa->x][pa->y] = '@';
    } else {
      ecosys[pa->x][pa->y] = 'O';
    }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie = compte_animal_it(liste_proie);
  int nbpred = compte_animal_it(liste_predateur);

  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H"); /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */

void bouger_animaux(Animal *la) {
  /*A Completer*/
  while (la) {
    // dir[0]
    float a = (float)rand() / (float)RAND_MAX;
    if (a < p_ch_dir) {
      la->dir[0] = rand() % 3 - 1;
    }
    // dir[1]
    a = (float)rand() / (float)RAND_MAX;
    if (a < p_ch_dir) {
      la->dir[1] = rand() % 3 - 1;
    }
    la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;
    la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;
    la = la->suivant;
  }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  /*A Completer*/
  assert(liste_animal);
  Animal *pa = *liste_animal;
  float a;
  while (pa) {
    a = (float)rand() / (float)RAND_MAX;
    if (a < p_reproduce) {
      ajouter_animal(pa->x, pa->y, pa->energie / 2.0, liste_animal);
      pa->energie /= 2.0;
    }
    pa = pa->suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  // A Completer
  assert(liste_proie);
  bouger_animaux(*liste_proie);
  Animal *la = *liste_proie;
  Animal *tmp = NULL;
  while (la) {
    la->energie -= 1;
    if (monde[la->x][la->y] >= 0) {
      la->energie += monde[la->x][la->y];
      monde[la->x][la->y] = temps_repousse_herbe;
    }
    if (la->energie < 0) {
      tmp = la;
      la = la->suivant;
      enlever_animal(liste_proie, tmp);
    } else {
      la = la->suivant;
    }
  }

  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  /*A Completer*/
  Animal *p = l;
  while (p) {
    if (p->x == x && p->y == y) {
      return p;
    }
    p = p->suivant;
  }
  return NULL;
}
/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  // A Completer
  assert(liste_predateur);
  assert(liste_proie);
  Animal *la = *liste_predateur;
  bouger_animaux(la);
  Animal *proie = NULL;
  Animal *tmp = NULL;

  while (la) {
    la->energie -= 1;
    proie = animal_en_XY(*liste_proie, la->x, la->y);

    if (proie) {
      la->energie += proie->energie;
      enlever_animal(liste_proie, proie);
    }

    if (la->energie < 0) {
      tmp = la->suivant;
      enlever_animal(liste_predateur, la);
      la = tmp;
    }

    else {
      la = la->suivant;
    }
  }
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
  /*A Completer*/
  int i, j;
  for (i = 0; i < SIZE_X; i++)
    for (j = 0; j < SIZE_Y; j++) monde[i][j]++;
}

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur,
                   Animal *liste_proie) {
  FILE *fichier = NULL;
  fichier = fopen(nom_fichier, "w");
  assert(fichier);
  Animal *pa = liste_proie;
  fprintf(fichier, "<proies>\n");
  while (pa) {
    fprintf(fichier, "x=%d y=%d dir=[%d %d] e=%f\n", pa->x, pa->y, pa->dir[0],
            pa->dir[1], pa->energie);
    pa = pa->suivant;
  }
  fprintf(fichier, "</proies>\n");
  pa = liste_predateur;
  fprintf(fichier, "<predateurs>\n");
  while (pa) {
    fprintf(fichier, "x=%d y=%d dir=[%d %d] e=%f\n", pa->x, pa->y, pa->dir[0],
            pa->dir[1], pa->energie);
    pa = pa->suivant;
  }
  fprintf(fichier, "</predateurs>\n");
  fclose(fichier);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur,
                 Animal **liste_proie) {
  FILE *fichier = fopen(nom_fichier, "r");
  assert(fichier);
  char str[256];
  int x_lu;
  int y_lu;
  int dir1;
  int dir2;
  float e_lu;
  fgets(str, 256, fichier);
  assert((strncmp(str, "<proies>", 8)) == 0);
  fgets(str, 256, fichier);
  while (strncmp(str, "</proies>", 9) != 0) {
    sscanf(str, "x=%d y=%d dir=[%d %d] e=%f", &x_lu, &y_lu, &dir1, &dir2,
           &e_lu);
    Animal *a = creer_animal(x_lu, y_lu, e_lu);
    a->dir[0] = dir1;
    a->dir[1] = dir2;
    a->suivant = *liste_proie;
    *liste_proie = a;
    fgets(str, 256, fichier);
  }
  fgets(str, 256, fichier);
  assert((strncmp(str, "<predateurs>", 12)) == 0);
  fgets(str, 256, fichier);
  while (strncmp(str, "</predateurs>", 13) != 0) {
    sscanf(str, "x=%d y=%d dir=[%d %d] e=%f", &x_lu, &y_lu, &dir1, &dir2,
           &e_lu);
    Animal *a = creer_animal(x_lu, y_lu, e_lu);
    a->dir[0] = dir1;
    a->dir[1] = dir2;
    a->suivant = *liste_predateur;
    *liste_predateur = a;
    fgets(str, 256, fichier);
  }
  fclose(fichier);
}
