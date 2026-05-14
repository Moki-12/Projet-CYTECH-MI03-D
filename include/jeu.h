#ifndef JEU_H
#define JEU_H
#define SCORE_LIMIT 200 

#include "joueur.h"
#include "carte.h"

void manche(cartes *tab, int nb_joueur, joueur *joueurs, int *taille, int *dernierePioche);
void pause();
void vide_buffer();

#endif
