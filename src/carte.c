#include "carte.h"     
#include <string.h>    
#include <stdlib.h>


void AfficheTab(cartes tab[]){
    int i = 0;
    tab[i].numero = 0;
    tab[i].bonus[0] = '\0';
    i++;
    tab[i].numero = 1;
    tab[i].bonus[0] = '\0';
    i++;
    for(int n = 2; n <= 12; n++){
        for(int j = 0; j < n; j++){
            tab[i].numero = n;
            tab[i].bonus[0] = '\0';
            i++;
        }
    }
    strcpy(tab[i++].bonus, "x2");
    strcpy(tab[i++].bonus, "+2");
    strcpy(tab[i++].bonus, "+4");
    strcpy(tab[i++].bonus, "+6");
    strcpy(tab[i++].bonus, "+8");
    strcpy(tab[i++].bonus, "+10");
}


void melanger(cartes tab[], int taille){
    for(int i = taille - 1; i > 0; i--){
        int j = rand() % (i + 1);

        cartes temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}

int effetNumero(int numero,char *bonus, int score){
    score += numero;
    
    if(strcmp(bonus, "x2") == 0){
        score = score * 2;
    }
    else if(strcmp(bonus, "+2") == 0){
        score += 2;
    }
    else if(strcmp(bonus, "+4") == 0){
        score += 4;
    }
    else if(strcmp(bonus, "+6") == 0){
        score += 6;
    }
    else if(strcmp(bonus, "+8") == 0){
        score += 8;
    }
    else if(strcmp(bonus, "+10") == 0){
        score += 10;
    }

    return score;
}



int carteExiste(cartes tab[], int taille, cartes c){
    for(int i = 0; i < taille; i++){
        if(tab[i].type == c.type){
            if(c.type == NUMERO && tab[i].numero == c.numero)
                return 1;
            if(c.type == BONUS && strcmp(tab[i].bonus, c.bonus) == 0)
                return 1;
        }
    }
    return 0;
}

cartes piocherCarte(cartes tab[], int *indextab) {
    cartes c;
    c = tab[*indextab];
    (*indexPioche)++;
    return c;
}
