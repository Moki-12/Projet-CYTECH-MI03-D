#include <stdlib.h>
#include "joueur.h"
#include "carte.h"
 
// Compte les cartes numeros (sans bonus) depuis le début de la manche 
int compterNumeros(joueur *j) {
    if (j == NULL) exit(3);
    int count = 0;
    for (int m = j->debutManche; m < j->nb_cartes; m++)
        if (j->cartes[m].bonus[0] == '\0') count++;
    return count;
}
 
// Calcule le score final d'un joueur pour la manche en cours 
int calculerScoreFinal(joueur *j, int elimine) {
    int score = 0;
    int debut = j->debutManche;
    int fin   = j->debutManche + j->nbCartesManche;   // dernière carte de la main = première carte de la main + le nombre de cartes piochés durant la manche
 
    if (fin > j->nb_cartes){
     fin = j->nb_cartes;
    }
    if (debut >= fin){       
    return 0;
    }
 
    // Les joueurs éliminés (doublon) ont un scire de 0
    if (elimine != 0){
     return 0;
    }
    // Ajouter la valeur de la carte numéro au score  
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] == '\0')
            score = effetNumero(j->cartes[i].numero, score);
 
    // Ajouter la valeur de la carte bonus au score 
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] != '\0')
            score = effetBonus(j->cartes[i].bonus, score);
 
    return score;
}
 
