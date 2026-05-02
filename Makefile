all : fliptech
 
carte.o : src/carte.c include/carte.h
	gcc -c src/carte.c -Iinclude -o carte.o
 
joueur.o : src/joueur.c include/joueur.h include/carte.h
	gcc -c src/joueur.c -Iinclude -o joueur.o
 
affichage.o : src/affichage.c include/affichage.h include/carte.h include/joueur.h
	gcc -c src/affichage.c -Iinclude -o affichage.o
 
jeu.o : src/jeu.c include/jeu.h include/carte.h include/joueur.h include/affichage.h
	gcc -c src/jeu.c -Iinclude -o jeu.o
 
main.o : src/main.c include/carte.h include/joueur.h include/affichage.h include/jeu.h
	gcc -c src/main.c -Iinclude -o main.o
 
fliptech : main.o carte.o joueur.o affichage.o jeu.o
	gcc main.o carte.o joueur.o affichage.o jeu.o -o fliptech
 
