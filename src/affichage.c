#include <stdio.h>
#include "carte.h"
#include "joueur.h"
#include "affichage.h"
 
void afficher_une_carte(cartes c, int ligne) {
    if (ligne == 0) {
        printf(" " OR "┌─────┐" RESET);
    } else if (ligne == 1 || ligne == 3) {
        if (c.bonus[0] != '\0')
            printf(" " OR "│" BG_GOLD "     " RESET OR "│" RESET);
        else
            printf(" " OR "│" BG_WHITE "     " RESET OR "│" RESET);
    } else if (ligne == 2) {
        if (c.bonus[0] != '\0')
            printf(" " OR "│" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET, c.bonus);
        else
            printf(" " OR "│" BG_WHITE TEXT_BLACK " %2d  " RESET OR "│" RESET, c.numero);
    } else if (ligne == 4) {
        printf(" " OR "└─────┘" RESET);
    }
}
 
void afficher_ligne_carte(cartes *tab_cartes, int taille) {
    for (int ligne = 0; ligne < 5; ligne++) {
        for (int m = 0; m < taille; m++)
            afficher_une_carte(tab_cartes[m], ligne);
        printf("\n");
    }
}
 
void afficher_accueil(void) {
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
    int debutAff = j->nb_cartes - j->nbCartesManche;
    afficher_ligne_carte(&j->cartes[debutAff], j->nbCartesManche);
}
 
void afficherStats(cartes *tab, int n) {
    int compteur[13] = {0};
 
    for (int i = 0; i < n; i++)
        if (tab[i].numero >= 0 && tab[i].numero <= 12)
            compteur[tab[i].numero]++;
 
    printf("\n");
    printf(MAGENTA_GRAS " Statistiques de la pioche — cartes déjà sorties\n" RESET);
 
    /* Première rangée : cartes 0..6 */
    for (int ligne = 0; ligne < 5; ligne++) {
        for (int i = 0; i <= 6; i++) {
            cartes temp;
            temp.numero   = i;
            temp.bonus[0] = '\0';
            afficher_une_carte(temp, ligne);
            if (ligne == 2) {
                int total = (i == 0) ? 1 : i;
                printf(JAUNE_GRAS ":%2d" RESET "/%-2d", compteur[i], total);
            } else {
                printf("      ");
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
 
    /* Deuxième rangée : cartes 7..12 */
    for (int ligne = 0; ligne < 5; ligne++) {
        for (int i = 7; i <= 12; i++) {
            cartes temp;
            temp.numero   = i;
            temp.bonus[0] = '\0';
            afficher_une_carte(temp, ligne);
            if (ligne == 2)
                printf(JAUNE_GRAS ":%2d" RESET "/%-2d", compteur[i], i);
            else
                printf("      ");
            printf(" ");
        }
        printf("\n");
    }
}
 
void afficher_cartepiocher(cartes c) {
    printf(" Vous venez de piocher la carte :\n");
    afficher_ligne_carte(&c, 1);
}
 
void afficherRisque(joueur *j, cartes *tab, int n, int taille) {
    int stats_danger[13] = {0};
 
    for (int s = 0; s < n; s++)
        if (tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12)
            stats_danger[tab[s].numero]++;
 
    int dangerTotal = 0;
    printf(" ────────────────────────────────\n");
    printf(MAGENTA_GRAS " ANALYSE DU RISQUE \n\n" RESET);
 
    for (int m = j->debutManche; m < j->nb_cartes; m++) {
        if (j->cartes[m].bonus[0] != '\0') continue;
 
        int num_carte = j->cartes[m].numero;
        int restantes = num_carte - stats_danger[num_carte];
        if (restantes < 0) restantes = 0;
 
        dangerTotal += restantes;
        printf(" - Carte" JAUNE_GRAS " %d" RESET " : " ROUGE_GRAS "%d " RESET "encore dans la pioche\n",
               num_carte, restantes);
    }
 
    float risque = (taille > 0) ? (dangerTotal * 100.0f) / taille : 0.0f;
 
    printf(" Total cartes dangereuses : %d sur %d cartes restantes\n", dangerTotal, taille);
    printf(" Probabilité de doublon : ");
 
    if (risque < 20.0f)
        printf(VERT_GRAS "%.1f%%\n" RESET, risque);
    else if (risque < 37.0f)
        printf(JAUNE_GRAS "%.1f%%\n" RESET, risque);
    else
        printf(ROUGE_GRAS "%.1f%%\n" RESET, risque);
 
    printf("\n Conseil : ");
    if (risque < 20.0f)
        printf(VERT_GRAS "Risque faible — Piochez en toute tranquillité !\n" RESET);
    else if (risque < 37.0f)
        printf(JAUNE_GRAS "Risque moyen — Réfléchissez bien avant de piocher !\n" RESET);
    else
        printf(ROUGE_GRAS "Risque elevé — Il serait préférable de vous arrêter !\n" RESET);
 
    printf(" ──────────────────────────────────────\n\n");
}
 
void afficherScoresManche(joueur *joueurs, int nb_joueur, int indexLeader, int taille) {
    printf("\n  " MAGENTA_GRAS "SCORES" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        printf("\n  " BLANC_GRAS "★ %s" RESET, joueurs[j].pseudo);
        printf("\n  Score manche : %d", joueurs[j].score_pot);
 
        int numDiff = compterNumeros(&joueurs[j]);
        if (joueurs[j].score_pot == 0)
            printf(ROUGE_GRAS " (Doublon)" RESET);
        else if (numDiff >= 7 && joueurs[j].nb_cartes > 7)
            printf(VERT_GRAS " (Flip 7) !" RESET);
 
        printf("\n  " OR "SCORE TOTAL : %d" RESET "\n", joueurs[j].score_total);
    }
 
    printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
    printf(" Cartes restantes dans la pioche : %d\n", taille);
    printf(JAUNE_GRAS " %s est en tête avec %d points !" RESET "\n",
           joueurs[indexLeader].pseudo, joueurs[indexLeader].score_total);
    printf(OR " ────────────────────────────────────────────" RESET "\n\n");
}
 
void afficherFinPartie(joueur *joueurs, int nb_joueur, int taille) {
    printf("\n\n");
    printf(ROUGE_GRAS " FIN  DE  LA PARTIE" RESET "\n\n");
    if (taille <= 0)
        printf(JAUNE_GRAS " LA PIOCHE EST VIDE...\n Le moment de découvrir les résultats est arrivé !\n" RESET);
    else
        printf(JAUNE_GRAS " UN JOUEUR A ATTEINT 200 POINTS !\n Le moment de découvrir les résultats est arrivé !\n" RESET);
 
    printf("\n  Appuyez sur [Entree] pour afficher le classement final...");
    getchar();
 
    int maxFinal     = -1;
    int indexGagnant = 0;
    for (int j = 0; j < nb_joueur; j++) {
        if (joueurs[j].score_total > maxFinal) {
            maxFinal     = joueurs[j].score_total;
            indexGagnant = j;
        }
    }
 
    printf("\n " JAUNE_GRAS " 🏆 LE VAINQUEUR EST : %s !" RESET, joueurs[indexGagnant].pseudo);
    printf("\n " BLANC_GRAS " Avec un score total de %d points." RESET "\n", maxFinal);
    printf("\n" OR " ────────────────────────────────────────────" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        if (j == indexGagnant)
            printf(" - " JAUNE_GRAS "%-10s : %d pts (VAINQUEUR)" RESET "\n",
                   joueurs[j].pseudo, joueurs[j].score_total);
        else
            printf(" - %-10s : %d pts\n", joueurs[j].pseudo, joueurs[j].score_total);
    }
    printf(OR " ────────────────────────────────────────────" RESET "\n\n");
}
