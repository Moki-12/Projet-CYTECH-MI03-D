#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "cartes.h"
#include "joueur.h"


void affichagePioche(Carte tab[], int taille);
void affichageMain(Joueur j);
void affichageScores(Joueur joueurs[], int nb_joueur);
void affichageTour(int numeroTour);
void affichageCarte(Carte c);

#endif