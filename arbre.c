#include <stdio.h> // A supprimer plus tard
#include <stdlib.h> // A supprimer plus tard
#include "liste.h" // A supprimer plus tard
#include "arbre.h"

ArbreBR *creer_abr() {
	/* Créé un nouvel ABR vide.
       Retourne un pointeur vers celui-ci ou NULL en cas d'échec. */
	
	ArbreBR *abr = (ArbreBR *)malloc(sizeof(ArbreBR));
	
	if (abr != NULL) {
		abr->nb_mots_differents = 0;
		abr->nb_mots_total      = 0;
		abr->racine             = NULL;
		return abr;
	}
	
	return NULL;
}
/*
int main()
{
	ArbreBR *nouvel = creer_abr();
	
	printf("NB elts : %d\n", nouvel->nb_mots_differents);
	
	return 0;
}*/