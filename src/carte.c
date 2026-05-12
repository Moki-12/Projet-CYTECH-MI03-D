#include "carte.h"     
#include <string.h>    
#include <stdlib.h>


void corrigeTab(cartes *tab) {
    int i = 0;
    tab[i].numero = 0; tab[i].bonus[0] = '\0'; i++;
    tab[i].numero = 1; tab[i].bonus[0] = '\0'; i++;
    for (int n = 2; n <= 12; n++)
        for (int j = 0; j < n; j++) {
            tab[i].numero = n; tab[i].bonus[0] = '\0'; i++;
        }
    tab[i].numero = -1; strcpy(tab[i++].bonus, "x2");
    tab[i].numero = -2; strcpy(tab[i++].bonus, "+2");
    tab[i].numero = -3; strcpy(tab[i++].bonus, "+4");
    tab[i].numero = -4; strcpy(tab[i++].bonus, "+6");
    tab[i].numero = -5; strcpy(tab[i++].bonus, "+8");
    tab[i].numero = -6; strcpy(tab[i++].bonus, "+10");
}

int melanger(cartes *tab, int taille) {
    if (tab == NULL || taille <= 0) return 0;
    for (int i = taille - 1; i > 0; i--) {
        int j      = rand() % (i + 1);
        cartes tmp = tab[i]; tab[i] = tab[j]; tab[j] = tmp;
    }
    return 1;
}

int effetNumero(int numero, int score) {
    if (numero < 0 || numero > 12 || score < 0) exit(1);
    return score + numero;
}

int effetBonus(char *bonus, int score) {
    if (bonus == NULL || score < 0) exit(2);
    if (strcmp(bonus, "x2")  == 0) return score * 2;
    if (strcmp(bonus, "+2")  == 0) return score + 2;
    if (strcmp(bonus, "+4")  == 0) return score + 4;
    if (strcmp(bonus, "+6")  == 0) return score + 6;
    if (strcmp(bonus, "+8")  == 0) return score + 8;
    if (strcmp(bonus, "+10") == 0) return score + 10;
    return score;
}

int carteExisteManche(cartes *main, int debut, int taille, cartes carte) {
    if (main == NULL) exit(4);
    for (int i = debut; i < debut + taille; i++)
        if (main[i].numero == carte.numero) return 1;
    return 0;
}

// Compte les numéros (sans bonus) depuis le début de la manche 
int compterNumeros(joueur *j) {
    if (j == NULL) exit(3);
    int count = 0;
    for (int m = j->debutManche; m < j->nb_cartes; m++)
        if (j->cartes[m].bonus[0] == '\0') count++;
    return count;
}

// Calcul du score final 
int calculerScoreFinal (joueur *j, int elimine){
    int score = 0;
    int debut = j->debutManche;
    int fin = j->debutManche + j->nbCartesManche;
    if(fin > j->nb_cartes){
        fin = j->nb_cartes;
    }

    if(debut >= fin){
        return 0;
    }
    if (elimine == 0){
    for (int i=debut; i<fin; i++){
        if (j->cartes[i].bonus[0] == '\0'){
            score = effetNumero(j->cartes[i].numero, score);// ou score =+j->cartes[i].numero mais necessite de changer ou supprimer la fonction effetNumero
        }
    }
    for (int i=debut; i<fin; i++){
        if (j->cartes[i].bonus[0] != '\0'){
            score = effetBonus(j->cartes[i].bonus, score);
        }
    }
    }
    return score;
}
