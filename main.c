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
	int choix=0;
	char choix2;
	char nomfichier[100];
	char* nom;
	char* nom2;
	NoeudABR* noeud;
	ArbreBR *arbre=NULL;
	do{
		switch(choix){
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
				// choix
				printf("********** Indexation **********\n\n");
				printf("Que voulez-vous faire ?\n");
				printf("1. Créer un ABR\n2. Charger un fichier dans l'ABR\n");
				printf("3. Afficher les caractéristiques de l'ABR\n4. Affiche tous les mots distincts par ordre alphabétique\n");
				printf("5. Recherche un mot\n6. Affiche les phrases contenant les deux mots saisis\n");
				printf("7. Équilibre l'arbre\n8. Quitter\n");
				if (arbre!=NULL) {
					printf("Un arbre est existant.\n\n> ");
				} else {
					printf("\n> ");
				}
				scanf("%d",&choix);
				printf("********************************\n\n\n");
				break;
			case 1:
				// création de l'arbre
				if (arbre==NULL) arbre = creer_abr();
				else {
					printf("L'arbre existe déjà. Voulez-vous le remplacer ? (tapez y pour valider, tapez autre chose pour annuler)\n>");
					scanf("%c",&choix2);
					if (choix2 == 'y') arbre = creer_abr();
				}
				choix=0;
				break;
			case 2:
				// chargement d'un fichier dans l'ABR
				if (arbre==NULL){
					printf("L'arbre n'a pas été créé !\n");
					choix =0;
					break;
				}
				printf("Quel fichier voulez-vous charger ?\n>");
				scanf("%s",nomfichier);
				if (charger_fichier(arbre,nomfichier) != 0) printf("Fichier chargé avec succès.\n");
				else printf("Échec lors du chargement du fichier !\n");
				choix=0;
				break;
			case 3:
				// affichage des caractéristiques de l'arbre

				if (arbre==NULL){
					printf("L'arbre n'a pas été créé !\n");
					choix =0;
					break;
				}
				printf("Caractéristiques de l'arbre :\n");
				printf("Nombre de noeuds dans l'arbre : %d\n",nb_descendents(*(arbre->racine)));
				printf("Profondeur de l'arbre (commence à 0 pour un arbre avec juste une racine) : %d\n",hauteur(*(arbre->racine)));
				if (equilibre(*arbre)) printf("L'arbre est équilibré !\n");
				else printf("L'arbre n'est pas équilibré !\n");
				choix=0;
				break;

			case 4:
				// affichage des mots par ordre alphabétique
				if (arbre==NULL){
					printf("L'arbre n'a pas été créé !\n");
					choix =0;
					break;
				}
				afficher_arbre(*arbre);
				choix=0;
				break;
			case 5:
				// recherche d'un mot
				if (arbre==NULL){
					printf("L'arbre n'a pas été créé !\n");
					choix =0;
					break;
				}
				printf("Quel mot voulez-vous rechercher ?\n>");
				nom=malloc(100*sizeof(char));
				scanf("%s",nom);
				noeud= rechercher_noeud(arbre,nom);
				if (noeud!=NULL) afficher_noeud(*noeud);
				else printf("Le nœud n'a pas été trouvé !\n");
				choix=0;
				break;
			case 6:
				// affichage des phrases contenant les 2 mots saisis
				if (arbre==NULL){
					printf("L'arbre n'a pas été créé !\n");
					choix =0;
					break;
				}

				printf("Quels mots voulez-vous rechercher ?\n>");
				nom=malloc(100*sizeof(char));
				nom2=malloc(100*sizeof(char));
				scanf("%s%s",nom,nom2);
				rechPhrase(*arbre,nom,nom2,nomfichier);

				choix=0;
				break;
			case 7:
				// EQUILIBRAGE DE L'ARBRE

				// A FAIRE
				break;
			case 8:
				// quitter

				// VIDAGE DELA MEMOIRE : A FAIRE
				break;
		}
	}while(choix>=0);
	return 0;
}
