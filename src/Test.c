#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define ROUGE_GRAS  "\x1b[1;31m"
#define VERT_GRAS   "\x1b[1;32m"
#define JAUNE_GRAS  "\x1b[1;93m"
#define OR          "\x1b[33m"
#define BLANC       "\x1b[97m"
#define BLANC_GRAS  "\x1b[1;37m"
#define RESET       "\x1b[0m"
#define BG_WHITE    "\033[47m"
#define BG_GOLD     "\033[43m"
#define TEXT_BLACK  "\033[30m"
#define MAGENTA_GRAS "\x1b[38;5;202m"

typedef struct{
    int numero;
    char bonus[5];
} cartes;

typedef struct{
    char pseudo[100];
    int scores;
    cartes cartes[85];
    int nb_cartes;
    int score_total;
    int nbCartesManche;
    int score_pot;
} joueur;

// ============================================================
// FONCTIONS UTILITAIRES
// ============================================================

void pause() {
    printf("  Appuyez sur [Entree] pour passer au joueur suivant.\n");
    while (getchar() != '\n'); 
    getchar();                
}

void corrigeTab(cartes tab[]){
    int i = 0;
    tab[i].numero = 0;
    tab[i].bonus[0] = '\0';
    i++;
    tab[i].numero = 1;
    tab[i].bonus[0] = '\0';
    i++;
    for(int n = 2; n <= 12; n++){
        for(int j = 0; j < n; j++){
            tab[i].numero = n;
            tab[i].bonus[0] = '\0';
            i++;
        }
    }
    tab[i].numero = -1;  strcpy(tab[i++].bonus, "x2");
    tab[i].numero = -2;  strcpy(tab[i++].bonus, "+2");
    tab[i].numero = -3;  strcpy(tab[i++].bonus, "+4");
    tab[i].numero = -4;  strcpy(tab[i++].bonus, "+6");
    tab[i].numero = -5;  strcpy(tab[i++].bonus, "+8");
    tab[i].numero = -6;  strcpy(tab[i++].bonus, "+10");
}

void melanger(cartes tab[], int taille){
    for(int i = taille - 1; i > 0; i--){
        int j = rand() % (i + 1);
        cartes temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}

int effetNumero(int numero, int score){
    score += numero;
    return score;
}

int carteExisteManche(cartes main[], int debut, int taille, cartes carte) {
    for (int i = debut; i < debut + taille; i++) {
        if (main[i].numero == carte.numero) {
            return 1;
        }
    }
    return 0;
}

int calculerScoreFinal(joueur *j) {
    int scoreNumeros = 0;
    int aX2          = 0;
    int bonusPlus    = 0;

    int debut = j->nb_cartes - j->nbCartesManche;

    for (int m = debut; m < j->nb_cartes; m++) {
        cartes c = j->cartes[m];

        if (c.bonus[0] == '\0') {
            scoreNumeros += c.numero;
        } else if (strcmp(c.bonus, "x2")  == 0) {
            aX2 = 1;
        } else if (strcmp(c.bonus, "+2")  == 0) bonusPlus += 2;
        else if  (strcmp(c.bonus, "+4")  == 0) bonusPlus += 4;
        else if  (strcmp(c.bonus, "+6")  == 0) bonusPlus += 6;
        else if  (strcmp(c.bonus, "+8")  == 0) bonusPlus += 8;
        else if  (strcmp(c.bonus, "+10") == 0) bonusPlus += 10;
    }

    
    if (aX2) scoreNumeros *= 2;

    return scoreNumeros + bonusPlus;
}

// ============================================================
// FONCTIONS D'AFFICHAGE
// ============================================================

void afficherAccueil() {
    printf("\n");
    printf(ROUGE_GRAS "  ╔════════════════════════════════════════╗\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ║" JAUNE_GRAS "               FLIPTECH                 " ROUGE_GRAS "║\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ╚════════════════════════════════════════╝\n\n" RESET);
}

void afficherHeaderTour(joueur joueurs[], int j, int tour) {
    printf("\n");
    printf(OR "  ┌──────────────────────────────────────────────────────────────────────────────┐" RESET "\n");
    printf(OR "  │ " ROUGE_GRAS  " AU TOUR DE %-20s" RESET, joueurs[j].pseudo);
    printf(OR "                                    Tour n°%d │" RESET "\n" , tour);
    printf(OR "  └──────────────────────────────────────────────────────────────────────────────┘" RESET "\n");
    printf("\n");
}

void afficherMain(joueur joueurs[], int j) {
    printf(MAGENTA_GRAS "  Vos cartes en main :\n" RESET);

    int n_main      = joueurs[j].nbCartesManche;
    int debutManche = joueurs[j].nb_cartes - n_main;

    if (n_main > 0) {
        for (int m = 0; m < n_main; m++) {
            printf(OR " ┌─────┐" RESET " ");
        }
        printf("\n");
        for (int m = 0; m < n_main; m++) {
            int index = debutManche + m;
            if (joueurs[j].cartes[index].bonus[0] == '\0'){
                printf(OR " │" BG_WHITE "     " RESET OR "│" RESET " ");
            }else{
                printf(OR " │" BG_GOLD  "     " RESET OR "│" RESET " ");
            }
        }
        printf("\n");
        for (int m = 0; m < n_main; m++) {
            int index = debutManche + m;
            if (joueurs[j].cartes[index].bonus[0] == '\0') {
                printf(OR " │" BG_WHITE TEXT_BLACK " %2d  " RESET OR "│" RESET " ", joueurs[j].cartes[index].numero);
            } else {
                printf(OR " │" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET " ", joueurs[j].cartes[index].bonus);
            }
        }
        printf("\n");
        for (int m = 0; m < n_main; m++) {
            int index = debutManche + m;
            if (joueurs[j].cartes[index].bonus[0] == '\0'){
                printf(OR " │" BG_WHITE "     " RESET OR "│" RESET " ");
            }else{
                printf(OR " │" BG_GOLD  "     " RESET OR "│" RESET " ");
            }
        }
        printf("\n");
        for (int m = 0; m < n_main; m++) {
            printf(OR " └─────┘" RESET " ");
        }
    }
    printf("\n");
}

void afficherStats(cartes tab[], int n) {
    cartes compteur[13] = {0};
    for (int b = 0; b < n; b++) {
        if (tab[b].numero >= 0 && tab[b].numero <= 12) {
           compteur[tab[b].numero].numero++;
        }
    }

    printf("\n");
    printf(MAGENTA_GRAS "  Statistiques — cartes déjà sorties\n" RESET);

    for (int w = 0; w <= 6; w++){
        printf(OR "┌─────┐" RESET "  ");
    }
    printf("\n");
    for (int w = 0; w <= 6; w++) {
        printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", w);
    }
    printf("\n");
    for (int w = 0; w <= 6; w++){
        printf(OR "│  -  │" RESET "  ");
    }
    printf("\n");
    for (int w = 0; w <= 6; w++) {
        int total_w = (w == 0) ? 1 : w;
        printf(OR "│" RESET JAUNE_GRAS " %d/%-2d" RESET OR "│" RESET "  ", compteur[w].numero, total_w);
    }
    printf("\n");
    for (int w = 0; w <= 6; w++){
        printf(OR "└─────┘" RESET "  ");
    }
    printf("\n");

    for (int w = 7; w <= 12; w++){
        printf(OR "┌─────┐" RESET "  ");
    }
    printf("\n");
    for (int w = 7; w <= 12; w++) {
        printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", w);
    }
    printf("\n");
    for (int w = 7; w <= 12; w++){
        printf(OR "│  -  │" RESET "  ");
    }
    printf("\n");
    for (int w = 7; w <= 12; w++) {
        printf(OR "│" RESET JAUNE_GRAS" %d/%-2d" RESET OR "│" RESET "  ", compteur[w].numero, w);
    }
    printf("\n");
    for (int w = 7; w <= 12; w++){
        printf(OR "└─────┘" RESET "  ");
    }
    printf("\n\n");
}

void afficherRisque(joueur joueurs[], int j, cartes tab[], int n, int taille) {
    int stats_danger[13] = {0};
    for(int s = 0; s < n; s++){
        if(tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12){
            stats_danger[tab[s].numero]++;
        }
    }

    int dangerTotal = 0;
    printf(MAGENTA_GRAS "  ANALYSE DU RISQUE \n\n" RESET);

    int debutMain = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;
    for(int c = 0; c < joueurs[j].nbCartesManche; c++){
        int index = debutMain + c;
        if(joueurs[j].cartes[index].bonus[0] != '\0') continue;
        int num_carte = joueurs[j].cartes[index].numero;
        int totalmain;
        if(num_carte == 0 || num_carte == 1){
           totalmain = 1;
        }else{
             totalmain = num_carte;
        }
        int restantes = totalmain - stats_danger[num_carte];
        if (restantes < 0){
             restantes = 0;
        }
        dangerTotal += restantes;
        printf("  - Carte" JAUNE_GRAS" %d"RESET " : " ROUGE_GRAS "%d " RESET "encore dans la pioche\n", num_carte, restantes);
    }

    float risque = 0;
    if (taille > 0) {
        risque = (dangerTotal * 100.0) / taille;
    }

    printf("  Total cartes dangereuses :" BLANC_GRAS"%d"RESET " sur " BLANC_GRAS"%d "RESET "cartes restantes\n", dangerTotal, taille);
    printf("  Probabilite de doublon : ");
    if (risque < 20.0f) {
        printf(VERT_GRAS "%.1f%%\n" RESET, risque);
    } else if (risque < 37.0f) {
        printf(JAUNE_GRAS "%.1f%%\n" RESET, risque);
    } else {
        printf(ROUGE_GRAS "%.1f%%\n" RESET, risque);
    }

    printf("\n  Conseil : ");
    if (risque < 20.0f) {
        printf(VERT_GRAS "Risque faible — Piochez en toute tranquillite !\n" RESET);
    } else if (risque < 37.0f) {
        printf(JAUNE_GRAS "Risque moyen — Reflechissez bien avant de piocher.\n" RESET);
    } else {
        printf(ROUGE_GRAS "Risque eleve — Il serait préférable de vous arreter !\n" RESET);
    }
}

void afficherCartePiochee(cartes c) {
    printf("  Vous venez de piocher la carte :\n");
    printf(OR "  ┌─────┐" RESET "\n");
    if (c.bonus[0] == '\0') {
        printf(OR "  │" BG_WHITE "     " RESET OR "│" RESET "\n");
        printf(OR "  │" BG_WHITE TEXT_BLACK "  %2d " RESET OR "│" RESET "\n", c.numero);
        printf(OR "  │" BG_WHITE "     " RESET OR "│" RESET "\n");
    } else {
        printf(OR "  │" BG_GOLD "     " RESET OR "│" RESET "\n");
        printf(OR "  │" BG_GOLD TEXT_BLACK " %-3s " RESET OR "│" RESET "\n", c.bonus);
        printf(OR "  │" BG_GOLD "     " RESET OR "│" RESET "\n");
    }
    printf(OR "  └─────┘" RESET "\n");
}

void afficherDoublon(cartes c) {
    printf("  " ROUGE_GRAS "💀  DOUBLON !" RESET "\n");
    printf("  Aïe ! vous venez de piocher un %d alors que vous en aviez déjà un.\n", c.numero);
    printf("Vous êtes éliminé pour le reste de la manche.\n");
    printf("\n  " ROUGE_GRAS "Votre score pour cette manche est donc de 0." RESET "\n\n");
}

void afficherNouvelleCarteObtenue(cartes c, int scoreAvant, int scoreApres) {
    printf("  " JAUNE_GRAS "✦ Nouvelle carte obtenue ! " RESET "\n");
    if (c.bonus[0] == '\0') {
        printf("  Score : %d + %d = " BLANC_GRAS "%d pts" RESET "\n\n", 
                scoreAvant, c.numero, scoreApres);
    } else {
        // Affichage informatif du bonus reçu — il sera appliqué en fin de manche
        printf("  Bonus " JAUNE_GRAS "%s" RESET " obtenu ! Il sera appliqué à la fin de la manche.\n\n", c.bonus);
    }
}

void afficherFlip7(int scoreSansBon, int scoreAvecBonus) {
    printf("  " JAUNE_GRAS "★ FLIP 7 !" RESET "\n");
    printf("  Wow ! Vous avez collecté 7 numéros différents ! Bonus accordé !\n");
    printf("\n  %d + " JAUNE_GRAS "15" RESET " = " BLANC_GRAS "%d" RESET "\n\n", 
            scoreSansBon, scoreAvecBonus);
}

void afficherScoresManche(joueur joueur[], int nb_joueur, int indexLeader, int TAILLE) {
    printf("\n  " MAGENTA_GRAS "SCORES" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        printf("\n  " BLANC_GRAS "★ %s" RESET, joueur[j].pseudo);
        printf("\n  Score manche : %d", joueur[j].score_pot);
        if (joueur[j].score_pot == 0) printf(ROUGE_GRAS " (Doublon)" RESET);
        else if (joueur[j].nbCartesManche >= 7) printf(VERT_GRAS " (Flip 7 )" RESET);
        printf("\n  " OR "SCORE TOTAL : %d" RESET "\n", joueur[j].score_total);
    }
    printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
    printf("  Nombre de cartes restantes dans la pioche : %d\n", TAILLE);
    printf("  " JAUNE_GRAS "%s est en tête avec %d points !" RESET "\n", 
            joueur[indexLeader].pseudo, joueur[indexLeader].score_total);
    printf("  " OR "────────────────────────────────────────────" RESET "\n\n");
}

void afficherFinPartie(joueur joueur[], int nb_joueur, int TAILLE) {
    printf("\n\n");
    printf(ROUGE_GRAS "  F I N   D E   P A R T I E" RESET "\n\n");
    if (TAILLE <= 0) {
        printf(JAUNE_GRAS "  LA PIOCHE EST VIDE...\n  Le moment de découvrir les résultats est arrivé !\n " RESET);
    } else {
        printf(JAUNE_GRAS "  UN JOUEUR A ATTEINT LES 200 POINTS...\n  Le moment de découvrir les résultats est arrivé !\n " RESET);
    }

    printf("\n  Appuyez sur [Entree] pour afficher le classement final...");
    while (getchar() != '\n'); 
    getchar(); 

    int maxFinal    = -1;
    int indexGagnant = 0;
    for (int j = 0; j < nb_joueur; j++) {
        if (joueur[j].score_total > maxFinal) {
            maxFinal     = joueur[j].score_total;
            indexGagnant = j;
        }
    }

    printf("\n  " JAUNE_GRAS "  🏆 LE GRAND VAINQUEUR EST : %s !" RESET, joueur[indexGagnant].pseudo);
    printf("\n  " BLANC_GRAS "  Avec un score total de %d points." RESET "\n", maxFinal);
    printf("\n  " OR "────────────────────────────────────────────" RESET "\n");
    for (int j = 0; j < nb_joueur; j++) {
        if (j == indexGagnant) {
            printf("  - " JAUNE_GRAS "%-10s : %d pts (VAINQUEUR)" RESET "\n", joueur[j].pseudo, joueur[j].score_total);
        } else {
            printf("  - %-10s : %d pts\n", joueur[j].pseudo, joueur[j].score_total);
        }
    }
    printf("  " OR "────────────────────────────────────────────" RESET "\n\n");
}

// ============================================================
// FONCTIONS DE JEU
// ============================================================

void initialiserManche(joueur joueurs[], int nb_joueur, int penalise[]) {
    for (int l = 0; l < nb_joueur; l++){
        joueurs[l].scores         = 0;
        penalise[l]               = 0;
        joueurs[l].nbCartesManche = 0;
        joueurs[l].score_pot      = 0;
        joueurs[l].nb_cartes      = 0; // repart à 0 à chaque manche
    }
}

int tousLesjoueursPenalises(int penalise[], int nb_joueur) {
    for (int k = 0; k < nb_joueur; k++)
        if (penalise[k] == 0) return 0;
    return 1;
}

// Retourne 1 si Flip 7 déclenché, 0 sinon
int traiterCartePiochee(joueur joueurs[], int j, cartes c, int penalise[], int *n) {
    int scoreAvant = joueurs[j].score_pot;
    int debut      = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;

    afficherCartePiochee(c);

    // Cas doublon
    if (carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, c)) {
        afficherDoublon(c);
        joueurs[j].scores    = 0;
        joueurs[j].score_pot = 0;
        penalise[j]          = 1;
        joueurs[j].nb_cartes++;
        return 0;
    }

    // Carte valide : on enregistre la carte dans la main
    joueurs[j].cartes[joueurs[j].nb_cartes] = c;

    // On applique seulement les numéros en temps réel
    // Les bonus sont stockés et calculés en fin de manche via calculerScoreFinal()
    if(c.bonus[0] == '\0'){
        joueurs[j].scores = effetNumero(c.numero, joueurs[j].scores);
    }

    joueurs[j].nb_cartes++;
    joueurs[j].nbCartesManche++;

    joueurs[j].score_pot = calculerScoreFinal(&joueurs[j]);

    // Comptage des numéros uniquement pour le test Flip 7
    int nbNumeros    = 0;
    int debutMancheC = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;
    for (int m = debutMancheC; m < joueurs[j].nb_cartes; m++) {
        if (joueurs[j].cartes[m].bonus[0] == '\0') {
            nbNumeros++;
        }
    }

    // Test Flip 7 : 7 numéros différents ET la carte déclenchante est un numéro
    if (nbNumeros >= 7 && c.bonus[0] == '\0') {
        afficherFlip7(joueurs[j].score_pot, joueurs[j].score_pot + 15);
        joueurs[j].score_pot += 15;
        (*n)++;
        return 1; // Flip 7 déclenché
    }

    // Carte normale ou bonus obtenu
    afficherNouvelleCarteObtenue(c, scoreAvant, joueurs[j].score_pot);
    return 0;
}

// Retourne 1 si un joueur a atteint 200 points, 0 sinon
int verifierFinPartie(joueur joueurs[], int nb_joueur) {
    for (int j = 0; j < nb_joueur; j++) {
        if (joueurs[j].score_total + joueurs[j].score_pot >= 200) {
            return 1;
        }
    }
    return 0;
}

void manche(cartes tab[], int nb_joueur, joueur joueurs[], int *taille, int *dernierePioche, int *finPartie){
    int nb_tour = 0;
    int n       = *dernierePioche;
    int sortir;
    int penalise[50];

    initialiserManche(joueurs, nb_joueur, penalise);

    for(int i = 0; i < 15; i++){
        nb_tour++;

        // Si tous les joueurs sont pénalisés ou arrêtés on arrête la manche
        if (tousLesjoueursPenalises(penalise, nb_joueur)) break;

        for(int j = 0; j < nb_joueur; j++){

            // Pioche vide : on arrête immédiatement
            if (*taille == 0) {
                *dernierePioche = n;
                return;
            }

            if (penalise[j] == 1){
                continue;
            }

            // Boucle de saisie du choix du joueur
            do {
                afficherHeaderTour(joueurs, j, i + 1);

                if (joueurs[j].nbCartesManche >= 1) {
                    afficherMain(joueurs, j);
                    printf("\n");
                    printf("  Votre score potentiel : %d\n  ",
                            joueurs[j].score_pot);
                    afficherStats(tab, n);
                    afficherRisque(joueurs, j, tab, n, *taille);
                }

                if (nb_tour <= 1){
                    printf("  %s que voulez vous faire ?\n  [1] : Piocher\n",
                            joueurs[j].pseudo);
                } else {
                    printf("  %s que voulez vous faire ?\n  [1] : Piocher || [2] : S'arrêter\n\n",
                            joueurs[j].pseudo);
                }
                printf("  ────────────────────────────────────────");

                scanf("%d", &sortir);

            } while (sortir != 1 && sortir != 2);

            if (sortir == 2) {
                penalise[j] = 1;
            } else {
                // On récupère la carte du dessus de la pioche
                cartes c = tab[n];

                // On traite la carte : doublon, flip7, ou carte normale
                int flip7 = traiterCartePiochee(joueurs, j, c, penalise, &n);

                // Vérification immédiate si un joueur atteint 200 pts
                if (verifierFinPartie(joueurs, nb_joueur)) {
                    printf(JAUNE_GRAS "\n  ★ Un joueur vient d'atteindre 200 points ! La partie s'arrête !\n" RESET);
                    *finPartie      = 1;
                    (*taille)--;
                    n++;
                    *dernierePioche = n;
                    return;
                }

                if (flip7) {
                    i = 15; // Force la fin de la boucle des tours
                    break;
                }

                if (sortir == 1) { 
                    pause(); 
                }
                (*taille)--;
                n++;
            }
        }
    }

    *dernierePioche = n;
}

// ============================================================
// SAUVEGARDE
// ============================================================

void CahierDesCharges(int nb_joueur, joueur joueurs[], char nom[]) {
    FILE *f = NULL;
    char nomComplet[100];
    sprintf(nomComplet, "%s.txt", nom); 
    f = fopen(nomComplet, "w"); 
    if (f == NULL) {
        printf("Erreur : Impossible de créer le fichier %s\n", nomComplet);
        return;
    }
    for (int i = 0; i < nb_joueur; i++) {
        fprintf(f, "  Joueur : %s | Score Final : %d\n", joueurs[i].pseudo, joueurs[i].score_total);
        fprintf(f, "  Cartes obtenues : ");
        for (int j = 0; j < joueurs[i].nb_cartes; j++) {
            if (joueurs[i].cartes[j].bonus[0] == '\0') {
                fprintf(f, "[%d] ", joueurs[i].cartes[j].numero);
            } else {
                fprintf(f, "[%s] ", joueurs[i].cartes[j].bonus);
            }
        }
        fprintf(f, "\n  ──────────────────────────────\n");
    }
    fclose(f);
    printf("La partie a ete sauvegardee sous le nom : %s\n", nomComplet);
}

// ============================================================
// MAIN
// ============================================================

int main(){
    srand(time(NULL));
    int nb_manche      = 1;
    int TAILLE         = 85;
    int dernierePioche = 0;
    int fin            = 0; // 0 = partie en cours, 1 = partie terminée
    int nb_joueur;
    joueur joueur[50];
    cartes tab[85];

    corrigeTab(tab);
    melanger(tab, TAILLE);

    // Ecran d'accueil
    afficherAccueil();

    // Saisie du nombre de joueurs et de leurs pseudos
    printf("  Combien de joueurs ? ");
    scanf("%d", &nb_joueur);
    for (int i = 0; i < nb_joueur; i++){
        printf("  Joueur %d quel est votre pseudo ? ", i+1);
        scanf(" %s", joueur[i].pseudo);
        printf("  Prénom du joueur %d est %s !\n", i+1, joueur[i].pseudo);
    }

    // Initialisation des scores totaux
    for (int a = 0; a < nb_joueur; a++){
        joueur[a].nb_cartes   = 0;
        joueur[a].score_total = 0;
    }

    // Boucle principale de la partie
    do {
        printf("\n  " OR "  M A N C H E  N°%d " RESET "\n\n", nb_manche);

        manche(tab, nb_joueur, joueur, &TAILLE, &dernierePioche, &fin);
        nb_manche++;

        // Calcul des scores totaux et du leader
        int maxScore    = -1;
        int indexLeader = 0;
        for (int j = 0; j < nb_joueur; j++) {
            joueur[j].score_total += joueur[j].score_pot;
            if (joueur[j].score_total > maxScore) {
                maxScore    = joueur[j].score_total;
                indexLeader = j;
            }
            // Vérification si un joueur atteint 200 pts
            if (joueur[j].score_total >= 200) {
                fin = 1;
            }
        }

        // Affichage des scores entre les manches si la partie continue
        if (fin == 0 && TAILLE > 0) {
            afficherScoresManche(joueur, nb_joueur, indexLeader, TAILLE);
        }

    } while (fin == 0 && TAILLE > 0);

    // Affichage de la fin de partie et du classement
    afficherFinPartie(joueur, nb_joueur, TAILLE);

    // Proposition de sauvegarde
    char enregistrer;
    do {
        printf("Voulez-vous enregistrer les scores de la partie ? o(oui) ou n(non)\n");
        scanf(" %c", &enregistrer);
    }
    while (enregistrer != 'o' && enregistrer != 'n');

    if (enregistrer == 'o') {
        char nom_fichier[50];
        printf("Quel nom voulez-vous donner au fichier ? (sans extension)\n");
        scanf("%s", nom_fichier);
        CahierDesCharges(nb_joueur, joueur, nom_fichier);
    }

    return 0;
}
