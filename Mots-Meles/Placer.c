/**
* \fn Placer.c
* \author Andy Dinga Théo Loison Kevin Leca
* \brief 
* \date Vendredi 16 Decembre 2016
*/
#include "Outil.h"
#define N 20
/**
* \fn void horizontale(char grille[N][N], char mot[N], int x, int y)
* \brief //Permet d'insÃ©rer un mot a  l'horizontale vers la droite; necessite le nom de la grille, le mot a  inserer, et les coordonnees de la premiere lettre//
*/

void horizontale(char grille[N][N], char mot[N], int x, int y){
	int i;
	for(i=0; i<nChaineLg(mot); i++){
		grille[x][y] = mot[i];
		y++;
	}
}
/**
* \fn void verticale(char grille[N][N], char mot[N], int x, int y)
* \brief //Permet d'inserer un mot a  la verticale vers le bas; necessite le nom de la grille, le mot a  inserer, et les coordonnees de la premiere lettre//
*/

void verticale(char grille[N][N], char mot[N], int x, int y){
	int i;
	for(i=0;i<nChaineLg(mot); i++){
		grille[x][y] = mot[i];
		x++;
	}
}
/**
* \fn void diagonale(char grille[N][N], char mot[N], int x, int y)
* \brief //Permet d'inserer un mot en diagonale vers le bas a droite; necessite le nom de la grille, le mot a inserer, et les coordonnees de la premiere lettre//
*/

void diagonale(char grille[N][N], char mot[N], int x, int y){
	int i;
	for(i=0;i<nChaineLg(mot); i++){
		grille[x][y] = mot[i];
		x++;
		y++;
	}
}