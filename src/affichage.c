#include <stdio.h>
#include "carte.h"
#include "joueur.h"
#include "affichage.h"
 
void afficher_une_carte(cartes c, int ligne) {     // créer le design d'une carte sur une même ligne
    if (ligne == 0) {
        printf(" " OR "┌─────┐" RESET);
    } else if (ligne == 1 || ligne == 3) {
        if (c.bonus[0] != '\0')
            printf(" " OR "│" BG_GOLD "     " RESET OR "│" RESET);
        else
            printf(" " OR "│" BG_WHITE "     " RESET OR "│" RESET);
    } else if (ligne == 2) {
        if (c.bonus[0] != '\0')
            printf(" " OR "│" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET, c.bonus);    // -3s sert à bloquer l'affichage à gauche pour éviter les décalages
        else
            printf(" " OR "│" BG_WHITE TEXT_BLACK " %2d  " RESET OR "│" RESET, c.numero);
    } else if (ligne == 4) {
        printf(" " OR "└─────┘" RESET);
    }
}
 
void afficher_ligne_carte(cartes *tab_cartes, int taille) {          // affiche taille cartes côte à côte  
    for (int ligne = 0; ligne < 5; ligne++) {           // 5 lignes pour dessiner une carte complète 
        for (int m = 0; m < taille; m++)
            afficher_une_carte(tab_cartes[m], ligne);  //chaque carte est dessinée ligne par ligne
        printf("\n");
    }
}
 
void afficher_accueil(void) {     // void en paramètre = sécurité contre les bugs : signale que la fonction ne prend rien en entrée
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
    printf(ROUGE_GRAS " ┌──────────────────────────────────────────────────────────────────────────────┐" RESET "\n");
    printf(ROUGE_GRAS " │ " OR " AU TOUR DE %-20s" RESET, j->pseudo);
    printf(ROUGE_GRAS "                                      Tour %d │" RESET "\n", tour);
    printf(ROUGE_GRAS " └──────────────────────────────────────────────────────────────────────────────┘" RESET "\n");
    printf("\n");
}
 
void afficherMain(joueur *j) {
    printf(MAGENTA_GRAS " 🃏  Vos cartes en main : (%d/7 numeros)\n" RESET, compterNumeros(j));
    int debutAff = j->nb_cartes - j->nbCartesManche;   //indice de la première carte de la manche
    afficher_ligne_carte(&j->cartes[debutAff], j->nbCartesManche);
}

//affiche le nombre de fois que chaque carte numéro est déjà sortie
void afficherStats(cartes *tab, int n) {  
    int compteur[13] = {0};  //initialise un tableau à 0 pour chaques cartes numéros

    // parcourt les n cartes déjà sorties et incrémente le compteur correspondant
    for (int i = 0; i < n; i++)
        if (tab[i].numero >= 0 && tab[i].numero <= 12)
            compteur[tab[i].numero]++;
 
    printf("\n");
    printf(MAGENTA_GRAS " 📊  Statistiques de la pioche — cartes déjà sorties\n" RESET);
 
    // première rangée : cartes 0 à 6 
    for (int ligne = 0; ligne < 5; ligne++) {
        for (int i = 0; i <= 6; i++) {
            cartes temp;       // carte temporaire juste pour l'affichage 
            temp.numero   = i;
            temp.bonus[0] = '\0';
            afficher_une_carte(temp, ligne);
            if (ligne == 2) {
             
                int total;
                   if (i == 0) {   // la carte 0 n'existe qu'en 1 exemplaire, les autres en i exemplaires
                   total = 1;
                   } else {
                     total = i;
                   }   
                printf(JAUNE_GRAS ":%2d" RESET "/%-2d", compteur[i], total);
            } else {
                printf("      ");   //espaces pour aligner avec la stat affichée ligne 2
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
 
    // Deuxième rangée : cartes 7 à 12 
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
    int stats_danger[13] = {0};    // nombre d'exemplaires de chaque carte déjà sortis

    // Compte les cartes numéros déjà sorties de la pioche
    for (int s = 0; s < n; s++) {
        if (tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12) {
            stats_danger[tab[s].numero]++;
        }
    }
 
    printf("\n");
    printf(MAGENTA_GRAS " ⚠️  ANALYSE DU RISQUE \n\n" RESET);

    int cartes_comptees = 0;
    printf(" Vous possédez dans votre main les cartes suivantes :\n");
    
    // Pour chaque carte numéro dans la main du joueur on affiche sa présence dans la pioche
    for (int m = j->debutManche; m < j->nb_cartes; m++) {
        if (j->cartes[m].bonus[0] != '\0') {
            continue;    // on ignore les cartes bonus car elles ne créent pas de doublon
        }
        
        int num_carte = j->cartes[m].numero;
        int restantes = num_carte - stats_danger[num_carte]; // total exemplaire - sorties
        if (restantes < 0) {
            restantes = 0;
        }
        printf( JAUNE_GRAS " - Carte %d" RESET " : " ROUGE_GRAS "%d " RESET "encore dans la pioche\n",
               num_carte, restantes);
        cartes_comptees += restantes;
    }

    // Calcul de la probabilité brute de doublon
    float risque = 0.0f;
    if (taille > 0) {
        risque = (cartes_comptees * 100.0f) / taille;
    }
    printf("\n Probabilité de doublon :" ROUGE_GRAS " %.1f%%\n" RESET , risque);
    printf("\n\n");
}
 
void afficherScoresManche(joueur *joueurs, int nb_joueur, int indexLeader, int taille) {
    printf("\n  " MAGENTA_GRAS "📝  SCORES" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        printf("\n " BLANC_GRAS "★ %s" RESET, joueurs[j].pseudo);
        printf("\n Score manche : %d", joueurs[j].score_pot);
 
        int numDiff = compterNumeros(&joueurs[j]);
        if (joueurs[j].score_pot == 0)
            printf(ROUGE_GRAS " (Doublon)" RESET);
        else if (numDiff >= 7 && joueurs[j].nb_cartes > 7)
            printf(VERT_GRAS " (Flip 7) !" RESET);
 
        printf("\n " OR "SCORE TOTAL : %d" RESET "\n", joueurs[j].score_total);
    }
 
    printf("\n " OR "────────────────────────────────────────────" RESET "\n");
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

    // recherche du gagnant
    int maxFinal = -1;   // initialisé à -1 pour être sûr que n'importe quel score positif le dépasse
    int indexGagnant = 0;
    for (int j = 0; j < nb_joueur; j++) {
        if (joueurs[j].score_total > maxFinal) {
            maxFinal = joueurs[j].score_total;
            indexGagnant = j;
        }
    }
 
    printf("\n " JAUNE_GRAS "🏆 LE VAINQUEUR EST : %s !" RESET, joueurs[indexGagnant].pseudo);
    printf("\n " BLANC_GRAS "Avec un score total de %d points." RESET "\n", maxFinal);
    printf("\n" OR " ────────────────────────────────────────────" RESET "\n");

    // affiche tous les joueurs
    for (int j = 0; j < nb_joueur; j++) {
        if (j == indexGagnant)
            printf(" - " JAUNE_GRAS "%-10s : %d pts (VAINQUEUR)" RESET "\n",
                   joueurs[j].pseudo, joueurs[j].score_total);
        else
            printf(" - %-10s : %d pts\n", joueurs[j].pseudo, joueurs[j].score_total);
    }
    printf(OR " ────────────────────────────────────────────" RESET "\n\n");
}
