#ifndef JOUEUR_H
#define JOUEUR_H
 
#include "carte.h"
 
typedef struct {
    char   pseudo[100];
    int    scores;         // le score obtenu après avoir pioché une carte
    cartes cartes[500];
    int    nb_cartes;
    int    score_total;   // le score total en fin de manche 
    int    nbCartesManche;
    int    score_pot;    // le score potentiel en fin d'un tour
    int    debutManche;
    int    flip7;
} joueur;
 
int compterNumeros(joueur *j);                     
int calculerScoreFinal(joueur *j, int elimine);
 
#endif
 
