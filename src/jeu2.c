void manche(cartes *tab, int nb_joueur, joueur *joueurs, int *taille, int *dernierePioche){
    if (tab == NULL || joueurs == NULL || nb_joueur < 0){
        exit (5);
    }
    int nb_tour = 0;
    int n = *dernierePioche;
    int sortir;
    int *arret = malloc (nb_joueur * sizeof(int));
    int *elimine = malloc (nb_joueur * sizeof(int));
    if (arret == NULL || elimine == NULL){
        printf ("Erreur allocation dynamique");
        exit(1);
    }
    int verif;
    int joueur_actif;
    int flip7 = 0;
    //mettre a zero
    init(joueurs, nb_joueur, arret, elimine);
    
    do {
        nb_tour++;
        for(int j = 0; j < nb_joueur; j++){

            if(*taille == 0) return;
            if(arret[j] == 1 || elimine[j] == 1) continue;

            do {
                printf("\n");
                printf(OR "  ┌──────────────────────────────────────────────────────────────────────────────┐" RESET "\n");
                printf(OR "  │ " ROUGE_GRAS " AU TOUR DE %-20s" RESET, joueurs[j].pseudo);
                printf(OR "                                    Tour %d │" RESET "\n", nb_tour);
                printf(OR "  └──────────────────────────────────────────────────────────────────────────────┘" RESET "\n");
                printf("\n");

                if(joueurs[j].nbCartesManche >= 1){
                    //carte dans la main
                    AfficherCartes(joueurs, j);
                    
                    printf("\n  Votre score potentiel : %d\n  ────────────────────────────────\n",
                           joueurs[j].score_pot);

                    /* Statistiques */
                    StatsPioche(tab, n);
                    
                    /* Analyse du risque */
                    AnalyseRisque(joueurs, tab, n, j, *taille);
                    
                }
                do {
                if(nb_tour <= 1)
                    printf("  %s que voulez vous faire ?\n  [1] : Piocher\n", joueurs[j].pseudo);
                else
                    printf("  %s que voulez vous faire ?\n  [1] : Piocher || [2] : S'arrêter\n\n", joueurs[j].pseudo);
                printf("  ────────────────────────────────────────\n");

                verif = scanf("%d", &sortir);
                vide_buffer();
                } while (verif != 1);

            } while (sortir != 1 && sortir != 2 || verif != 1);

            if(sortir == 2){
                arret[j] = 1;
            } else {
                int scoreAvant = joueurs[j].score_pot;

                /* On place la carte piochée dans le tableau */
                joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
                cartes c = joueurs[j].cartes[joueurs[j].nb_cartes];
                int debut = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;

                /* Affichage carte piochée */
               AfficherCartePioche(c);
               
                /* Doublon ? */
                if(carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, c)){
                    printf("  " ROUGE_GRAS "💀  DOUBLON !" RESET "\n");
                    printf("  Aïe ! vous venez de piocher un %d alors que vous en aviez déjà un.\n", c.numero);
                    printf("  Vous êtes éliminé pour le reste de la manche.\n");
                    printf("\n  " ROUGE_GRAS "Votre score pour cette manche est donc de 0." RESET "\n\n");
                    joueurs[j].scores    = 0;
                    joueurs[j].score_pot = 0;
                    elimine[j]          = 1;
                    joueurs[j].nb_cartes++;
                } else {
                    /* Appliquer l'effet de la carte */
                    if(c.bonus[0] == '\0')
                        joueurs[j].scores = effetNumero(c.numero, joueurs[j].scores);
                    joueurs[j].nb_cartes++;
                    joueurs[j].nbCartesManche++;
                    joueurs[j].score_pot = joueurs[j].scores;

                    /* ══ TEST FLIP 7 ══
                       Règle : exactement 7 NUMÉROS différents (bonus non comptés)
                       ET la carte qui déclenche doit être un numéro               */
                    int nbNumeros = compterNumeros(&joueurs[j]);

                    if(nbNumeros >= 7 && c.bonus[0] == '\0'){
                        printf("  " JAUNE_GRAS "★ FLIP 7 !" RESET "\n");
                        printf("  Vous venez de collecter 7 numeros differents ! Bonus accorde !\n");
                        joueurs[j].score_pot += 15;
                        flip7 = 1;
                        joueurs[j].flip7 = 1;
                        n++;
                        break;
                    } else {
                        printf("  " JAUNE_GRAS "✦ Nouvelle carte obtenue !" RESET "\n");
                        if(c.bonus[0] == '\0')
                            printf("  Score : %d + %d = " BLANC_GRAS "%d pts" RESET "\n\n",
                                   scoreAvant, c.numero, joueurs[j].score_pot);
                        else
                            printf("  Score : %d = " BLANC_GRAS "%d pts" RESET "\n\n",
                                   scoreAvant, joueurs[j].score_pot);
                    }
                }

                if(sortir == 1) pause();
                (*taille)--;
                n++;
            }
        }
        //comptage des joueurs encore actif (non sortie ni elimine)
        joueur_actif = 0;
        for (int v=0; v<nb_joueur; v++){
            if (arret[v] == 0 && elimine[v] == 0){
                joueur_actif++;
            }
        }
    } while (flip7 == 0 && joueur_actif > 0);
    // recomptage des cartes pioches pour connaitre le score
    for (int d=0; d<nb_joueur; d++){
        joueurs[d].score_pot = calculerScoreFinal (&joueurs[d], elimine[d]);
        if (joueurs[d].flip7 == 1){
            joueurs[d].score_pot += 15;
        }
    }
    *dernierePioche = n;
free(elimine);
free(arret);
}
