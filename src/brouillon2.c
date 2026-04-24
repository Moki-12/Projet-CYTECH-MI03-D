//115 A 120
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

//177 A 192
void StatsPioche (joueur joueur[], carte tab[], int j, int n){
    cartes compteur[13] = {0};
    for (int i=0; i<n ;i++){
        compteur[tab[i].numero].numero++;
    }
    printf ("Statistiques de la pioche :\n");
    printf ("[0] : %d/1  ", compteur[0].numero);
    for (int j=1; j<13; j++){
        printf ("[%d] : %d/%d  ", j, compteur[j].numero, j);
    }
    printf ("\n");
}

// 198 A 205
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

// 214 A 219
void AfficherCarte (joueur joueur[], int j){
    if (joueur[j].cartes[joueur[j].nb_cartes].bonus[0] == '\0'){
        printf ("Carte piochée : [%d]\n", joueur[j].cartes[joueur[j].nb_cartes].numero);
    }
    else {
        printf ("Carte piochée : [%d]\n", joueur[j].cartes[joueur[j].nb_cartes].numero);
    }
}
// 221 A 228
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

//231 A 241
void BonnePioche (joueur joueur[], int j){
    if (joueur[j].cartes[joueur[j].nb_cartes].bonus[0] == '\0'){
        joueur[j].scores = effetNumero (joueur[j].cartes[joueur[j].nb_cartes].numero, joueur[j].scores);
    }
    else {
        joueur[j].scores = effetBonus (joueur[j].cartes[joueur[j].nb_cartes].bonus, joueur[j].scores);
    }
}
 //247 A 254
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
