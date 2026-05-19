typedef struct {
    char   pseudo[100];
    int    scores;
    cartes cartes[500]; // Sécurité contre l'overflow
    int    nb_cartes;
    int    score_total;
    int    nbCartesManche;
    int    score_pot;
    int    debutManche;
    int    flip7;
} joueur;

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
