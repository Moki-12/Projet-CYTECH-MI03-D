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
 
// Recalcule du score en fonction des cartes piochées dans la manche
int calculerScoreFinal(joueur *j, int elimine) {
    int score = 0;
    int debut = j->debutManche; //indice de la première carte piochée
    int fin   = j->debutManche + j->nbCartesManche;   // dernière carte de la main = première carte de la main + le nombre de cartes piochés durant la manche
 
    if (fin > j->nb_cartes){ // verife que fin ne depasse pas le nombre de cartes du joueur
     fin = j->nb_cartes;
    }
    if (debut >= fin){    
    return 0;
    }
 
    // Les joueurs éliminés (doublon) ont un score de 0
    if (elimine != 0){
     return 0;
    }
    // Ajouter la valeur de la carte numéro au score seulement pour les joueurs encore actifs 
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] == '\0')
            score = effetNumero(j->cartes[i].numero, score);
 
    // Ajouter la valeur de la carte bonus au score pour tous les joueurs
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] != '\0')
            score = effetBonus(j->cartes[i].bonus, score);
 
    return score;
}
 
