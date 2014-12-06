#include "arbre.h"

ArbreBR *creer_abr() {
	/* Cr�� un nouvel ABR vide.
       Retourne un pointeur vers celui-ci ou NULL en cas d'�chec. */

	ArbreBR *arbre = (ArbreBR *)malloc(sizeof(ArbreBR));

	if (arbre != NULL) {
		arbre->nb_mots_differents = 0;
		arbre->nb_mots_total      = 0;
		arbre->racine             = NULL;
		return arbre;
	}

	return NULL;
}

int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre, int numPhrase){
	if (arbre == NULL || mot == NULL)
		return 0; // Cas où l'arbre ou le mot ne sont pas définis




	// AJOUT DU NŒUD DANS L'ARBRE DE RECHERCHE

		// PREMIER CAS : IL N'Y A PAS DE NOEUD DANS L'ARBRE

	if (arbre->racine == NULL){

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
		if (ajouter_position(listePosN,ligne,ordre,numPhrase) == 0) return 0;
		noeudAAdd->positions=*listePosN;

		arbre->nb_mots_differents++;
		arbre->nb_mots_total++;
		arbre->racine = noeudAAdd;
		return 1;
	}

		// SECOND CAS : IL Y A DES NOEUDS DANS L'ARBRE

	struct NoeudABR *iter=arbre->racine;
	do{
		// On rentre dans une boucle avec iter qui parcourt tous les éléments de l'arbre.
		// Lorsqu'on a fini, on met iter à null pour signifier la fin de la boucle.

		if (strcmp(iter->mot,mot) == 0){
			// alors il y a déjà une occurence du mot dans l'arbre
			ajouter_position(&(iter->positions),ligne,ordre,numPhrase);
			arbre->nb_mots_total++;
			iter=NULL;
		} else if (strcmp(iter->mot,mot) < 0){
			// si le nouveau mot est situé avant le suivant

			if (iter->filsGauche != NULL) iter=iter->filsGauche;

			else{

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
				if (ajouter_position(listePosN,ligne,ordre,numPhrase) == 0) return 0;
				noeudAAdd->positions=*listePosN;

				arbre->nb_mots_differents++;

				arbre->nb_mots_total++;
				iter->filsGauche=noeudAAdd;
				iter=NULL;
			}
		} else if (strcmp(iter->mot,mot) > 0){

			if (iter->filsDroit != NULL) iter=iter->filsDroit;

			else{

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
				if (ajouter_position(listePosN,ligne,ordre,numPhrase) == 0) return 0;
				noeudAAdd->positions=*listePosN;

				arbre->nb_mots_differents++;

				arbre->nb_mots_total++;
				iter->filsDroit=noeudAAdd;
				iter=NULL;
			}

		} else return 0;
	}while(iter!=NULL);

	return 1;
}

NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot){
	// Rend NULL si le noeud n'a pas été trouvé
	// sinon rend le pointeur vers le nœud correspondant
	NoeudABR *iter=arbre->racine;

	if (iter==NULL) return NULL;

	while(strcmp(iter->mot,mot) != 0){
		if(strcmp(iter->mot,mot) < 0){
			if(iter->filsGauche == NULL) return NULL;
			else iter=iter->filsGauche;
		} else {
			if(iter->filsDroit == NULL) return NULL;
			else iter=iter->filsDroit;
		}
	}

	return iter;
}

void afficher_noeud(NoeudABR noeud){
	// idem que afficher_noeuds, mais sans la récurrence
	printf("=====> MOT : %s\n",noeud.mot);
	Position *iter=(noeud.positions).debut;
	while(iter != NULL){
		printf("%d-e occurence : s'affiche en ligne %d, à la %d-e phrase.\n",iter->ordre,iter->numero_ligne,iter->numero_phrase);
		iter=iter->suivant;
	}
	return;
}

void afficher_noeuds(NoeudABR noeud){
	if (noeud.filsGauche != NULL)
		afficher_noeuds(*(noeud.filsGauche));
	afficher_noeud(noeud);
	if (noeud.filsDroit != NULL)
		afficher_noeuds(*(noeud.filsDroit));
	return;
}

void afficher_arbre(ArbreBR arbre){
	if (arbre.racine == NULL) return;
	afficher_noeuds(*(arbre.racine));
}

/*
int main()
{
	ArbreBR *nouvel = creer_abr();

	printf("NB elts : %d\n", nouvel->nb_mots_differents);

	return 0;
}*/
