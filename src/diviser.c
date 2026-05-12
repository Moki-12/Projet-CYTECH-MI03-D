#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ============================================================
// COULEURS ANSI
// ============================================================
#define ROUGE_GRAS   "\x1b[1;31m"
#define VERT_GRAS    "\x1b[1;32m"
#define JAUNE_GRAS   "\x1b[1;93m"
#define OR           "\x1b[33m"
#define BLANC        "\x1b[97m"
#define BLANC_GRAS   "\x1b[1;37m"
#define RESET        "\x1b[0m"
#define BG_WHITE     "\033[47m"
#define BG_GOLD      "\033[43m"
#define TEXT_BLACK   "\033[30m"
#define MAGENTA_GRAS "\x1b[38;5;210m"

// ============================================================
// STRUCTURES
// ============================================================
typedef struct {
    int  numero;
    char bonus[5];
} cartes;

typedef struct {
    char   pseudo[100];
    int    scores;
    cartes cartes[200];
    int    nb_cartes;
    int    score_total;
    int    nbCartesManche;
    int    score_pot;
    int    debutManche;
    int    flip7;
} joueur;

// ============================================================
// UTILITAIRES
// ============================================================

void pause() {
    printf(" Appuyez sur [Entree] pour passer au joueur suivant.\n");
    getchar();
}

void vide_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ============================================================
// FONCTIONS CARTES
// ============================================================

void corrigeTab(cartes *tab) {
    int i = 0;
    tab[i].numero = 0; tab[i].bonus[0] = '\0'; i++;
    tab[i].numero = 1; tab[i].bonus[0] = '\0'; i++;
    for (int n = 2; n <= 12; n++)
        for (int j = 0; j < n; j++) {
            tab[i].numero = n; tab[i].bonus[0] = '\0'; i++;
        }
    tab[i].numero = -1; strcpy(tab[i++].bonus, "x2");
    tab[i].numero = -2; strcpy(tab[i++].bonus, "+2");
    tab[i].numero = -3; strcpy(tab[i++].bonus, "+4");
    tab[i].numero = -4; strcpy(tab[i++].bonus, "+6");
    tab[i].numero = -5; strcpy(tab[i++].bonus, "+8");
    tab[i].numero = -6; strcpy(tab[i++].bonus, "+10");
}

int melanger(cartes *tab, int taille) {
    if (tab == NULL || taille <= 0) return 0;
    for (int i = taille - 1; i > 0; i--) {
        int j      = rand() % (i + 1);
        cartes tmp = tab[i]; tab[i] = tab[j]; tab[j] = tmp;
    }
    return 1;
}

int effetNumero(int numero, int score) {
    if (numero < 0 || numero > 12 || score < 0) exit(1);
    return score + numero;
}

int effetBonus(char *bonus, int score) {
    if (bonus == NULL || score < 0) exit(2);
    if (strcmp(bonus, "x2")  == 0) return score * 2;
    if (strcmp(bonus, "+2")  == 0) return score + 2;
    if (strcmp(bonus, "+4")  == 0) return score + 4;
    if (strcmp(bonus, "+6")  == 0) return score + 6;
    if (strcmp(bonus, "+8")  == 0) return score + 8;
    if (strcmp(bonus, "+10") == 0) return score + 10;
    return score;
}

int carteExisteManche(cartes *main, int debut, int taille, cartes carte) {
    if (main == NULL) exit(4);
    for (int i = debut; i < debut + taille; i++)
        if (main[i].numero == carte.numero) return 1;
    return 0;
}

/* Compte les numéros (sans bonus) depuis le début de la manche */
int compterNumeros(joueur *j) {
    if (j == NULL) exit(3);
    int count = 0;
    for (int m = j->debutManche; m < j->nb_cartes; m++)
        if (j->cartes[m].bonus[0] == '\0') count++;
    return count;
}

/* Calcul du score final selon les règles officielles : */
int calculerScoreFinal (joueur *j, int elimine){
    int score = 0;
    int debut = j->debutManche;
    int fin = j->debutManche + j->nbCartesManche;
    if(fin > j->nb_cartes){
        fin = j->nb_cartes;
    }

    if(debut >= fin){
        return 0;
    }
    if (elimine == 0){
    for (int i=debut; i<fin; i++){
        if (j->cartes[i].bonus[0] == '\0'){
            score = effetNumero(j->cartes[i].numero, score);// ou score =+j->cartes[i].numero mais necessite de changer ou supprimer la fonction effetNumero
        }
    }
    }
    for (int i=debut; i<fin; i++){
        if (j->cartes[i].bonus[0] != '\0'){
            score = effetBonus(j->cartes[i].bonus, score);
        }
    }
    return score;
}

// ============================================================
// FONCTIONS D'AFFICHAGE
// ============================================================


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

    for(int ligne = 0; ligne < 5; ligne++){ //première rangée de carte
        for (int i = 0; i <= 6; i++){
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

void afficherFinPartie(joueur *joueurs, int nb_joueur, int TAILLE) {
    printf("\n\n");
    printf(ROUGE_GRAS " FIN  DE  LA PARTIE" RESET "\n\n");
    if (TAILLE <= 0)
        printf(JAUNE_GRAS " LA PIOCHE EST VIDE...\n Le moment de découvrir les résultats est arrivé !\n" RESET);
    else
        printf(JAUNE_GRAS " UN JOUEUR A ATTEINT 200 POINTS !\n Le moment de découvrir les résultats est arrivé !\n" RESET);

    printf("\n  Appuyez sur [Entree] pour afficher le classement final...");
    getchar();

    int maxFinal = -1;
    int indexGagnant = 0;
    for (int j = 0; j < nb_joueur; j++) {
        if (joueurs[j].score_total > maxFinal) {
            maxFinal = joueurs[j].score_total;
            indexGagnant = j;
        }
    }

    printf("\n " JAUNE_GRAS " 🏆 LE VAINQUEUR EST : %s !" RESET, joueurs[indexGagnant].pseudo);
    printf("\n " BLANC_GRAS " Avec un score total de %d points." RESET "\n", maxFinal);
    printf("\n" OR " ────────────────────────────────────────────" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        if (j == indexGagnant)
            printf(" - " JAUNE_GRAS "%-10s : %d pts (VAINQUEUR)" RESET "\n", joueurs[j].pseudo, joueurs[j].score_total);
        else
            printf(" - %-10s : %d pts\n", joueurs[j].pseudo, joueurs[j].score_total);
    }
    printf(OR" ────────────────────────────────────────────" RESET "\n\n");
}

// ============================================================
// FONCTION MANCHE
// ============================================================

void manche(cartes *tab, int nb_joueur, joueur *joueurs, int *taille, int *dernierePioche) {
    if (tab == NULL || joueurs == NULL || nb_joueur <= 0) exit(5);

    int nb_tour = 0;
    int n       = *dernierePioche;
    int sortir;
    int verif;
    int flip7        = 0;
    int joueur_actif = 0;

    int *arret   = malloc(nb_joueur * sizeof(int));
    int *elimine = malloc(nb_joueur * sizeof(int));
    if (arret == NULL || elimine == NULL) { printf("Erreur allocation\n"); exit(1); }

    /* Initialisation de la manche */
    for (int l = 0; l < nb_joueur; l++) {
        joueurs[l].scores         = 0;
        arret[l]                  = 0;
        joueurs[l].flip7          = 0;
        elimine[l]                = 0;
        joueurs[l].nbCartesManche = 0;
        joueurs[l].score_pot      = 0;
        joueurs[l].debutManche    = joueurs[l].nb_cartes;
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
                        printf("  %s que voulez vous faire ?\n  [1] : Piocher\n", joueurs[j].pseudo);
                    else
                        printf("  %s que voulez vous faire ?\n  [1] : Piocher || [2] : S'arrêter\n\n", joueurs[j].pseudo);
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
                cartes c = joueurs[j].cartes[joueurs[j].nb_cartes];
                int debut = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;

                afficher_cartepiochée(c);

                /* Doublon ? */
                if (carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, c)) {
                    printf("\n");
                    printf(ROUGE_GRAS " 💀  DOUBLON !" RESET "\n");
                    printf(" Aïe ! vous venez de piocher un %d alors que vous en aviez déjà un.\n", c.numero);
                    printf(" Vous êtes éliminé pour le reste de la manche.\n");
                    /* Score = 0, bonus non appliqués (elimine = 1) */
                    printf("\n  " ROUGE_GRAS "Votre score pour cette manche est donc de 0." RESET "\n\n");
                    joueurs[j].scores    = 0;
                    joueurs[j].score_pot = 0;
                    elimine[j]           = 1;
                    joueurs[j].nb_cartes++;
                } else {
                    /* Carte valide : on applique seulement les numéros en temps réel */
                    if (c.bonus[0] == '\0')
                        joueurs[j].scores = effetNumero(c.numero, joueurs[j].scores);
                    joueurs[j].nb_cartes++;
                    joueurs[j].nbCartesManche++;

                    /* Score potentiel calculé avec les règles officielles */
                    joueurs[j].score_pot = calculerScoreFinal(&joueurs[j], 0);

                    /* Test Flip 7 */
                    int nbNumeros = compterNumeros(&joueurs[j]);
                    if (nbNumeros >= 7 && c.bonus[0] == '\0') {
                        printf("  " JAUNE_GRAS "★ FLIP 7 !" RESET "\n");
                        printf(" Vous venez de collecter 7 numéros différents ! Un bonus vous est accordé !\n");
                        printf("\n  %d + " JAUNE_GRAS "15" RESET " = " BLANC_GRAS "%d" RESET "\n\n",
                               joueurs[j].score_pot, joueurs[j].score_pot + 15);
                        joueurs[j].flip7     = 1;
                        flip7                = 1;
                        n++;
                        (*taille)--;
                        break;
                    } else {
                        printf("  " JAUNE_GRAS "✦ Nouvelle carte obtenue !" RESET "\n");
                        if (c.bonus[0] == '\0')
                            printf("  Score : %d + %d = " BLANC_GRAS "%d pts" RESET "\n\n",
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

// ============================================================
// SAUVEGARDE
// ============================================================

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

// ============================================================
// MAIN
// ============================================================

int main() {
    srand(time(NULL));
    int nb_manche      = 1;
    int TAILLE         = 85;
    int dernierePioche = 0;
    int fin            = 1;
    int nb_joueur;
    joueur *joueurs;
    cartes tab[85];
    int verif;

    corrigeTab(tab);
    melanger(tab, TAILLE);

    afficher_accueil();

    /* Saisie du nombre de joueurs */
    do {
        printf(" Combien de joueurs ? ");
        verif = scanf("%d", &nb_joueur);
        vide_buffer();
    } while (nb_joueur <= 0 || verif != 1);

    joueurs = malloc(nb_joueur * sizeof(joueur));
    if (joueurs == NULL) { printf("Erreur allocation\n"); return 1; }

    /* Saisie des pseudos */
    for (int i = 0; i < nb_joueur; i++) {
        printf(" Joueur %d quel est votre pseudo ? ", i + 1);
        scanf(" %s", joueurs[i].pseudo);
        vide_buffer();
        printf("\n");
        printf(" Bienvenue %s !\n", joueurs[i].pseudo);
    }

    /* Initialisation des scores totaux */
    for (int a = 0; a < nb_joueur; a++) {
        joueurs[a].nb_cartes   = 0;
        joueurs[a].score_total = 0;
        joueurs[a].debutManche = 0;
    }

    /* Boucle principale de la partie */
    do {
        printf("\n"); 
        printf(JAUNE_GRAS " MANCHE  N°%d " RESET "\n\n", nb_manche);
        manche(tab, nb_joueur, joueurs, &TAILLE, &dernierePioche);
        nb_manche++;

        /* Calcul des scores totaux et du leader */
        int maxScore    = -1;
        int indexLeader = 0;
        for (int j = 0; j < nb_joueur; j++) {
            joueurs[j].score_total += joueurs[j].score_pot;
            if (joueurs[j].score_total > maxScore) {
                maxScore    = joueurs[j].score_total;
                indexLeader = j;
            }
            if (joueurs[j].score_total >= 200) fin = 0;
        }

        /* Affichage des scores entre les manches si la partie continue */
        if (fin != 0 && TAILLE > 0)
            afficherScoresManche(joueurs, nb_joueur, indexLeader, TAILLE);

    } while (fin != 0 && TAILLE > 0);

    /* Fin de partie */
    afficherFinPartie(joueurs, nb_joueur, TAILLE);

    /* Proposition de sauvegarde */
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
