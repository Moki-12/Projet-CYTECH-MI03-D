#ifndef CARTE_H
#define CARTE_H
 
typedef struct {
    int  numero;
    char bonus[5];
} cartes;
 
void creerPioche(cartes *tab);
int  melanger(cartes *tab, int taille);
int  effetNumero(int numero, int score);
int  effetBonus(char *bonus, int score);
int  carteExisteManche(cartes *main, int debut, int taille, cartes carte);
 
#endif
 
