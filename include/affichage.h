#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "cartes.h"
#include "joueur.h"

#define ROUGE_GRAS   "\x1b[1;31m"
#define VERT_GRAS    "\x1b[1;32m"
#define JAUNE_GRAS   "\x1b[1;93m"
#define OR           "\x1b[33m"
#define BLANC        "\x1b[97m"
#define BLANC_GRAS   "\x1b[1;37m"
#define RESET        "\x1b[0m"
#define BG_WHITE     "\033[47m"
#define BG_GOLD      "\033[43m"
#define TEXT_BLACK   "\033[30m"
#define MAGENTA_GRAS "\x1b[38;5;210m"

void afficher_une_carte(cartes c, int ligne);
void afficherMain(joueur j);
void afficher_cartepiochée(cartes c);
void afficherRisque(joueur *j, cartes *tab, int n, int taille);
void afficherFinPartie(joueur *joueurs, int nb_joueur, int TAILLE);

#endif
