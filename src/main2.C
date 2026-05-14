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

        fin = ScoreFinManche(joueur, fin, nb_joueur, TAILLE);
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
