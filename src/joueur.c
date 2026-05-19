#include <stdlib.h>
#include "joueur.h"
#include "carte.h"
 
/* Compte les cartes numérotées (sans bonus) depuis le début de la manche */
int compterNumeros(joueur *j) {
    if (j == NULL) exit(3);
    int count = 0;
    for (int m = j->debutManche; m < j->nb_cartes; m++)
        if (j->cartes[m].bonus[0] == '\0') count++;
    return count;
}
 
/* Calcule le score final d'un joueur pour la manche en cours */
int calculerScoreFinal(joueur *j, int elimine) {
    int score = 0;
    int debut = j->debutManche;
    int fin   = j->debutManche + j->nbCartesManche;
 
    if (fin > j->nb_cartes) fin = j->nb_cartes;
    if (debut >= fin)        return 0;
 
    /* Les joueurs éliminés (doublon) obtiennent 0 */
    if (elimine != 0) return 0;
 
    /* 1. Appliquer les cartes numérotées */
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] == '\0')
            score = effetNumero(j->cartes[i].numero, score);
 
    /* 2. Appliquer les cartes bonus */
    for (int i = debut; i < fin; i++)
        if (j->cartes[i].bonus[0] != '\0')
            score = effetBonus(j->cartes[i].bonus, score);
 
    return score;
}
 
