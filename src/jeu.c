#include <stdio.h>
#include <stdlib.h>
#include "carte.h"
#include "joueur.h"
#include "affichage.h"
#include "jeu.h"
 
void vide_buffer(void) {
    while (getchar() != '\n');
}
 
void pause(void) {
    printf("  Appuyez sur [Entree] pour passer au joueur suivant.\n");
    while (getchar() != '\n');
    getchar();
}
 
void manche(cartes *tab, int nb_joueur, joueur *joueurs, int *taille, int *dernierePioche) {
    if (tab == NULL || joueurs == NULL || nb_joueur <= 0) exit(5);
 
    int nb_tour     = 0;
    int n           = *dernierePioche;
    int sortir;
    int verif;
    int flip7       = 0;
    int joueur_actif = 0;
 
    int *arret   = malloc(nb_joueur * sizeof(int));
    int *elimine = malloc(nb_joueur * sizeof(int));
    if (arret == NULL || elimine == NULL) { printf("Erreur allocation\n"); exit(1); }
 
    /* Initialisation de la manche */
    for (int l = 0; l < nb_joueur; l++) {
        joueurs[l].scores        = 0;
        arret[l]                 = 0;
        joueurs[l].flip7         = 0;
        elimine[l]               = 0;
        joueurs[l].nbCartesManche = 0;
        joueurs[l].score_pot     = 0;
        joueurs[l].debutManche   = joueurs[l].nb_cartes;
    }
 
    do {
        nb_tour++;
 
        for (int j = 0; j < nb_joueur; j++) {
 
            /* Pioche vide : arrêt immédiat */
            if (*taille == 0) {
                *dernierePioche = n;
                free(arret); free(elimine);
                return;
            }
 
            if (arret[j] == 1 || elimine[j] == 1) continue;
 
            /* Boucle d'affichage et de saisie */
            do {
                afficher_tour(&joueurs[j], nb_tour);
 
                if (joueurs[j].nbCartesManche >= 1) {
                    afficherMain(&joueurs[j]);
                    printf("\n  Votre score potentiel : %d\n  ────────────────────────────────\n",
                           joueurs[j].score_pot);
                    afficherStats(tab, n);
                    afficherRisque(&joueurs[j], tab, n, *taille);
                }
 
                do {
                    if (nb_tour <= 1)
                        printf(" %s que voulez vous faire ?\n [1] : Piocher\n", joueurs[j].pseudo);
                    else
                        printf(" %s que voulez vous faire ?\n [1] : Piocher || [2] : S'arrêter\n\n", joueurs[j].pseudo);
                    printf(" ────────────────────────────────────────\n");
                    verif = scanf("%d", &sortir);
                    vide_buffer();
                } while (verif != 1);
 
            } while (sortir != 1 && (sortir != 2 || nb_tour <= 1));
 
            if (sortir == 2) {
                arret[j] = 1;
            } else {
                /* Récupération de la carte piochée */
                joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
                cartes c   = joueurs[j].cartes[joueurs[j].nb_cartes];
                int debut  = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;
 
                afficher_cartepiocher(c);
 
                /* Vérification doublon */
                if (carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, c)) {
                    printf("\n");
                    printf(ROUGE_GRAS " 💀  DOUBLON !" RESET "\n");
                    printf(" Aïe ! vous venez de piocher un %d alors que vous en aviez déjà un.\n", c.numero);
                    printf(" Vous êtes éliminé pour le reste de la manche.\n");
                    printf("\n  " ROUGE_GRAS "Votre score pour cette manche est donc de 0." RESET "\n\n");
                    joueurs[j].scores    = 0;
                    joueurs[j].score_pot = 0;
                    elimine[j]           = 1;
                    joueurs[j].nb_cartes++;
                } else {
                    /* Carte valide */
                    if (c.bonus[0] == '\0')
                        joueurs[j].scores = effetNumero(c.numero, joueurs[j].scores);
                    joueurs[j].nb_cartes++;
                    joueurs[j].nbCartesManche++;
                    joueurs[j].score_pot = calculerScoreFinal(&joueurs[j], 0);
 
                    /* Test Flip 7 */
                    int nbNumeros = compterNumeros(&joueurs[j]);
                    if (nbNumeros >= 7 && c.bonus[0] == '\0') {
                        printf("  " JAUNE_GRAS "★ FLIP 7 !" RESET "\n");
                        printf(" Vous venez de collecter 7 numéros différents ! Un bonus vous est accordé !\n");
                        printf("\n  %d + " JAUNE_GRAS "15" RESET " = " BLANC_GRAS "%d" RESET "\n\n",
                               joueurs[j].score_pot, joueurs[j].score_pot + 15);
                        joueurs[j].flip7 = 1;
                        flip7            = 1;
                        n++;
                        (*taille)--;
                        break;
                    } else {
                        printf(JAUNE_GRAS " ✦ Nouvelle carte obtenue !" RESET "\n");
                        if (c.bonus[0] == '\0')
                            printf(" Score : %d + %d = " BLANC_GRAS "%d pts" RESET "\n\n",
                                   joueurs[j].scores - c.numero, c.numero, joueurs[j].score_pot);
                        else
                            printf(" Bonus " JAUNE_GRAS "%s" RESET " obtenu ! Sera appliqué en fin de manche.\n\n",
                                   c.bonus);
                    }
                }
 
                if (sortir == 1) pause();
                (*taille)--;
                n++;
            }
        }
 
        /* Compte les joueurs encore actifs */
        joueur_actif = 0;
        for (int v = 0; v < nb_joueur; v++)
            if (arret[v] == 0 && elimine[v] == 0) joueur_actif++;
 
    } while (flip7 == 0 && joueur_actif > 0);
 
    /* Calcul des scores finaux en fin de manche */
    for (int d = 0; d < nb_joueur; d++) {
        joueurs[d].score_pot = calculerScoreFinal(&joueurs[d], elimine[d]);
        if (joueurs[d].flip7 == 1)
            joueurs[d].score_pot += 15;
    }
 
    *dernierePioche = n;
    free(elimine);
    free(arret);
}
 
