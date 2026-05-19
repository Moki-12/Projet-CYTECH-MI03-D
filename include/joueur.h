#ifndef JOUEUR_H
#define JOUEUR_H
 
#include "carte.h"
 
typedef struct {
    char   pseudo[100];
    int    scores;         // le score obtenu après avoir pioché une carte
    cartes cartes[500];    // tableau de toutes les cartes piochées sur toute la partie (500 pour éviter l'overflow)
    int    nb_cartes;       // nombre total de carte piochée depuis le début de la partie
    int    score_total;   // le score total en fin de manche 
    int    nbCartesManche;
    int    score_pot;    // le score potentiel en fin d'un tour
    int    debutManche;   // indice du tab carte de la première carte piochée par le joueur dans la manche 
    int    flip7;
} joueur;
 
int compterNumeros(joueur *j);                     
int calculerScoreFinal(joueur *j, int elimine);
 
#endif
 
