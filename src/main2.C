int main(){
    srand(time(NULL));
    int nb_manche   = 1;
    int TAILLE      = 85;
    int dernierePioche = 0;
    int fin         = 1;
    joueur *joueur;
    cartes tab[85];
    int melange_valid;
    int nb_joueur;
    int verif;

    corrigeTab(tab);
    

    printf("\n");
    printf(ROUGE_GRAS "  ╔════════════════════════════════════════╗\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ║" JAUNE_GRAS "               FLIPTECH                 " ROUGE_GRAS "║\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ╚════════════════════════════════════════╝\n\n" RESET);
    
    do {
    melange_valid = melanger(tab, TAILLE);
    } while (melange_valid != 1);
    do {
    printf (" Combien de joueur ? ");
    verif = scanf ("%d", &nb_joueur);
    vide_buffer();
    } while (nb_joueur <= 0 || verif != 1);
    
    joueur = malloc (nb_joueur * sizeof(joueur));
    
    menu(joueur, nb_joueur);
    do {
        printf("\n  " OR "  M A N C H E  N°%d " RESET "\n\n", nb_manche);
        manche(tab, nb_joueur, joueur, &TAILLE, &dernierePioche);
        nb_manche++;

        int maxScore    = -1;
        int indexLeader = 0;
        for(int j = 0; j < nb_joueur; j++){
            joueur[j].score_total += joueur[j].score_pot;
            if(joueur[j].score_total > maxScore){
                maxScore    = joueur[j].score_total;
                indexLeader = j;
            }
            if(joueur[j].score_total >= 200) fin = 0;
        }

        if(fin != 0 && TAILLE > 0){
            printf("\n  " MAGENTA_GRAS "SCORES" RESET "\n");
            for(int j = 0; j < nb_joueur; j++){
                printf("\n  " BLANC_GRAS "★ %s" RESET, joueur[j].pseudo);
                printf("\n  Score manche : %d", joueur[j].score_pot);

                if(joueur[j].score_pot == 0)
                    printf(ROUGE_GRAS " (Doublon)" RESET);
                else {
                    /* Flip 7 = 7 numéros — on recompte proprement */
                    int nbNumerosAff = compterNumeros(&joueur[j]);
                    if(nbNumerosAff >= 7)
                        printf(VERT_GRAS " (Flip 7)" RESET);
                }
                printf("\n  " OR "SCORE TOTAL : %d" RESET "\n", joueur[j].score_total);
            }
            printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
            printf("  Cartes restantes dans la pioche : %d\n", TAILLE);
            printf("  " JAUNE_GRAS "%s est en tête avec %d points !" RESET "\n",
                   joueur[indexLeader].pseudo, joueur[indexLeader].score_total);
            printf("  " OR "────────────────────────────────────────────" RESET "\n\n");
        }

    } while(fin != 0 && TAILLE > 0);

    AfficherFinPartie(TAILLE);
    AfficherGagnant(joueur, nb_joueur);

    char enregistrer;
    do {
        printf("Voulez-vous enregistrer les scores ? o(oui) ou n(non)\n");
        scanf(" %c", &enregistrer);
    } while(enregistrer != 'o' && enregistrer != 'n');

    if(enregistrer == 'o'){
        char nom_fichier[50];
        printf("Nom du fichier (sans extension) : ");
        scanf("%s", nom_fichier);
        CahierDesCharges(nb_joueur, joueur, nom_fichier);
    }
    free(joueur);
    return 0;
}
