int stats_danger[13] = {0};    //à partir de la ligne 194 c'est entre la fin des statistiques de la pioche et le début de que voulez vous faire 
for(int s = 0; s < n; s++){
    if(tab[s].bonus[0] == '\0' && tab[s].numero >= 0 && tab[s].numero <= 12){
        stats_danger[tab[s].numero]++;
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
