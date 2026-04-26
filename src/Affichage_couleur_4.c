#include <stdio.h>
#include<stdlib.h>
#include<time.h>
//#define TAILLE 85
#include<string.h>
#define ROUGE_GRAS  "\x1b[1;31m"
#define VERT_GRAS   "\x1b[1;32m"
#define JAUNE_GRAS  "\x1b[1;93m"
#define OR      "\x1b[33m"
#define BLANC   "\x1b[97m"
#define BLANC_GRAS  "\x1b[1;37m"
#define RESET   "\x1b[0m"
#define BG_WHITE   "\033[47m"  // Fond blanc pour les numéros
#define BG_GOLD    "\033[43m"  // Fond jaune pour les bonus
#define TEXT_BLACK "\033[30m"  // Texte noir sur les fonds clairs
#define BLEU_GRAS     "\x1b[1;34m"  // Calme, professionnel
#define CYAN_GRAS     "\x1b[1;36m"  // Très lisible, idéal pour les scores
#define MAGENTA_GRAS  "\x1b[1;35m"  // Pour les noms de joueurs ou les annonces

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

void affichage(cartes tab[], int taille){
int i;
for (i=0; i<taille; i++){
    if (tab[i].bonus[0]=='\0'){
        printf ("%d ", tab[i].numero);
    }
    else {
        printf ("%s ", tab[i].bonus);
    }
}
printf ("\n");
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
int effetBonus(char *bonus, int score){
    if(strcmp(bonus, "x2") == 0){
        score = score * 2;
    }
    else if(strcmp(bonus, "+2") == 0){
        score += 2;
    }
    else if(strcmp(bonus, "+4") == 0){
        score += 4;
    }
    else if(strcmp(bonus, "+6") == 0){
        score += 6;
    }
    else if(strcmp(bonus, "+8") == 0){
        score += 8;
    }
    else if(strcmp(bonus, "+10") == 0){
        score += 10;
    }

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
/*void stats (cartes pioche[], int piochées){
    int stats [13];
    
}*/
void manche(cartes tab[], int nb_joueur, joueur joueurs[], int *taille, int *dernierePioche){
    
    int i, j, t;
    int nb_tour = 0;
    int n = *dernierePioche;
    int sortir;
    int penalise[50];
    int cartesPiochées = 0;
    int nb_manche = 1;
    
    for (int l=0; l<nb_joueur; l++){
        joueurs[l].scores = 0;
        penalise[l] = 0;
        joueurs[l].nbCartesManche = 0;
        joueurs[l].score_pot = 0;
    }

    for(int i=0; i<7; i++){
        nb_tour++;

        for(int j=0; j<nb_joueur; j++){
            if ((*taille)==1){
                joueurs[j].scores += 15;

                if(joueurs[j].cartes[joueurs[j].nb_cartes].bonus[0] == '\0'){
                    joueurs[j].scores = effetNumero(
                        joueurs[j].cartes[joueurs[j].nb_cartes].numero,
                        joueurs[j].scores
                    );
                } else {
                    joueurs[j].scores = effetBonus(
                        joueurs[j].cartes[joueurs[j].nb_cartes].bonus,
                        joueurs[j].scores
                    );
                }
            }
            else if ((*taille)==0){
                return;
            }

            if (penalise[j]==1){
                continue;
            }

            do {
                printf("\n");

printf(OR "  ┌──────────────────────────────────────────────────────────────────────────────┐" RESET "\n");

printf(OR "  │ " ROUGE_GRAS  " AU TOUR DE %-20s" RESET, joueurs[j].pseudo);

printf(OR "                                    Tour %d/7 │" RESET "\n", nb_manche , i + 1);

printf(OR "  └──────────────────────────────────────────────────────────────────────────────┘" RESET "\n");
printf("\n");


                if (joueurs[j].nbCartesManche >= 1) {

  printf(MAGENTA_GRAS "  Vos cartes en main :\n" RESET);

int n_main = joueurs[j].nbCartesManche;
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
                    //cartesPiochées++;

                    printf ("\n");
                    printf ("  Votre score potentiel : %d\n  ────────────────────────────────\n",
                            joueurs[j].score_pot);

                    cartes compteur[13] = {0};
                    /*cartes compteur_cartes_joueurs[50] = {0};
                    for (int y=0; y<=nb_cartes; y++){
                        compteur_cartes_joueurs[joueurs[j].cartes[y]].numero++;
                    }*/
                    for (int b = 0; b <n; b++) {
                        if (tab[b].numero >= 0 && tab[b].numero <= 12) { // <--- IMPORTANTTTTT !!!!!!!
                           compteur[tab[b].numero].numero++;
                        }
                    }
                    printf ("\n");  
    
                       

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
    int total_w;
                        if (w == 0){
                            total_w = 1;
                        }
                        else {
                            total_w = w;
                        }

    printf(OR "│" RESET JAUNE_GRAS " %d/%-2d" RESET OR "│" RESET "  ", compteur[w].numero, total_w);
}
printf("\n");
for (int w = 0; w <= 6; w++){
    printf(OR "└─────┘" RESET "  ");
}
printf("\n");



for (int w = 7; w <= 12; w++){
    printf(OR "┌─────┐" RESET "  ");
} printf("\n");


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
            
int stats_danger[13] = {0};
for(int s = 0; s < n; s++){
    if(tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12){
        stats_danger[tab[s].numero]++;
    }
}                         
         

int dangerTotal = 0;
printf ("  ────────────────────────────────\n");
printf(MAGENTA_GRAS  "  ANALYSE DU RISQUE \n\n" RESET);

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
if (*taille > 0) {
    risque = (dangerTotal * 100.0) / (*taille);
}


printf("  Total cartes dangereuses :" BLANC_GRAS"%d"RESET " sur " BLANC_GRAS"%d "RESET "cartes restantes\n", dangerTotal, *taille);
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
printf("  ──────────────────────────────────────\n\n");
                
               
                
                
                
                
                
                
                
                //if (){
                //printf ("Conseil : Attention , %d cartes %d sont déjà sorties.\nVous en avez %d, il en reste %d dans la pioches",compteur[ ].numero,/*(la variable*/, compteur_cartes_joueurs[joueurs[j].cartes[/*variable*/]].numero,compteur[/*variable*/].numero);
                //}
                if (nb_tour <= 1){
                    printf ("  %s que voulez vous faire ?\n  [1] : Piocher\n",
                            joueurs[j].pseudo);
                } else {
                    printf ("  %s que voulez vous faire ?\n  [1] : Piocher || [2] : S'arrêter\n\n",
                            joueurs[j].pseudo);
                }
                printf("  ────────────────────────────────────────\n");

                scanf ("%d", &sortir);

            } while (sortir != 1 && sortir != 2);

            if (sortir == 2) {
    penalise[j] = 1;
} 
else {
 
    int scoreAvant = joueurs[j].score_pot;
    joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
    cartes c = joueurs[j].cartes[joueurs[j].nb_cartes]; 
    int debut = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;

 
    printf("  Vous venez de piocher la carte :\n", joueurs[j].pseudo);

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

    if (carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, c)) {
        printf("  " ROUGE_GRAS "💀  DOUBLON !" RESET "\n");
        printf("  Aïe ! vous venez de piocher un %d alors que vous en aviez déjà un.\n", c.numero);
        printf("Vous êtes éliminé pour le reste de la manche.\n");
        printf("\n  " ROUGE_GRAS "Votre score pour cette manche est donc de 0." RESET "\n\n");
        
        joueurs[j].scores = 0;
        joueurs[j].score_pot = 0;
        penalise[j] = 1;
        joueurs[j].nb_cartes++;
    } 
    else {
        
        if(c.bonus[0] == '\0'){
            joueurs[j].scores = effetNumero(c.numero, joueurs[j].scores);
        }else{
            joueurs[j].scores = effetBonus(c.bonus, joueurs[j].scores);
        }
        joueurs[j].nb_cartes++;
        joueurs[j].nbCartesManche++;
        joueurs[j].score_pot = joueurs[j].scores;

        if(joueurs[j].nbCartesManche >= 7) {
            printf("  " JAUNE_GRAS "★ FLIP  7 !" RESET "\n");
            printf("  Wow ! Vous venez de collecter 7 cartes différentes ! Un bonus vous a été accordé !\n");
            
            printf("\n  %d + " JAUNE_GRAS "15" RESET " = " BLANC_GRAS "%d" RESET "\n\n", 
                    joueurs[j].score_pot, joueurs[j].score_pot + 15);
            
            joueurs[j].score_pot += 15;
            i = 7; 
            n++;
            break;
        } 
        else {
            printf("  " JAUNE_GRAS "✦ Nouvelle carte obtenue ! " RESET "\n");
            
            if (c.bonus[0] == '\0') {
                printf("  Score : %d + %d = " BLANC_GRAS "%d pts" RESET "\n\n", 
                        scoreAvant, c.numero, joueurs[j].score_pot);
            } else {
                if (strcmp(c.bonus, "x2") == 0)
                    printf("  Score : %d * 2 = " BLANC_GRAS "%d pts" RESET "\n\n", scoreAvant, joueurs[j].score_pot);
                else
                    printf("  Score : %d %s = " BLANC_GRAS "%d pts" RESET "\n\n", scoreAvant, c.bonus, joueurs[j].score_pot);
            }
        }
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

int main(){
    srand(time(NULL));
    int nb_manche = 1;
    //int TAILLE = 20;
    int TAILLE = 85;
    int dernierePioche=0;
    int fin = 1;
    int nb_joueur;
    joueur joueur[50];
    char prénom[50];
    cartes tab[TAILLE];
    corrigeTab(tab);
    //affichage(tab, TAILLE);
    melanger(tab, TAILLE);
    
    
     printf("\n");
    printf(ROUGE_GRAS "  ╔════════════════════════════════════════╗\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ║" JAUNE_GRAS "               FLIPTECH                 " ROUGE_GRAS "║\n" RESET);
    printf(ROUGE_GRAS "  ║                                        ║\n" RESET);
    printf(ROUGE_GRAS "  ╚════════════════════════════════════════╝\n\n" RESET);

    printf( "  Combien de joueurs ? " );
    scanf ("%d", &nb_joueur);
    for (int i=0; i<nb_joueur; i++){
        printf ( "  Joueur %d quel est votre pseudo ?" , i+1);
        scanf (" %s",joueur[i].pseudo);
        //strcpy(joueur[i].pseudo, prénom);
        printf ("  Prénom du joueur %d est %s !\n", i+1, joueur[i].pseudo);
    }
    for (int a=0; a<nb_joueur; a++){
    joueur[a].nb_cartes=0;
    joueur[a].score_total=0;
    }

    do {
    printf("\n  " OR "  M A N C H E  N°%d " RESET "\n\n", nb_manche);

    manche(tab, nb_joueur, joueur, &TAILLE, &dernierePioche);
    
    nb_manche++;

    
    int maxScore = -1;
    int indexLeader = 0;

    for (int j = 0; j < nb_joueur; j++) {
        joueur[j].score_total += joueur[j].score_pot;

        if (joueur[j].score_total > maxScore) {
            maxScore = joueur[j].score_total;
            indexLeader = j;
        }

        if (joueur[j].score_total >= 200) {
            fin = 0; 
        }
    }

    
    if (fin != 0 && TAILLE > 0) {
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
    

} while (fin != 0 && TAILLE > 0);


printf("\n\n");
 printf(ROUGE_GRAS "  F I N   D E   P A R T I E" RESET "\n\n");
    if (TAILLE <= 0) {
        printf( JAUNE_GRAS "  LA PIOCHE EST VIDE...\n  Le moment de découvrir les résultats est arrivé !\n " RESET );
        
    } else {
        
        printf(JAUNE_GRAS "  UN JOUEUR A ATTEINT LES 200 POINTS...\n  Le moment de découvrir les résultats est arrivé !\n " RESET );
    }

    printf("\n  Appuyez sur [Entree] pour afficher le classement final...");
    while (getchar() != '\n'); 
    getchar(); 

   

    int maxFinal = -1;
    int indexGagnant = 0;
    for (int j = 0; j < nb_joueur; j++) {
        if (joueur[j].score_total > maxFinal) {
            maxFinal = joueur[j].score_total;
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



    char enregistrer;
    do {
        printf ("Voulez-vous enregistrer les scores de la partie ? o(oui) ou n(non)\n");
        scanf (" %c", &enregistrer);
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
