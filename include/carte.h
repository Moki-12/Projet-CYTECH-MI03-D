#ifndef CARTES_H
#define CARTES_H

#define NUMERO 1
#define BONUS 0

typedef struct {
    int type;
    int valeur;
    char bonus[5];
} cartes;

void affichageTab(cartes tab[]);
void melanger(cartes tab[], int taille);
int effets(cartes c, int score);
int carteExiste(cartes tab[], int taille, cartes c);
cartes piocherCarte(cartes tab[], int *indextab)

#endif
