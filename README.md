# 🃏 PROJET FLIPTECH


## Table des matières

- [Introduction](#introduction)
- [Règle du jeu](#règle-du-jeu)
- [Pré-requis](#pré-requis)
- [Guide d'installation](#guide-dinstallation)
- [Guide d'utilisation](#guide-dutilisation)
- [Structure du Projet](#structure-du-projet)
- [Auteurs](#auteurs)

## Introduction 

FlipTech est un jeu de cartes de prise de risque développé en langage C. Le but est d'accumuler le plus de points possible sans piocher de doublons. Le programme gère les statistiques de la pioche en temps réel pour aider les joueurs dans leurs décisions. Ce projet a pour objectif de mettre en pratique la manipulation des structures, des tableaux de tableaux, des fichiers et l'affichage graphique en console.

## Règles du Jeu 
- **Pioche** : À chaque tour, chaque joueur décide de piocher une carte ou de s'arrêter.
- **Doublon** : Si vous piochez un numéro que vous possédez déjà dans la manche actuelle, votre score retombe à 0 pour cette manche !
- **Bonus** : Des cartes spéciales (+2, +4, x2...) permettent de booster votre score en fin de manche.
- **Flip 7** : Collectionnez 7 numéros différents sans doublon pour obtenir un bonus de 15 points.
- **Victoire** : Le premier joueur à atteindre 200 points ou à obtenir le plus de point une fois la pioche épuisée, gagne la partie.

## Pré-requis

* **GCC** (Compilateur C)
* **Make**

## Guide d'installation 

```bash
# Clonez le dépôt
git clone [https://github.com/ton-pseudo/FlipTech.git](https://github.com/ton-pseudo/FlipTech.git) 

# Accédez au répertoire
cd FlipTech

# Compilez le projet
make

# Exécutez le jeu
./fliptech
```

## Auteurs
Raphaêl Yoyotte
Yasmine Mouchrif
Saghina Robert
