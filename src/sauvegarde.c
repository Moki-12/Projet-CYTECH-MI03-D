void CahierDesCharges(int nb_joueur, joueur *joueurs, char *nom) {
    if (nb_joueur <= 0 || joueurs == NULL || nom == NULL) exit(1);
    char nomComplet[110];
    sprintf(nomComplet, "%s.txt", nom);
    FILE *f = fopen(nomComplet, "w");
    if (!f) { printf("Erreur : Impossible de créer le fichier %s\n", nomComplet); return; }
    for (int i = 0; i < nb_joueur; i++) {
        fprintf(f, " Joueur : %s | Score Final : %d\n", joueurs[i].pseudo, joueurs[i].score_total);
        fprintf(f, " Cartes obtenues : ");
        for (int j = 0; j < joueurs[i].nb_cartes; j++) {
            if (joueurs[i].cartes[j].bonus[0] == '\0')
                fprintf(f, "[%d] ", joueurs[i].cartes[j].numero);
            else
                fprintf(f, "[%s] ", joueurs[i].cartes[j].bonus);
        }
        fprintf(f, "\n  ──────────────────────────────\n");
    }
    fclose(f);
    printf(" La partie a ete sauvegardee sous le nom : %s\n", nomComplet);
}
