#include "carte.h"  
#include "joueur.h"    
#include <string.h>    
#include <stdlib.h>


void manche(cartes tab[], int nb_joueur, joueur joueurs[], int *taille/*revoir*/, int *dernierePioche){
   
    int i, j, t;
    int n = *dernierePioche;
    char sortir;
    int penalise[50];
    for (int l=0; l<nb_joueur; l++){
        joueurs[l].scores = 0;
        penalise[l] = 0;
        joueurs[l].nbCartesManche=0;
    }
    for(int i=0; i<7; i++){
        printf ("Tour n°%d : \n", i+1);
        for(int j=0; j<nb_joueur; j++){
            if ((*taille)==1){
                joueurs[j].scores += 15;
                if(joueurs[j].cartes[joueurs[j].nb_cartes].bonus[0] == '\0'){
                joueurs[j].scores = effetNumero(joueurs[j].cartes[joueurs[j].nb_cartes].numero, joueurs[j].scores);
            }
            else {
                joueurs[j].scores = effetBonus(joueurs[j].cartes[joueurs[j].nb_cartes].bonus, joueurs[j].scores);
            }
               
            }
            else if ((*taille)==0) return;
            if (penalise[j]==1){
                continue;
            }
            do {
            printf ("%s voulez-vous sortir de la manche ? o(oui), n(non) !\n",joueurs[j].pseudo);
            scanf (" %c", &sortir);
            }
            while (sortir != 'n' && sortir != 'o');
            if (sortir == 'o'){
                penalise[j] = 1;
            }
            else {
            joueurs[j].cartes[joueurs[j].nb_cartes] = tab[n];
            (*taille)--;
            if (carteExiste(joueurs[j].cartes, i,tab[n])==1){
                joueurs[j].scores = 0;
                penalise[j] = 1;
                printf ("\nCarte deja possédé !\n\n");
                joueurs[j].nb_cartes++;
                joueurs[j].nbCartesManche++;
            }
            else if (penalise[j] == 0){
           
            if(joueurs[j].cartes[joueurs[j].nb_cartes].bonus[0] == '\0'){
                joueurs[j].scores = effetNumero(joueurs[j].cartes[joueurs[j].nb_cartes].numero, joueurs[j].scores);
            }
            else {
                joueurs[j].scores = effetBonus(joueurs[j].cartes[joueurs[j].nb_cartes].bonus, joueurs[j].scores);
            }
           // printf ("Score de la manche de %s : %d !\n", joueurs[j].pseudo, joueurs[j].scores);
            joueurs[j].nb_cartes++;
            if(joueurs[j].nbCartesManche>=7){
                joueurs[j].scores+= 15;    // a revoir fin de manche pour premier a 7 cartes
            return;
            }
        }
            n++;
           
           
        }
        }
        }
for (int p=0; p<nb_joueur; p++){
    printf ("Score de %s à la fin de la manche : %d !\n", joueurs[p].pseudo, joueurs[p].scores);
}
*dernierePioche=n;
}