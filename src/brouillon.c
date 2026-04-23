printf("Statistiques de la pioche :\n--------------------------------\n"); //à partir de la ligne
int total;
if (i < 2) {
    total = 1;
    }else {
        total = i;  
}

for (int i = 0; i <= 5; i++){
    printf("+----+      ");
}

printf("\n");

for (int i = 0; i <= 5; i++){
    printf("| %d  |:%d/%-2d ", i, compteur[i].numero, total);  // Le %-2 sert à forcer l'alignement
}

printf("\n");

for (int i = 0; i <= 5; i++){
    printf("+----+      ");
}
printf("\n");
printf("\n");
for (int i = 6; i <= 12; i++){
    printf("+----+      ");
}

printf("\n");

for (int i = 6; i <= 12; i++){
    printf("| %2d |:%d/%-2d ", i, compteur[i].numero, i);
}
printf("\n");

for (int i = 6; i <= 12; i++){
    printf("+----+      ");
}
printf("\n");
}
