#include <stdio.h> // A supprimer plus tard
#include <stdlib.h> // A supprimer plus tard
#include "liste.h" // A supprimer plus tard
#include "arbre.h"

ArbreBR *creer_abr() {
	/* Cr�� un nouvel ABR vide.
       Retourne un pointeur vers celui-ci ou NULL en cas d'�chec. */

	ArbreBR *abr = (ArbreBR *)malloc(sizeof(ArbreBR));

	if (abr != NULL) {
		abr->nb_mots_differents = 0;
		abr->nb_mots_total      = 0;
		abr->racine             = NULL;
		return abr;
	}

	return NULL;
}

int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre){
	if (arbre == NULL || mot == NULL)
		return 0; // Cas où l'arbre ou le mot ne sont pas définis


	// AJOUT DU NŒUD DANS LA MEMOIRE
	NoeudABR* noeudAAdd=(NoeudABR*)malloc(sizeof(NoeudABR));
		// Ce nœud est le nœud qu'on veut ajouter.
	if (noeudAAdd==NULL) return 0;
		// On crée le nœud qu'on veut ajouter.
	noeudAAdd->mot = mot;
	noeudAAdd->filsGauche=NULL;
	noeudAAdd->filsDroit=NULL;

	// On crée la liste des positions.

	ListePosition* listePosN=creer_liste_positions();
	if (ajouter_position(listePosN,ligne,ordre) == 0) return 0;
	noeudAAdd->positions=*listePosN;

	// AJOUT DU NŒUD DANS L'ARBRE DE RECHERCHE

		// PREMIER CAS : IL N'Y A PAS DE NOEUD DANS L'ARBRE

	if (arbre->racine == NULL){

		abr->nb_mots_differents++;
		abr->nb_mots_total++;
		arbre->racine = noeudAAdd;
		return 1;
	}

		// SECOND CAS : IL Y A DES NOEUDS DANS L'ARBRE

	struct NoeudABR *iter=arbre->racine;
	do{
		if (strcmp(iter->mot,mot) == 0){
			// alors il y a déjà une occurence du mot dans l'arbre
			ajouter_position(iter->positions,ligne,ordre)
		} else if (strcmp(iter->mot,mot) < 0){
			if (iter->filsGauche != NULL) iter=iter->filsGauche;
			else{
				abr->nb_mots_differents++;

				abr->nb_mots_total++;
			}
		} else if (strcmp(iter->mot,mot) > 0){

		} else return 0;
	}while(iter!=NULL);
}
/*
int main()
{
	ArbreBR *nouvel = creer_abr();

	printf("NB elts : %d\n", nouvel->nb_mots_differents);

	return 0;
}*/
