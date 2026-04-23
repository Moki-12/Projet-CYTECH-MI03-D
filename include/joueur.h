#ifndef JOUEUR_H
#define JOUEUR_H

#include "carte.h"

typedef struct {
    char pseudo[50];
    Carte main[50];
    int nb_cartes;
    int score_manche;
    int score_total;
} Joueur;



#endif