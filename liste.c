#include <stdio.h> // A supprimer plus tard
#include <stdlib.h> // A supprimer plus tard
#include "liste.h"

ListePosition *creer_liste_positions() {
	/* Créé une nouvelle liste de positions.
	   Retourne un pointeur vers celle-ci ou NULL en cas d'échec. */
	
	ListePosition *liste_positions = (ListePosition *)malloc(sizeof(ListePosition));
	
	if (liste_positions != NULL) {
		liste_positions->nb_elements = 0;
		liste_positions->debut       = NULL;
		return liste_positions;
	}
	
	return NULL;
}

int ajouter_position(ListePosition *listeP, int ligne, int ordre, int numero_phrase) {
	/* Ajoute une position en respectant l'ordre du mot dans le texte à une ListePosition.
	   Retourne 1 en cas de succès, sinon 0. */
	
	// Création d'une nouvelle position
	Position *nouvelle_position = (Position *)malloc(sizeof(Position));
	
	if (nouvelle_position == NULL) return 0; // Une erreur d'allocation est survenue.
	
	nouvelle_position->numero_ligne  = ligne;
	nouvelle_position->ordre         = ordre;
	nouvelle_position->numero_phrase = numero_phrase;
	nouvelle_position->suivant       = NULL;
	
	if (listeP->debut == NULL) { // Cas 1 : actuellement aucune position dans la liste.
		listeP->debut = nouvelle_position;
		listeP->nb_elements++;
		printf("Ok 1\n"); // A supprimer plus tard
		return 1;
	} else { // Cas 2 : tous les autres cas. On parcourt la liste chaînée pour trouver la position d'insertion.
		Position *positionTemp = listeP->debut; // Itérateur
		
		while(positionTemp->suivant != NULL) { // Tant que nous ne sommes pas au bout de la ListePosition
			// INCOHERENCE AU NIVEAU DES CONDITIONS, A REVOIR !!!
			if (positionTemp->suivant == NULL) { // Ajout de la position en queue de liste
				positionTemp->suivant = nouvelle_position;
				nouvelle_position->suivant = NULL;
				listeP->nb_elements++;
				return 1;
			} else if (positionTemp->numero_ligne <= nouvelle_position->numero_ligne && positionTemp->ordre <= nouvelle_position->ordre) { // L'élement suivant a été trouvé, on insère la nouvelle position juste avant celui-ci.
				nouvelle_position->suivant = positionTemp->suivant;
				positionTemp->suivant = nouvelle_position;
				listeP->nb_elements++;
				return 1;
			}
			
			positionTemp = positionTemp->suivant;
		}
		
		return 0;
	}
}

int main()
{
	ListePosition *nouvelleListePositions = creer_liste_positions();
	int resAjoutPosition = ajouter_position(nouvelleListePositions, 3, 10, 2);
	int resAjoutPosition2 = ajouter_position(nouvelleListePositions, 4, 5, 2);
	int resAjoutPosition3 = ajouter_position(nouvelleListePositions, 1, 26, 12);
	
	printf("NB elts : %d, Ajout reussi ? : %d, Ajout 2 reussi ? : %d, Ajout 3 reussi ? : %d\n", nouvelleListePositions->nb_elements, resAjoutPosition, resAjoutPosition2, resAjoutPosition3);
	
	return 0;
}