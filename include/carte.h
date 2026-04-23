#ifndef CARTES_H
#define CARTES_H

#define NUMERO 
#define BONUS 

typedef struct {
    int type;
    int valeur;
    char bonus[5];
} cartes;

void affichageTab(cartes tab[]);
void melanger(cartes tab[], int taille);
int effetCarte(cartes c, int score);
int carteExiste(cartes tab[], int taille, cartes c);
cartes piocherCarte(cartes tab[], int *indextab)

#endif