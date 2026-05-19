#ifndef JOUEUR_H
#define JOUEUR_H
 
#include "carte.h"
 
typedef struct {
    char   pseudo[100];
    int    scores;
    cartes cartes[500];
    int    nb_cartes;
    int    score_total;
    int    nbCartesManche;
    int    score_pot;
    int    debutManche;
    int    flip7;
} joueur;
 
int compterNumeros(joueur *j);
int calculerScoreFinal(joueur *j, int elimine);
 
#endif
 
