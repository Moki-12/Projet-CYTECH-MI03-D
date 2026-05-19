#ifndef AFFICHAGE_H
#define AFFICHAGE_H
 
#include "carte.h"
#include "joueur.h"
 
/* Couleurs ANSI */
#define ROUGE_GRAS   "\x1b[1;31m"
#define VERT_GRAS    "\x1b[1;32m"
#define JAUNE_GRAS   "\x1b[1;93m"
#define OR           "\x1b[33m"
#define BLANC        "\x1b[97m"
#define BLANC_GRAS   "\x1b[1;37m"
#define RESET        "\x1b[0m"
#define BG_WHITE     "\033[47m"
#define BG_GOLD      " #ffd700"
#define TEXT_BLACK   "\033[30m"
#define MAGENTA_GRAS "\x1b[38;5;210m"
#define FOND_NOIR    "\x1b[40m"
 
void afficher_une_carte(cartes c, int ligne);
void afficher_ligne_carte(cartes *tab_cartes, int taille);
void afficher_accueil(void);
void afficher_tour(joueur *j, int tour);
void afficherMain(joueur *j);
void afficherStats(cartes *tab, int n);
void afficher_cartepiocher(cartes c);
void afficherRisque(joueur *j, cartes *tab, int n, int taille);
void afficherScoresManche(joueur *joueurs, int nb_joueur, int indexLeader, int taille);
void afficherFinPartie(joueur *joueurs, int nb_joueur, int taille);
 
#endif
 
