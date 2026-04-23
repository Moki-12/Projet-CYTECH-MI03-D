#ifndef CARTES_H
#define CARTES_H

#define NUMERO 
#define BONUS 

typedef struct {
    int type;
    int valeur;
    char bonus[5];
} Carte;

void affichageTab(Carte tab[]);
void melanger(Carte tab[], int taille);
int effetCarte(Carte c, int score);
int carteExiste(Carte tab[], int taille, Carte c);
cartes piocherCarte(cartes tab[], int *indextab)

#endif