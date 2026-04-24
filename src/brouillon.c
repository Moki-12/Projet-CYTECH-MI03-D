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
#define RESET   "\x1b[0m"

typedef struct{
    int numero;
    char bonus[5];
} cartes;
typedef struct{
    char pseudo[1000];
    int scores;
    cartes cartes[50];
    int nb_cartes;
    int score_total;
    int nbCartesManche;
    int score_pot;
} joueur;


void pause() {
    printf("Appuyez sur [Entree] pour passer au joueur suivant.\n");
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

    for (int l=0; l<nb_joueur; l++){
        joueurs[l].scores = 0;
        penalise[l] = 0;
        joueurs[l].nbCartesManche = 0;
        joueurs[l].score_pot = 0;
    }

    for(int i=0; i<7; i++){
        printf ("Tour n°%d : \n", i+1);
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
                printf("\n");
                printf("\n");
                printf(ROUGE_GRAS "************** Au tour de %s ************" RESET "\n", joueurs[j].pseudo);
                printf("\n");
                if (joueurs[j].nbCartesManche >= 1) {

    printf("Vos cartes en main :\n");

    int debutManche = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;

    for (int m = 0; m < joueurs[j].nbCartesManche; m++) {

        int index = debutManche + m;

        if (joueurs[j].cartes[index].bonus[0] == '\0') {
            printf("[%d] ", joueurs[j].cartes[index].numero);
        } else {
            printf("[%s] ", joueurs[j].cartes[index].bonus);
        }
    }

    printf("\n");
                    //cartesPiochées++;

                    printf ("\n");
                    printf ("Votre score potentiel : %d\n----------------------------\n",
                            joueurs[j].score_pot);

                    cartes compteur[13] = {0};
                    /*cartes compteur_cartes_joueurs[50] = {0};
                    for (int y=0; y<=nb_cartes; y++){
                        compteur_cartes_joueurs[joueurs[j].cartes[y]].numero++;
                    }*/
                    for (int b = 0; b <n; b++) {
                        if (tab[b].numero >= 0) { // <--- INDISPENSABLE
                           compteur[tab[b].numero].numero++;
                        }
                    }
                        
                  

printf(ROUGE_GRAS "  Statistiques de la pioche :\n--------------------------------\n" RESET);
printf("\n");

for (int w = 0; w <= 6; w++){
    printf(OR "┌─────┐" RESET "  ");
}
printf("\n");
for (int w = 0; w <= 6; w++) {
    printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", w);
}
printf("\n");
for (int w = 0; w <= 6; w++) {
    int total_w;
if (i < 2) {
    total_w = 1;
    }else {
        total_w = i;  
}
    printf(OR "│"  "%d/%-2d " OR "│"  "  ", compteur[w].numero, total_w);
}
printf("\n");

for (int w = 0; w <= 6; w++){
    printf(OR "└─────┘" RESET "  ");
}
printf("\n\n");
for (int w = 7; w <= 12; w++){
    printf(OR "┌─────┐" RESET "  ");
}
printf("\n");



for (int w = 7; w <= 12; w++) {
    printf(OR "│" BLANC " %2d  " OR "│" RESET "  ", w);
}
printf("\n");

for (int w = 7; w <= 12; w++) {
    printf(OR "│"  "%d/%-2d " OR "│"  "  ", compteur[w].numero, w);
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
printf(ROUGE_GRAS "  -------- ANALYSE DU RISQUE ---------\n" RESET);

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
    printf("  - Carte %d : %d encore dans la pioche\n", num_carte, restantes);
}

float risque = 0;
if (*taille > 0) {
    risque = (dangerTotal * 100.0) / (*taille);
}


printf("  Total cartes dangereuses : %d sur %d cartes restantes\n", dangerTotal, *taille);
printf("  Probabilite de doublon : %.1f%%\n", risque);

printf("  Conseil : ");
if(risque < 20.0f){
    printf(VERT_GRAS "Risque faible — Piochez en toute tranquillite !\n" RESET);
    }else if(risque < 37.0f){
        printf(JAUNE_GRAS "Risque moyen — Reflechissez bien avant de piocher.\n" RESET);
        }else{
            printf(ROUGE_GRAS "Risque eleve — Il serait preferable de vous arreter !\n" RESET);
            }
printf("----------------------------------\n\n");
                
                
                
                
                
                
                
                
                
                //if (){
                //printf ("Conseil : Attention , %d cartes %d sont déjà sorties.\nVous en avez %d, il en reste %d dans la pioches",compteur[ ].numero,/*(la variable*/, compteur_cartes_joueurs[joueurs[j].cartes[/*variable*/]].numero,compteur[/*variable*/].numero);
                //}
                if (nb_tour <= 1){
                    printf ("%s que voulez vous faire ?\n[1] : Piocher\n",
                            joueurs[j].pseudo);
                } else {
                    printf ("%s que voulez vous faire ?\n[1] : Piocher || [2] : S'arrêter\n",
                            joueurs[j].pseudo);
                }

                scanf ("%d", &sortir);

            } while (sortir != 1 && sortir != 2);

            if (sortir == 2){
                penalise[j] = 1;
            }
            else {
                joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
                if (joueurs[j].cartes[joueurs[j].nb_cartes].bonus[0] == '\0'){
                    printf ("Carte piochée : [%d]\n", joueurs[j].cartes[joueurs[j].nb_cartes].numero);
                }
                else {
                    printf ("Carte piochée : [%s]\n", joueurs[j].cartes[joueurs[j].nb_cartes].bonus);
                }
                (*taille)--;
                int debut = joueurs[j].nb_cartes - joueurs[j].nbCartesManche;
                if (carteExisteManche(joueurs[j].cartes, debut, joueurs[j].nbCartesManche, joueurs[j].cartes[joueurs[j].nb_cartes])){
                    joueurs[j].scores = 0;
                    joueurs[j].score_pot = 0;
                    penalise[j] = 1;
                    printf ("\nDommage vous avez un doublon (%d) !\nVotre score pour cette manche est 0 !\n\n", joueurs[j].cartes[joueurs[j].nb_cartes].numero);
                    joueurs[j].nb_cartes++;
                }
                else if (penalise[j] == 0){

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

                    joueurs[j].nb_cartes++;
                    joueurs[j].nbCartesManche++;
                    joueurs[j].score_pot = joueurs[j].scores;

                    if(joueurs[j].nbCartesManche >= 7){
                        printf ("FELICITATION %s ! Vous venez de réaliser une Flip7 !\nVotre score pour cette manche est %d + 15\n", joueurs[j].pseudo, joueurs[j].scores);
                        joueurs[j].score_pot += 15;
                        i=7;
                        n++;
                        break;
                        
                    }
                }
                
                if (sortir == 1) { 
                    pause(); 
                }

                n++;
            }
        }
    }

    for (int p=0; p<nb_joueur; p++){
        printf ("Score de %s à la fin de la manche : %d !\n",
                joueurs[p].pseudo, joueurs[p].score_pot);
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
        fprintf(f, "Joueur : %s | Score Final : %d\n", joueurs[i].pseudo, joueurs[i].score_total);
        fprintf(f, " Cartes obtenues : ");
        for (int j = 0; j < joueurs[i].nb_cartes; j++) {
            if (joueurs[i].cartes[j].bonus[0] == '\0') {
                fprintf(f, "[%d] ", joueurs[i].cartes[j].numero);
            } else {
                fprintf(f, "[%s] ", joueurs[i].cartes[j].bonus);
            }
        }
        fprintf(f, "\n--------------------------\n");
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
    affichage(tab, TAILLE);
    
    printf ("  Combien de joueurs ? \n");
    scanf ("%d", &nb_joueur);
    for (int i=0; i<nb_joueur; i++){
        printf ("  Joueur %d quel est votre pseudo ?\n", i+1);
        scanf (" %s",joueur[i].pseudo);
        //strcpy(joueur[i].pseudo, prénom);
        printf ("  Prénom du joueur %d est %s !\n", i+1, joueur[i].pseudo);
    }
    for (int a=0; a<nb_joueur; a++){
    joueur[a].nb_cartes=0;
    joueur[a].score_total=0;
    }

    do{
        printf ("\n----------------------------Manche n°%d--------------------------\n\n", nb_manche);
        manche(tab, nb_joueur, joueur, &TAILLE/*revoir*/,&dernierePioche);
        nb_manche++;
        printf ("Nombre de cartes restantes dans la pioche : %d\n", TAILLE);
     for (int j=0; j<nb_joueur; j++){
        joueur[j].score_total += joueur[j].score_pot;
        printf ("Le score total de %s est %d !\n", joueur[j].pseudo, joueur[j].score_total);
        if (joueur[j].score_total>=200){
        fin=0;
        }
    }
    }
    while ( fin !=0  && TAILLE > 0);
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
