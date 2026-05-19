#ifndef CARTE_H
#define CARTE_H
 
typedef struct {
    int  numero;
    char bonus[5];  // stocke le texte du bonus ("+10", "x2") en incluant le '\0' 
} cartes;
 
void creerPioche(cartes *tab);   // remplit le tableau de 85 cartes qui constitue la pioche
int  melanger(cartes *tab, int taille);  // mélange aléatoirement les cartes de la pioche
int  effetNumero(int numero, int score);  // ajoute la valeur du numéro au score 
int  effetBonus(char *bonus, int score);  // ajoute la valeur du bonus au score
int  carteExisteManche(cartes *main, int debut, int taille, cartes carte);  // cherche si un joueur possède un doublon
 
#endif
 
