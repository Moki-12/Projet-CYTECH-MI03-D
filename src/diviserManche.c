void InitManche (joueur joueur[], int nb_joueur, int penalite[]){
    for (int i=0; i<nb_joueur; i++){
        joueur[i].scores = 0;
        penalite[i] = 0;
        joueur[i].nbCarteManche = 0;
        joueur[i].score_pot = 0;
    }
}

// 155 A 170
void CartesMain (joueur joueur[], int j){
    printf ("Vos cartes en main :\n");
    int debutManche = joueur[j].nb_cartes - joueur[j].nbCarteManche;
    for (int m=0; m<joueur[j].nbCarteManche; m++){
        int index = debutManche + m;
        if (joueur[j].cartes[index].bonus[0] == '\0'){
            printf ("[%d] ", joueur[j].cartes[index].numero);
        }
        else {
            printf ("[%s] ", joueur[j].cartes[index].bonus);
        }
    }
    printf ("\n");
}

//177 A 230
void StatsPioche (joueur joueur[], carte tab[], int j, int n){
    cartes compteur[13] = {0};
    for (int i = 0; i <n; i++) {
                        compteur[tab[i].numero].numero++;
                    }
                        printf ("Statistiques de la pioche :\n--------------------------------\n");
                    printf ("\n");
                    int total;
                    int j = 0;
                    if (j < 2){
                        total = 1;
                    }
                    else {
                        total = j;
                    }
                    for (int k = 0; k <= 5; k++){
                        printf("+----+      ");
                    }
                    
                    printf ("\n");
                    //printf ("| 00  | : %d/1 ", compteur[0].numero);

                    for (int j=0; j<=5; j++){
                        if (j == 0){
                            total = 1;
                        }
                        else {
                            total = j;
                        }
                        printf ("| %d  |:%d/%-2d ", j, compteur[j].numero, total);
                    }
                    printf ("\n");
                    for (int l = 0; l <= 5;l++){
                        printf("+----+      ");
                    }
                    printf ("\n");
                    printf ("\n");
                    for (int m = 6; m <= 12; m++){
                        printf("+----+      ");
                    }
                    
                    printf ("\n");
                    
                    for (int n=6; n<=12; n++){
                        printf ("| %2d |:%d/%-2d ", n, compteur[n].numero, n);
                    }
                    printf ("\n");
                    for (int o=6; o<=12; o++){
                        printf("+----+      ");
                    }
                    printf ("\n");
                }

//233 A 268
void Conseil (cartes tab[], joueur joueur[], int j, int *taille){
                    int stats_danger[13] = {0};    //à partir de la ligne 194 c'est entre la fin des statistiques de la pioche et le début de que voulez vous faire 
                for(int i = 0; i < n; i++){
                    if(tab[i].bonus[0] == '\0' && tab[i].numero >= 0 && tab[i].numero <= 12){
                        stats_danger[tab[i].numero]++;
                        
                    }
                    
                }
                int dangerTotal = 0;
                printf("\n-------- ANALYSE DU RISQUE ---------\n");
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
    printf("- Carte %d : %d encore dans la pioche\n", num_carte, restantes);
}

float risque = 0;
if (*taille > 0) {
    risque = (dangerTotal * 100.0) / (*taille);
}
printf("Total cartes dangereuses : %d | Cartes restantes : %d\n", dangerTotal, *taille);
printf("Probabilite de doublon : %.1f%%\n", risque);


if(risque < 20.0){
printf("🟢 Risque faible - Conseil 🤓 : Vous pouvez piocher en toute tranquilité !\n");
}
else if (risque < 37.0){
    printf("🟡 Risque moyen - Conseil 🤓 : Attention, reflechissez bien.\n");
}
else {
printf("🔴 Risque eleve - Conseil 🤓 : C'est dangereux, il serait préférable d'arrêter !\n");
}
printf("----------------------------------\n\n");
}


// 288 A 296
int Piocher (joueur joueur[], int j, int nb_tour, int sortir){
    if (nb_tour <= 1){
        printf ("%s que voulez vous faire ?\n[1] : Piocher\n", joueur[j].pseudo);
    }
    else {
        printf ("%s que voulez vous faire ?\n[1] : Piocher || [2] : S'arrêter\n", joueur[j].pseudo);
    }
    scanf ("%d", &sortir);
    return sortir;
}

// 305 A 310
void AfficherCarte (joueur joueur[], int j){
    if (joueur[j].cartes[joueur[j].nb_cartes].bonus[0] == '\0'){
        printf ("Carte piochée : [%d]\n", joueur[j].cartes[joueur[j].nb_cartes].numero);
    }
    else {
        printf ("Carte piochée : [%d]\n", joueur[j].cartes[joueur[j].nb_cartes].numero);
    }
}
// 312 A 319
void Doublon (joueur joueur[], int j, int penalite[]){
    int debut = joueur[j].nb_cartes - joueur[j].nbCarteManche;
    if (carteExiste (joueur[j].cartes, debut, joueur[j].nb_cartes, joueur[j].cartes[joueur[j].nb_cartes])){
        joueur[j].score = 0;
        joueur[j].score_pot = 0;
        penalite[j] = 1;
        printf ("\nDommage vous avez pioché un doublon (%d) !\nVotre score pour cette manche est 0 !\n\n", joueur[j].cartes[joueur[j].nb_cartes].numero);
        joueur[j].nb_cartes++;
    }
}

//322 A 332
void BonnePioche (joueur joueur[], int j){
    if (joueur[j].cartes[joueur[j].nb_cartes].bonus[0] == '\0'){
        joueur[j].scores = effetNumero (joueur[j].cartes[joueur[j].nb_cartes].numero, joueur[j].scores);
    }
    else {
        joueur[j].scores = effetBonus (joueur[j].cartes[joueur[j].nb_cartes].bonus, joueur[j].scores);
    }
}
 //338 A 343
void Flip7 (joueur joueur[], int j, int *i, int *n){
    int I = *i;
    int N = *n;
    if (joueur[j].nbCarteManche >= 7){
        printf ("FELICITATION %s ! Vous venez de réaliser un Flip7 !\nVotre score pour cette manche est %d + 15\n", joueur[j].pseudo, joueur[j].scores);
        joueur[j].score_pot += 15;
        I=7;
        N++;
        break;
    }
}


void manche(cartes tab[], int nb_joueur, joueur joueurs[], int *taille, int *dernierePioche){
        int i, j, t;
    int nb_tour = 0;
    int n = *dernierePioche;
    int sortir;
    int penalise[50];
    int cartesPiochées = 0;
    InitManche(joueurs, nb_joueur, penalise);
    for (int i=0; i<n; i++){
        printf ("Tour n°%d\n", i+1);
        nb_tour++;
        for (int j=0; j<nb_joueur; j++){
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
                printf ("------------Au tour de %s------------\n", joueurs[j].pseudo);
                
                if (joueurs[j].nbCartesManche >= 1) {
                    CartesMain(joueurs, j);
                    printf ("Votre score potentiel : %d\n----------------------------\n",
                            joueurs[j].score_pot);
                            StatsPioche(tab);
                }
                Conseil(tab, joueurs, j, *taille);
                sortir = Piocher(joueurs, j, nb_tour, sortir);
                }
                while (sortir != 1 && sortir != 2);
                if (sortir == 2){
                    penalise[j] = 1;
                }
                else {
                    joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
                    AfficherCarte(joueurs, j);
                    (*taille)--;
                    Doublon(joueurs, j, penalise);
                    if (penalise[j] == 0){
                    BonnePioche(joueurs, j);
                    joueurs[j].nb_cartes++;
                    joueurs[j].nbCartesManche++;
                    joueurs[j].score_pot = joueurs[j].scores;
                    Flip7(joueurs, j, &i, &n);
                    }
                    n++;
                }
                printf ("\nAppuyer sur Entrée pour passer au joueur suivant\n");
            getchar();
            getchar();
    }
}
    for (int p=0; p<nb_joueur; p++){
        printf ("Score de %s à la fin de la manche : %d !\n",
                joueurs[p].pseudo, joueurs[p].score_pot);
    }

    *dernierePioche = n;
}
