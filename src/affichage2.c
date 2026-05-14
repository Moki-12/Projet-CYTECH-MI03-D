void AfficherCartes(joueur *joueur, int j){
    printf(MAGENTA_GRAS "  Vos cartes en main : (%d/7 numeros)\n" RESET, compterNumeros(&joueur[j]));
    
    int n_main = joueur[j].nbCartesManche;
    int debutAff = joueur[j].nb_cartes - n_main;
    
    for (int k=0; k<n_main; k++)printf(OR " ┌─────┐" RESET " "); 
    printf ("\n");
    for (int i=0; i<n_main; i++){
        int idx = debutAff + i;
        if (joueur[j].cartes[idx].bonus[0] == '\0'){
            printf(OR " │" BG_WHITE "     " RESET OR "│" RESET " ");
        }
        else {
            printf(OR " │" BG_GOLD  "     " RESET OR "│" RESET " ");
        }
    }
    printf ("\n");
    for (int i=0; i<n_main; i++){
        int idx = debutAff + i;
        if (joueur[j].cartes[idx].bonus[0] == '\0'){
            printf(OR " │" BG_WHITE TEXT_BLACK " %2d  " RESET OR "│" RESET " ", joueur[j].cartes[idx].numero);
        }
        else {
            printf(OR " │" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET " ", joueur[j].cartes[idx].bonus);
        }
    }
    printf ("\n");
    for (int i=0; i<n_main; i++){
        int idx = debutAff + i;
        if (joueur[j].cartes[idx].bonus[0] == '\0'){
            printf(OR " │" BG_WHITE "     " RESET OR "│" RESET " ");
    }
    else {
        printf(OR " │" BG_GOLD  "     " RESET OR "│" RESET " ");
    }
    }
    printf ("\n");
    for (int i=0; i<n_main; i++){
        printf(OR " └─────┘" RESET " ");
    }
    printf ("\n");
}

void StatsPioche (cartes *tab, int n){
    //compter les frequences
    cartes compteur[13] = {0};
    for (int i=0; i<n; i++){
        if (tab[i].numero >= 0 && tab[i].numero <= 12){
            compteur[tab[i].numero].numero++;
        }
    }
    printf ("\n");
    printf(MAGENTA_GRAS "  Statistiques — cartes déjà sorties\n" RESET);
    //afficher les cartes
    
    //premiere ligne
    for (int l=0; l<=6; l++) printf(OR "┌─────┐" RESET "  ");
    printf("\n");
    for (int l=0; l<=6; l++) printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", l);
    printf("\n");
    for (int l=0; l<=6; l++) printf(OR "│  -  │" RESET "  ");
    printf("\n");
    for (int l=0; l<=6; l++){
        int total_l;
        if (l == 0) {
            total_l = 1;
            
        }
        else {
            total_l = l;
        }
        printf(OR "│" RESET JAUNE_GRAS " %d/%-2d" RESET OR "│" RESET "  ", compteur[l].numero, total_l);
    }
    printf("\n");
    for(int l = 0; l <= 6; l++) printf(OR "└─────┘" RESET "  ");
    printf("\n");
    
    //seconde ligne
    for (int l=7; l<=12; l++) printf(OR "┌─────┐" RESET "  ");
    printf("\n");
    for (int l=7; l<=12; l++) printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", l);
    printf("\n");
    for (int l=7; l<=12; l++) printf(OR "│  -  │" RESET "  ");
    printf("\n");
    for (int l=7; l<=12; l++) printf(OR "│" RESET JAUNE_GRAS " %d/%-2d" RESET OR "│" RESET "  ", compteur[l].numero, l);
    printf("\n");
    for (int l=7; l<=12; l++) printf(OR "└─────┘" RESET "  ");
    printf("\n\n");
}

void AnalyseRisque(joueur *joueur, cartes *tab, int n, int j, int taille){
    int stats_danger[13] = {0};
    for (int i=0; i<n; i++){
        if (tab[i].bonus[0] == '\0' && tab[i].numero >= 0 && tab[i].numero <= 12)
        stats_danger[tab[i].numero]++;
    }
    
    int dangerTotal= 0;
    printf("  ────────────────────────────────\n");
    printf(MAGENTA_GRAS "  ANALYSE DU RISQUE \n\n" RESET);
    for (int k = joueur[j].debutManche; k < joueur[j].nb_cartes; k++){
        if(joueur[j].cartes[k].bonus[0] != '\0') continue;
        int num_carte = joueur[j].cartes[k].numero;
        int totalmain = (num_carte <= 1) ? 1 : num_carte;
        int restantes = totalmain - stats_danger[num_carte];
        if (restantes < 0) restantes = 0;
        dangerTotal += restantes;
        printf("  - Carte" JAUNE_GRAS " %d" RESET " : " ROUGE_GRAS "%d " RESET "encore dans la pioche\n", num_carte, restantes);
    }
    float risque;
    if (taille > 0) {
        risque = (dangerTotal * 100.0f) / (taille);
    }
    else {
    risque = 0;
    }
    printf("  Total cartes dangereuses :" BLANC_GRAS "%d" RESET " sur " BLANC_GRAS "%d " RESET "cartes restantes\n", dangerTotal, taille);
    printf("  Probabilite de doublon : ");
    if(risque < 20.0f) printf(VERT_GRAS  "%.1f%%\n" RESET, risque);
    else if(risque < 37.0f) printf(JAUNE_GRAS "%.1f%%\n" RESET, risque);
    else printf(ROUGE_GRAS "%.1f%%\n" RESET, risque);
    
    printf ("\n Conseil : ");
    if(risque < 20.0f) printf(VERT_GRAS  "Risque faible — Piochez en toute tranquillite !\n" RESET);
    else if(risque < 37.0f)  printf(JAUNE_GRAS "Risque moyen — Reflechissez bien avant de piocher.\n" RESET);
    else printf(ROUGE_GRAS "Risque eleve — Il serait préférable de vous arreter !\n" RESET);
    printf("  ──────────────────────────────────────\n\n");
}

void AfficherCartePioche (cartes c){
    printf (" Vous venez de piocher la carte :\n");
    printf(OR "  ┌─────┐" RESET "\n");
    if (c.bonus[0] == '\0'){
        printf(OR "  │" BG_WHITE "     " RESET OR "│" RESET "\n");
        printf(OR "  │" BG_WHITE TEXT_BLACK "  %2d " RESET OR "│" RESET "\n", c.numero);
        printf(OR "  │" BG_WHITE "     " RESET OR "│" RESET "\n");
    }
    else {
        printf(OR "  │" BG_GOLD "     " RESET OR "│" RESET "\n");
        printf(OR "  │" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET "\n", c.bonus);
        printf(OR "  │" BG_GOLD "     " RESET OR "│" RESET "\n");
    }
    printf(OR "  └─────┘" RESET "\n");
}
