#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "carte.h"
#include "joueur.h"
#include "affichage.h"
#include "jeu.h"
#include "sauvegarde.h"
 
int main(void) {
    srand(time(NULL));
 
    int nb_manche = 1;    // compteur de manches
    int TAILLE = 85;    // nombre total de cartes dans la pioche
    int dernierePioche = 0;  // indice de la prochaine carte à piocher dans tab 
    int fin  = 1;   // quand un joueur atteint 200 pts
    int nb_joueur;
    joueur *joueurs;
    cartes tab[85];     // la pioche 
    int verif;
 
    creerPioche(tab);
    melanger(tab, TAILLE);

 
    afficher_accueil();
 
    // Saisie du nombre de joueurs 
    do {
        printf(" Combien de joueurs ? ");
        verif = scanf("%d", &nb_joueur);
        vide_buffer();
    } while (nb_joueur <= 0 || verif != 1);
 
    joueurs = malloc(nb_joueur * sizeof(joueur));
    if (joueurs == NULL) { printf("Erreur allocation\n"); return 1; }
 
    // Saisie des pseudos 
    for (int i = 0; i < nb_joueur; i++) {
        printf(" Joueur %d quel est votre pseudo ? ", i + 1);
        scanf(" %s", joueurs[i].pseudo);
        vide_buffer();
        printf("\n Bienvenue %s !\n", joueurs[i].pseudo);
    }
 
    // Initialisation des scores totaux 
    for (int a = 0; a < nb_joueur; a++) {
        joueurs[a].nb_cartes   = 0;  // aucune carte piochée au départ
        joueurs[a].score_total = 0;   // score cumulé sur toutes les manches
        joueurs[a].debutManche = 0;
    }
 
    // Boucle principale de la partie 
    do {
        printf("\n");
        printf(JAUNE_GRAS " MANCHE  N°%d " RESET "\n\n", nb_manche);
        manche(tab, nb_joueur, joueurs, &TAILLE, &dernierePioche);
        nb_manche++;
 
        // Calcul des scores totaux et du leader 
        int maxScore    = -1;   // initialisé à -1 pour garantir qu'un score de 0 le dépasse
        int indexLeader = 0;
        for (int j = 0; j < nb_joueur; j++) {
            joueurs[j].score_total += joueurs[j].score_pot;
            if (joueurs[j].score_total > maxScore) {
                maxScore    = joueurs[j].score_total;
                indexLeader = j;
            }
            if (joueurs[j].score_total >= 200) fin = 0;
        }
 
        // Affichage des scores entre les manches si la partie continue 
        if (fin != 0 && TAILLE > 0)
            afficherScoresManche(joueurs, nb_joueur, indexLeader, TAILLE);
 
    } while (fin != 0 && TAILLE > 0);
 
    // Fin de partie 
    afficherFinPartie(joueurs, nb_joueur, TAILLE);
 
    // Proposition de sauvegarde 
    char enregistrer;
    do {
        printf(" Voulez-vous enregistrer les scores ? o(oui) ou n(non)\n");
        scanf(" %c", &enregistrer);
        vide_buffer();
    } while (enregistrer != 'o' && enregistrer != 'n');
 
    if (enregistrer == 'o') {
        char nom_fichier[50];
        printf(" Nom du fichier (sans extension) : ");
        scanf("%s", nom_fichier);
        vide_buffer();
        CahierDesCharges(nb_joueur, joueurs, nom_fichier);
    }
 
    free(joueurs);
    return 0;
}
 
