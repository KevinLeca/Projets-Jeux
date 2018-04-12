/**
* \fn Star.c
* \author Andy Dinga Théo Loison Kevin Leca
* \brief 
* \date Vendredi 16 Decembre 2016
*/

#include "Outil.h"
#include "Placer.h"
#define N 20
/**
*\fn void clrscr()
*\brief //nettoie l'écran//
*/

void clrscr()
{
    system("clear");
}
/**
*\fn void init_grille(char grille[N][N], int max_i,int max_j)
*\brief //Initialise la grille avec des espaces//
*/

void init_grille(char grille[N][N], int max_i,int max_j){
	int i, j;
	for(i=0; i<max_i; i++){
		for(j=0; j<max_j ; j++){
			char lettre = '.';
			grille[i][j] = lettre;
		}
	}
}
/**
*\fn void init_liste(char liste[50][10])
*\brief initialise la grille
*/
void init_liste(char liste[50][10]){
	int i,j;
	for(i=0; i<50; i++){
		for(j=0; j<10 ; j++){
			char lettre = '\0';
			liste[i][j] = lettre;
		}
	}
}
/**
*\fn void completer_grille(char grille[N][N])
*\brief //Complet les trous de la grilles par des lettres alÃ©atoires//
*/

void completer_grille(char grille[N][N]){
	int i, j;
	for(i=0; i<N; i++){
		for(j=0; j<N ; j++){
			if(grille[i][j] == '.'){
				int lettre = '@'+uHasard(26);
				grille[i][j] = lettre;
			}
		}
	}
}
/**
*\fn void afficher(char grille[N][N])
*\brief //Affiche la grille de Mots-MÃ©lÃ©s//
*/

void afficher(char grille[N][N]){
	int i, j;
	printf("\n");
	for(i=-1; i<N; i++){
            if (i==-1){
                printf("  ");
            }
            else if(i<10 && i!=-1){
                printf("%i  ",i);
            }
            else if (i>=10){
                printf("%i ",i);
            }
		for(j=0; j<N; j++){
		    if(i==-1){
                    if(j<10){
                        printf("%i  ",j);
                    }
                    else{

                        printf("%i ",j);
                    }
		    }
		    else{
                printf("%c  ", grille[i][j]);
		    }

		}
        printf("\n");
	}
	printf("\n");
}
/**
*\fn void placer(char mot[N], char grille[N][N], int x, int y, int direct)
*\brief //Place les mots dans la grille celon les indications de la fonction <verifier>//
*/

void placer(char mot[N], char grille[N][N], int x, int y, int direct){

	switch(direct)
		{	case 1: horizontale(grille,mot, x,y); break;
			case 2: verticale(grille, mot, x, y); break;
			case 3: diagonale(grille, mot, x, y); break;
			default: ;//Ne rien faire//
		}
}
/**
*\fn int verifier(char grille[N][N],char mot[N],int *x_start,int *y_start,int *x_end,int *y_end)
*\brief //Verifie si le mot peut etre placer dans la gril#include <conio.h>le//
*/

int verifier(char grille[N][N],char mot[N],int *x_start,int *y_start,int *x_end,int *y_end){
	int leng = nChaineLg(mot);
	int i, j, k, l	;
	int direct, possible;

	direct=rand()%3 + 1;

	if(direct == 1){	//Cas por horizontale vers la droite//
		for(i=0; i<N+1 ; i++){
			for(j=0; j<N+1; j++){
				possible = 1;
				if(leng + j <= N){
					for(k=0; k<=leng && possible==1; k++){
						if(grille[i][j+k] != '.' && grille[i][j+k] != mot[k]){
							possible = 0;
						}
					}
					if(possible == 1){
                            *x_start=j;
							*y_start=i;
							*x_end=j+(leng-1);
							*y_end=i;
							placer(mot, grille, i, j, direct);
							return 1;
					}
				}
			}
		}
	}

	else if(direct == 2){	//Cas pour verticale vers le bas//
		for(i=0; i<N+1 ; i++){
			for(j=0; j<N+1; j++){
				possible = 1;
				if(leng + j <= N){
					for(k=0; k<=leng && possible==1; k++){
						if(grille[i+k][j] != '.' && grille[i+k][j] != mot[k]){
							possible = 0;
						}
					}
					if(possible == 1){
                        			*x_start=j;
                        			*y_start=i;
                        			*x_end=j;
                        			*y_end=i+(leng-1);
						placer(mot, grille, i, j, direct);
						return 1;
					}
				}
			}
		}
	}

	else if(direct == 3){	//Cas pour diagonale vers le bas a droite//
		for(i=0; i<N+1 ; i++){
			for(j=0; j<N+1; j++){
				possible = 1;
				if(leng + j <= N){
					for(k=0; k<=leng && possible ==1; k++){
						if(grille[i+k][j+k] != '.' && grille[i+k][j+k] != mot[k]){
							possible = 0;
						}
					}
					if(possible == 1){
						*x_start=j;
                        			*y_start=i;
                        			*x_end=j+(leng-1);
                        			*y_end=i+(leng-1);
						placer(mot, grille, i, j, direct);
						return 1;
					}
				}
			}
		}
	}
}
/**
*\fn int selection(char grille[N][N],int coord[500],int *i)
*\brief selectionne le mot de l'utilisateur
*/
int selection(char grille[N][N],int coord[500],int *i){
	int x_start,y_start,x_end,y_end;
	*i=0;

    printf("Coordonnés de début de mot :\n");
    scanf("%i %i",&x_start,&y_start);
    printf("Coordonnées de fin de mot :\n");
    scanf("%i %i",&x_end,&y_end);
	while (*i<500){

		if(coord[*i+4] == -1){
			if(coord[*i]==x_start && coord[*i+1]==y_start && coord[*i+2]==x_end && coord[*i+3]==y_end){

					return 1;
			}else{
				*i=*i+5;
			}

		}
		 else{
            	*i++;
        	}
	}
}
/**
*\fn void supprimer_mot(char liste[50][10],int rang)
*\brief supprime de la liste les mots que le joueur a trouvé
*/
void supprimer_mot(char liste[50][10],int rang){
	int i=0;
	int j=0;
		for(j=0;j<10;j++){
			liste[rang][j]='\0';
		}
}
/**
*\fn void jouer(int theme)
*\brief //Permet de jouer au jeu//
*/

void jouer(int theme){
	char grille[N][N];		//Grille de mots-meles//
	char a[4];				//Mot pour la fin de partie//
	char adresse[50];		//Adresse du fichier contenant la liste de mot//
	char mot[N];			//Mot courant de la liste//
	char liste[50][10];
	int leng = nChaineLg(mot);
	int i = 0;				//Indice//
	int tmp;
	int x_start,y_start,x_end,y_end;
	int coord[500];
	int cpt=0;
	int select;
	int cptr_j,cptr_i=0;
	int indice ,num_mot;
	int verif=0;
	int trouve=0;
	init_grille(grille,N,N);	//Initialise la grille avec des points//
	init_liste(liste);


	while(strcmp(a, "fini") != 0){

		switch(theme){	//Permet de selectionner le fichier a ouvrir celon le choix du joueur//
			case 1: strcpy(adresse, "./TEXTE/ELECTIONS.txt"); break;
			case 2: strcpy(adresse, "./TEXTE/EAU.txt"); break;
			case 3: strcpy(adresse, "./TEXTE/CAPITALES.txt"); break;
			case 4: strcpy(adresse, "./TEXTE/POTTER.txt"); break;
		}

		FILE * fichier;


		fichier=fopen(adresse,"r");
			do{ //Parcours le fichier//
				for(i=0; i<10;i++){	//Permet de mettre dix mot par ligne pour la lisibilite//
					if(feof(fichier) == 0){
						fscanf(fichier, "%s", mot);			//Selectionne un mot dans la liste (fichier.txt)//
						tmp = verifier(grille, mot,&x_start,&y_start,&x_end,&y_end);		//Place le mot dans la grille//
						if(tmp == 1){
                           				coord[cpt]=x_start;
							cpt++;
							coord[cpt]=y_start;
							cpt++;
							coord[cpt]=x_end;
							cpt++;
							coord[cpt]=y_end;
							cpt++;
							coord[cpt]=-1;
							cpt++;

							    for(cptr_j=0;cptr_j<10;cptr_j++){

									liste[cptr_i][cptr_j]=mot[cptr_j];
									if (liste[cptr_i][cptr_j]== '\0'){
										break;
									}
							    }
							    cptr_i++;



						}
						else{
							i--;
						}
					}
				}
				printf("\n");
			}while(!feof(fichier));

		fclose (fichier);

		completer_grille(grille);	//Comble les trous de la grille par des lettres au hasard//

		while(trouve!= 1){
		    clrscr();
		    printf("\nVoici les mots a trouver: \n");
            printf("-------------------------\n");
		     for(i=0;i<50;i++){
		            //printf("\n");
		            for(cptr_j=0;cptr_j<10 ;cptr_j++){
		            	mot[cptr_j]=liste[i][cptr_j];
                        //printf("%c",liste[i][cptr_j]);
                        
		            }
		            if (i==10 || i==20 ||i==30||i==40||i==50){
		            	printf("\n");
		            }
		            printf("%s ",mot);
		    }
		    printf("\n");
		    afficher(grille);
		    select=selection(grille,coord,&indice);
		    num_mot=indice/5;
		    if (select == 1){
		        supprimer_mot(liste,num_mot);

		    }
		    verif=0;
		    for(i=0;i<50;i++){
		            for(cptr_j=0;cptr_j<10;cptr_j++){
		                if(liste[i][cptr_j]=='\0'){
		                    verif++;
		                }
		                if(verif==500){
		                    printf("vous avez gagné!! \n");
		                    trouve=1;
		                }
		            }
		    }
		}





		printf("Entrez <fini> une fois la partie terminee => ");
		scanf("%s", a);
	}
}
/**
*\fn void select_theme()
*\brief //Permet a  l'utilisateur de selectionner le theme de la grille//
*/

void select_theme(){
	int choix = 0;
	printf("\n		+-------------------------------------------------------+");
    printf("\n		|	Selectionnez un thème parmi ceux proposes:      |\n");

	while(choix<=0 || choix>4){
		printf("		|                                               	|\n");
		printf("		|		1 - Elections                           |\n");
		printf("		|		2 - L eau dans tout ses etats           |\n");
		printf("		|		3 - Capitales du monde                  |\n");
		printf("		|		4 - Harry Potter                        |\n");
        printf("		+-------------------------------------------------------+\n");
		printf("Votre choix : ");
		scanf("%i", &choix);

		switch(choix){
			case 1: choix = 1; break;
			case 2: choix = 2; break;
			case 3: choix =  3; break;
			case 4: choix =  4; break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
		}
	}
	jouer(choix);
}
/**
*\fn int main()
*\brief //Main du programme//
*/

int main(){
	srand(time(NULL));
	int choix;

// Affichage du menu et saisie du choix //
	do
	{	printf("\n\n\n\n\n\n\n\n\n");
		printf("	   #   #   ###   #####   ####       #   #  #####  #      #####   ####\n");
		printf("	   ## ##  #   #    #    #           ## ##  #      #      #      #\n");
		printf("	   # # #  #   #    #    #           # # #  #      #      #      #\n");
		printf("	   #   #  #   #    #     ###   ###  #   #  ####   #      ####    ###\n");
		printf("	   #   #  #   #    #        #       #   #  #      #      #          #\n");
		printf("	   #   #  #   #    #        #       #   #  #      #      #          #\n");
		printf("	   #   #   ###     #    ####        #   #  #####  #####  #####  ####\n");
		printf("\n			+---------------------------------------+\n");
		printf("			|					|");
		printf("\n			|		Menu :			|\n");
		printf("			|					|\n");
		printf("			|	1 - Selection du theme		|\n");
		printf("			|	2 - Regles du jeux     		|\n");
		printf("			|	3 - Quitter           		|\n");
		printf("			|					|");
        printf("\n			+---------------------------------------+\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

// Traitement du choix de l'utilisateur //
		switch(choix)
		{	case 1: select_theme();	break;
			case 2: printf("\n			Regles du jeu de mots meles: \n");
					printf("\n			Les mots à trouver s'affichent sous la grille.");
					printf("\n			Une même lettre peut être utilisée dans plusieurs mots à la fois.");
					printf("\n			Les mots sont écrits de gauche a droite et peuvent être disposés:");
					printf("\n			horizontalement, verticalement, et en diagonale .");
                    printf("\n			Une même lettre peut être utilisée dans plusieurs mots à la fois. \n"); break;
			case 3: break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 3\n");
		}
	}
	while(choix!=3);
	printf("Au revoir, et merci d'avoir joue !\n");
	printf("\n");
	return EXIT_SUCCESS;
}
