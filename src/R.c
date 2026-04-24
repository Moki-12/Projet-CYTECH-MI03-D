int stat[13];
for(int i = 0; i < 13; i++){
    stat[i] = 0;
}
for(int i = 0; i < nbcartespiochees; i++){
    if(pioche[i].type == NUMERO){
        int n = pioche[i].valeur;
        stat[n]++;
    }
}
for(int i = 0; i < 13; i++){
    printf
    ("carte %d:%d sorties\n",i,stat[i]);
}
