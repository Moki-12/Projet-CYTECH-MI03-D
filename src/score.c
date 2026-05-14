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
    }
    for (int i=debut; i<fin; i++){
        if (j->cartes[i].bonus[0] != '\0'){
            score = effetBonus(j->cartes[i].bonus, score);
        }
    }
    return score;
}

int ScoreFinManche (joueur *joueur, int fin, int nb_joueur, int taille){
    int maxScore = -1;
    int indexLeader = 0;
    for (int i=0; i<nb_joueur; i++){
        joueur[i].score_total += joueur[i].score_pot;
        if (joueur[i].score_total > maxScore){
            maxScore = joueur[i].score_total;
            indexLeader = i;
        }
        if (joueur[i].score_total >= 200) fin = 0;
    }
    if (fin != 0 && taille > 0){
        printf("\n  " MAGENTA_GRAS "SCORES" RESET "\n");
        for (int i=0; i<nb_joueur; i++){
            printf("\n  " BLANC_GRAS "★ %s" RESET, joueur[i].pseudo);
            printf("\n  Score manche : %d", joueur[i].score_pot);
            
            if (joueur[i].score_pot == 0)
            printf(ROUGE_GRAS " (Doublon)" RESET);
            else {
                int nbNumerosAff = compterNumeros (&joueur[i]);
                if (nbNumerosAff >= 7)
                printf(VERT_GRAS " (Flip 7)" RESET);
            }
            printf("\n  " OR "SCORE TOTAL : %d" RESET "\n", joueur[i].score_total);
        }
        printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
        printf("  Cartes restantes dans la pioche : %d\n", taille);
        printf("  " JAUNE_GRAS "%s est en tête avec %d points !" RESET "\n", joueur[indexLeader].pseudo, joueur[indexLeader].score_total);
        printf("  " OR "────────────────────────────────────────────" RESET "\n\n");
    }
}
