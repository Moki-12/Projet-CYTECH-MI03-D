#ifndef JEU_H
#define JEU_H
 
#include "joueur.h"
#include "carte.h"
 
void manche(cartes *tab, int nb_joueur, joueur *joueurs, int *taille, int *dernierePioche);
void pause(void);
void vide_buffer(void);
 
#endif
 
