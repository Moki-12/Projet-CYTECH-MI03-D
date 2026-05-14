void corrigeTab(cartes *tab){
    int i = 0;
    tab[i].numero = 0; tab[i].bonus[0] = '\0'; i++;
    tab[i].numero = 1; tab[i].bonus[0] = '\0'; i++;
    for(int n = 2; n <= 12; n++)
        for(int j = 0; j < n; j++){
            tab[i].numero = n; tab[i].bonus[0] = '\0'; i++;
        }
    tab[i].numero = -1; strcpy(tab[i++].bonus, "x2");
    tab[i].numero = -2; strcpy(tab[i++].bonus, "+2");
    tab[i].numero = -3; strcpy(tab[i++].bonus, "+4");
    tab[i].numero = -4; strcpy(tab[i++].bonus, "+6");
    tab[i].numero = -5; strcpy(tab[i++].bonus, "+8");
    tab[i].numero = -6; strcpy(tab[i++].bonus, "+10");
}


int melanger(cartes *tab, int taille){
    if (tab == NULL || taille <= 0){
        return 0;
    }
    for(int i = taille - 1; i > 0; i--){
        int j = rand() % (i + 1);
        cartes temp = tab[i]; tab[i] = tab[j]; tab[j] = temp;
    }
    return 1;
}


int effetNumero(int numero, int score){
    if (numero < 0 || numero > 12 || score < 0){
        exit(1);
    }
    return score + numero; 
    
}


int effetBonus(char *bonus, int score){
    if (bonus == NULL || score < 0){
        exit(2);
    } 
    if(strcmp(bonus, "x2")  == 0) return score * 2;
    if(strcmp(bonus, "+2")  == 0) return score + 2;
    if(strcmp(bonus, "+4")  == 0) return score + 4;
    if(strcmp(bonus, "+6")  == 0) return score + 6;
    if(strcmp(bonus, "+8")  == 0) return score + 8;
    if(strcmp(bonus, "+10") == 0) return score + 10;
    return score;
}

