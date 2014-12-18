#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "arbre.h"
#include "outils.h"
#include "outils.c"
#include "liste.c"
#include "arbre.c"

int main()
{
	int choix = 0;
	char nomfichier[100];
	char* nom;
	char* nom2;
	NoeudABR* noeud;
	ArbreBR *arbre = NULL;
	
	printf("\e[1;1H\e[2J"); // Clear Terminal
	
	do {
		switch(choix) {
			/* choix a 9 valeurs possibles :
			0 : le menu avec les différents choix doit s'afficher
			1 : l'ABR doit être créé
			2 : charger un fichier dans l'ABR
			3 : afficher les caractéristiques de l'ABR
			4 : afficher tous les mots distincts par ordre alphabétique
			5 : recherche un mot
			6 : affiche les phrases contenant deux mots
			7 : équilibre l'arbre
			-1 : quitte le programme
			*/
			case 0:
				// Menu choix de l'action
				printf("********** Indexation **********\n\n");
				printf("Que voulez-vous faire ?\n");
				printf("1. Créer un ABR\n2. Charger un fichier dans l'ABR\n");
				printf("3. Afficher les caractéristiques de l'ABR\n4. Affiche tous les mots distincts par ordre alphabétique\n");
				printf("5. Recherche un mot\n6. Affiche les phrases contenant les deux mots saisis\n");
				printf("7. Équilibre l'arbre\n8. Quitter\n\n");
				if (arbre != NULL) {
					printf("ABR créé : OUI\n\n> ");
				} else {
					printf("ABR créé : NON\n\n> ");
				}
				scanf("%d",&choix);
				printf("\e[1;1H\e[2J"); // Clear Terminal
				break;
				
			case 1:
				// Création de l'arbre
				if (arbre == NULL) arbre = creer_abr();
				else {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre existe déjà.\n\n");
				}
				choix=0;
				break;
				
			case 2:
				// Chargement d'un fichier dans l'ABR
				if (arbre == NULL) {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n\n");
					choix = 0;
					break;
				}
				
				printf("Quel fichier voulez-vous charger ?\n\n> ");
				scanf("%s",nomfichier);
				
				if (charger_fichier(arbre,nomfichier) != 0) {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("Fichier chargé avec succès.\n\n");
				} else {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("Échec lors du chargement du fichier !\n\n");
				}
				
				choix = 0;
				break;
				
			case 3:
				// Affichage des caractéristiques de l'arbre
				if (arbre == NULL) {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n\n");
					choix = 0;
					break;
				}
				
				printf("\e[1;1H\e[2J"); // Clear Terminal
				printf("Caractéristiques de l'arbre :\n\n");
				printf("- Nombre de noeuds dans l'arbre : %d\n",nb_descendents(*(arbre->racine)));
				printf("- Profondeur de l'arbre (0 si juste une racine) : %d\n",hauteur(*(arbre->racine)));
				if (equilibre(*arbre))
					printf("- L'arbre est équilibré.\n\n");
				else
					printf("- L'arbre n'est pas équilibré.\n\n");
				choix=0;
				break;
				
			case 4:
				// Affichage des mots par ordre alphabétique
				if (arbre == NULL) {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n");
					choix = 0;
					break;
				}
				
				afficher_arbre(*arbre);
				choix=0;
				break;
			case 5:
				// Recherche d'un mot
				if (arbre == NULL) {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n");
					choix = 0;
					break;
				}
				
				printf("Quel mot voulez-vous rechercher ?\n\n> ");
				nom = malloc(100*sizeof(char));
				scanf("%s",nom);
				noeud = rechercher_noeud(arbre,nom);
				
				if (noeud != NULL)
					afficher_noeud(*noeud);
				else {
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("Le nœud n'a pas été trouvé !\n\n");
				}
				
				choix=0;
				break;
			case 6:
				// Affichage des phrases contenant les 2 mots saisis.
				if (arbre == NULL){
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n");
					choix = 0;
					break;
				}

				printf("Quels mots voulez-vous rechercher ?\n\n> ");
				nom=malloc(100*sizeof(char));
				nom2=malloc(100*sizeof(char));
				scanf("%s%s",nom,nom2);
				
				printf("\e[1;1H\e[2J"); // Clear Terminal
				rechPhrase(*arbre,nom,nom2,nomfichier);

				choix=0;
				break;
			case 7:
				// EQUILIBRAGE DE L'ARBRE
				if (arbre == NULL){
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n\n");
					choix = 0;
					break;
				}

				if (arbre->racine == NULL){
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("Il n'y a pas de racine dans l'arbre !\n\n");
					choix = 0;
					break;
				}

				equilibrage(arbre, arbre->racine);

				printf("\e[1;1H\e[2J"); // Clear Terminal
				printf("L'arbre a bien été équilibré !\n\n");

				choix=0;

				break;
			case 8:
				// quitter
				// a supprimer : - l'arbre
				// dans l'arbre, chacun des nœuds
				// dans chaque noeud, la liste des positions
				// dans la liste des positions, chaque position
				if (arbre == NULL){
					printf("\e[1;1H\e[2J"); // Clear Terminal
					printf("L'arbre n'a pas été créé !\n\n");
					choix = 0;
					break;
				}

				supprimer_arbre(arbre);
				
				printf("\e[1;1H\e[2J"); // Clear Terminal
				printf("L'arbre a bien été supprimé.\n\n");

				choix=-1;

				break;
		}
	}while(choix>=0);
	return 0;
}
