#ifndef CARTES_H
#define CARTES_H

  
typedef struct {
    int numero;
    char bonus[5];
} cartes;
       
void corrigeTab(cartes *tab);
void melanger(cartes *tab, int taille);
int effetNumero(cartes *tab, int taille);
int effetBonus(char *bonus, int score);
int carteExisteManche(cartes *main, int debut, int taille, cartes carte);

#endif
