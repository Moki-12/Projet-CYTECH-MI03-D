void pause() {
    printf("  Appuyez sur [Entree] pour passer au joueur suivant.\n");
    while (getchar() != '\n');
    getchar();
}

void vide_buffer(){
    while (getchar() != '\n'){
    }
}

// informations joueurs et initialisations score des joueurs
int menu (joueur *j, int nb_joueur){
    char buffer [50];
    for (int i=0; i<nb_joueur; i++){
        printf (" Joueur %d quel est votre pseudo ? ", i + 1);
        scanf (" %s", buffer);
        strcpy(j[i].pseudo, buffer);
        j[i].nb_cartes   = 0;
        j[i].score_total = 0;
        j[i].debutManche = 0;
    }
}
