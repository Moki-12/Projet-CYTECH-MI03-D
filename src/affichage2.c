#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


void afficher_une_carte(cartes c, int ligne){
    if (ligne == 0){
        printf(" "OR "┌─────┐" RESET);
    } 
    else if (ligne == 1 || ligne == 3) {
        if (c.bonus[0] != '\0') {
            printf(" "OR "│" BG_GOLD "     " RESET OR "│" RESET);
        }else {
            printf(" "OR "│" BG_WHITE "     " RESET OR "│" RESET);
        }
    }
    else if (ligne == 2) {
        if (c.bonus[0] != '\0') {
            printf(" "OR "│" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET, c.bonus);
        }else {
            printf(" "OR "│" BG_WHITE TEXT_BLACK " %2d  " RESET OR "│" RESET, c.numero);
        }
    }
    else if (ligne == 4) {
        printf(" "OR "└─────┘" RESET);
    }
}
    

void afficher_ligne_carte(cartes *tab_cartes, int taille) {
    for (int ligne = 0; ligne < 5; ligne++) {
        for (int m = 0; m < taille; m++)
            afficher_une_carte(tab_cartes[m], ligne);
        printf("\n");
    }
}

void afficher_accueil() {
    printf("\n");
    printf(ROUGE_GRAS " ╔════════════════════════════════════════╗\n" RESET);
    printf(ROUGE_GRAS " ║                                        ║\n" RESET);
    printf(ROUGE_GRAS " ║" JAUNE_GRAS "               FLIPTECH                 " ROUGE_GRAS "║\n" RESET);
    printf(ROUGE_GRAS " ║                                        ║\n" RESET);
    printf(ROUGE_GRAS " ╚════════════════════════════════════════╝\n" RESET);
    printf("\n");
}

void afficher_tour(joueur *j, int tour) {
    printf("\n");
    printf(OR " ┌──────────────────────────────────────────────────────────────────────────────┐" RESET "\n");
    printf(OR " │ " ROUGE_GRAS " AU TOUR DE %-20s" RESET, j->pseudo);
    printf(OR "                                      Tour %d │" RESET "\n", tour);
    printf(OR " └──────────────────────────────────────────────────────────────────────────────┘" RESET "\n");
    printf("\n");
}

void afficherMain(joueur *j) {
    printf(MAGENTA_GRAS " Vos cartes en main : (%d/7 numeros)\n" RESET,
           compterNumeros(j));

    int n_main = j->nbCartesManche;
    int debutAff = j->nb_cartes-n_main;

    /* On passe les cartes de la main à afficherRangeeCartes */
    afficher_ligne_carte(&j->cartes[debutAff], n_main);
} 

void afficherStats(cartes *tab, int n){
    int compteur[13];
    for (int i = 0; i < 13; i++){
        compteur[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (tab[i].numero >= 0 && tab[i].numero <= 12){
            compteur[tab[i].numero] ++;
        }
    }
    printf("\n");
    printf(MAGENTA_GRAS " Statistiques de la pioche — cartes déjà sorties\n" RESET);

    for(int ligne = 0; ligne < 5; ligne++){ 
        for (int i = 0; i <= 6; i++){     //première rangée de carte
            cartes temp;               // pour stocker la fréquence
            temp.numero = i;
            temp.bonus[0] = '\0';
            afficher_une_carte(temp, ligne);
            int total_carte;
            if (ligne == 2){         // affichage stat
                if (i == 0){
                    total_carte = 1;
                }else {
                    total_carte = i;
                }
                
                /* %2d force l'affichage sur 2 caractères (ex: " 1" ou "11") */
                /* Cela garantit que le texte fait toujours la même largeur */
                printf(JAUNE_GRAS ":%2d"RESET "/%-2d" , compteur[i], total_carte);
            } else {
                printf("      "); 
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n"); 

    //seconde rangée même chose
    for (int ligne = 0; ligne < 5; ligne++){
        for (int i = 7; i <= 12; i++){
            cartes temp;
            temp.numero = i;
            temp.bonus[0] = '\0';

            afficher_une_carte(temp, ligne);

            if (ligne == 2) {
                printf(JAUNE_GRAS ":%2d" RESET "/%-2d" RESET, compteur[i], i);
            }else {
                printf("      ");
            }
            printf(" ");
        }
        printf("\n");
    }
}

void afficher_cartepiochée(cartes c) {
    printf(" Vous venez de piocher la carte :\n");
    afficher_ligne_carte(&c, 1);
}

void afficherRisque(joueur *j, cartes *tab, int n, int taille){
    int stats_danger[13];             // pour stocker risque
    for (int i = 0; i < 13; i++){
        stats_danger[i] = 0;
    }
    for (int s = 0; s < n; s++)
        if (tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12)
            stats_danger[tab[s].numero]++;

    int dangerTotal = 0;
    printf(" ────────────────────────────────\n");
    printf(MAGENTA_GRAS " ANALYSE DU RISQUE \n\n" RESET);

    for (int m = j->debutManche; m < j->nb_cartes; m++){
    if (j->cartes[m].bonus[0] != '\0'){   // Si la carte est un bonus on l'ignore
        continue; 
    }

    int num_carte = j->cartes[m].numero;
    int totalmain = num_carte; 
    int restantes = totalmain - stats_danger[num_carte];

    /* Sécurité pour ne pas avoir un nombre négatif */
    if (restantes < 0){
        restantes = 0;
    }

    dangerTotal += restantes;
        printf(" - Carte" JAUNE_GRAS" %d" RESET " : " ROUGE_GRAS "%d "RESET"encore dans la pioche\n", num_carte, restantes);
    }

   // Calcul risque
    float risque;
    if (taille > 0){
        /* On multiplie par 100.0f pour transformer le ratio en pourcentage (ex: 0.25 -> 25.0) */
        risque = (dangerTotal * 100.0f) / taille;
    } else {
        risque = 0.0f;
    }

    printf(" Total cartes dangereuses : %d sur %d cartes restantes\n", dangerTotal, taille);
    printf(" Probabilité de doublon : ");

    // affichage proba avec couleurs
    if(risque < 20.0f){
        printf(VERT_GRAS "%.1f%%\n" RESET, risque);
    }else if (risque < 37.0f){
        printf(JAUNE_GRAS "%.1f%%\n" RESET, risque);
    }else {
        printf(ROUGE_GRAS "%.1f%%\n" RESET, risque);
    }

    printf("\n Conseil : ");

    // affichage conseil selon niveau de risque
    if(risque < 20.0f){
        printf(VERT_GRAS "Risque faible — Piochez en toute tranquillité !\n" RESET);
    }else if (risque < 37.0f){
        printf(JAUNE_GRAS "Risque moyen — Réfléchissez bien avant de piocher !\n" RESET);
    }else {
        printf(ROUGE_GRAS "Risque eleve — Il serait préférable de vous arrêter !\n" RESET);
    }
    printf(" ──────────────────────────────────────\n");
    printf("\n");
}

void afficherScoresManche(joueur *joueurs, int nb_joueur, int indexLeader, int TAILLE) {
    printf("\n  " MAGENTA_GRAS "SCORES" RESET);
    printf("\n");
    for (int j = 0; j < nb_joueur; j++) {
        printf("\n  " BLANC_GRAS "★ %s" RESET, joueurs[j].pseudo);
        printf("\n  Score manche : %d", joueurs[j].score_pot);

        // On calcule le nombre de numéros différents pour la condition Flip 7
        int numDiff = compterNumeros(&joueurs[j]);
        if(joueurs[j].score_pot == 0){
            printf(ROUGE_GRAS " (Doublon)" RESET);
        }else if (numDiff >= 7) {
            if(joueurs[j].nb_cartes > 7){
                printf(VERT_GRAS " (Flip 7) !" RESET);
            }
        }
        printf("\n  " OR "SCORE TOTAL : %d" RESET "\n", joueurs[j].score_total);
    }

    printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
    printf(" Cartes restantes dans la pioche : %d\n", TAILLE);
    printf(JAUNE_GRAS " %s est en tête avec %d points !" RESET "\n",
           joueurs[indexLeader].pseudo, joueurs[indexLeader].score_total);
    printf(OR " ────────────────────────────────────────────" RESET "\n\n");
}

// afficher le gagnant a la fin de la partie
void AfficherGagnant(joueur *joueur, int nb_joueur){
    int maxFinal    = -1;
    int indexGagnant = 0;
    for(int j = 0; j < nb_joueur; j++){
        if(joueur[j].score_total > maxFinal){
            maxFinal     = joueur[j].score_total;
            indexGagnant = j;
        }
    }

    printf("\n  " JAUNE_GRAS "  🏆 LE VAINQUEUR EST : %s !" RESET, joueur[indexGagnant].pseudo);
    printf("\n  " BLANC_GRAS "  Avec un score total de %d points." RESET "\n", maxFinal);
    printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
    for(int j = 0; j < nb_joueur; j++){
        if(j == indexGagnant)
            printf("  - " JAUNE_GRAS "%-10s : %d pts (VAINQUEUR)" RESET "\n", joueur[j].pseudo, joueur[j].score_total);
        else
            printf("  - %-10s : %d pts\n", joueur[j].pseudo, joueur[j].score_total);
    }
    printf("  " OR "────────────────────────────────────────────" RESET "\n\n");

}

void AfficherFinPartie(int TAILLE){
     printf("\n\n");
    printf(ROUGE_GRAS "  F I N   D E   P A R T I E" RESET "\n\n");
    if(TAILLE <= 0)
        printf(JAUNE_GRAS "  LA PIOCHE EST VIDE...\n  Le moment de découvrir les résultats est arrivé !\n" RESET);
    else
        printf(JAUNE_GRAS "  UN JOUEUR A ATTEINT 200 POINTS !\n Le moment de découvrir les résultats est arrivé !\n" RESET);

    printf("\n  Appuyez sur [Entree] pour afficher le classement final...");
    while(getchar() != '\n');
    getchar();
}
