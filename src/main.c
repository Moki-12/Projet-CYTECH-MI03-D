int main(){
    srand(time(NULL));
    int TAILLE = 20;
    //int TAILLE = 85;
    int dernierePioche=0;
    int fin;
    int nb_joueur;
    joueur joueur[50];
    char prénom[50];
   
    printf ("Combien de joueurs ? \n");
    scanf ("%d", &nb_joueur);
    for (int i=0; i<nb_joueur; i++){
        printf ("Joueur %d quel est votre pseudo ?\n", i+1);
        scanf (" %s",prénom);
        strcpy(joueur[i].pseudo, prénom);
        printf ("Prénom du joueur %d est %s !\n", i+1, joueur[i].pseudo);
    }
    for (int a=0; a<nb_joueur; a++){
    joueur[a].nb_cartes=0;
    joueur[a].score_total=0;
    }
    cartes tab[TAILLE];
    corrigeTab(tab);
    //affichage(tab, TAILLE);
    melanger(tab, TAILLE);
    affichage(tab, TAILLE);
    do{
        manche(tab, nb_joueur, joueur, &TAILLE/*revoir*/,&dernierePioche);
        printf ("Nombre de cartes restantes dans la pioche : %d\n", TAILLE);
     for (int j=0; j<nb_joueur; j++){
        joueur[j].score_total += joueur[j].scores;
        printf ("Le score total de %s est %d !\n", joueur[j].pseudo, joueur[j].score_total);
        if (joueur[j].score_total>=200){
        fin=0;
        }
    }
    }
    while ( fin !=0  && TAILLE > 0);
    char enregistrer;
    do {
        printf ("Voulez-vous enregistrer les scores de la partie ? o(oui) ou n(non)\n");
        scanf (" %c", &enregistrer);
    }
    while (enregistrer != 'o' && enregistrer != 'n');
        if (enregistrer == 'o'){
            char nom_fichier[50];
            printf ("Quel nom voudrait que le fichier se nomme ?\n");
            scanf ("%s", nom_fichier);
            CahierDesCharges(nb_joueur, &TAILLE, joueur);
        }
    //creerTableau(tab, N);
    /*int v = verif(tab, N);
    printf ("%d\n", v);
    if (v==1){
        melanger(tab, TAILLE);
    }*/
    return 0;
}