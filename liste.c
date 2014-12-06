ListePosition *creer_liste_positions() {
	/* Créé une nouvelle liste de positions.
	   Retourne un pointeur vers celle-ci ou NULL en cas d'�chec. */

	ListePosition *liste_positions = (ListePosition *)malloc(sizeof(ListePosition));

	if (liste_positions != NULL) {
		liste_positions->nb_elements = 0;
		liste_positions->debut       = NULL;
		return liste_positions;
	}

	return NULL;
}

int ajouter_position(ListePosition *listeP, int ligne, int ordre, int numero_phrase) {
	/* Ajoute une position en respectant l'ordre du mot dans le texte � une ListePosition.
	   Retourne 1 en cas de succ�s, sinon 0. */

	// Cr�ation d'une nouvelle position
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
	} else { // Cas 2 : tous les autres cas. On parcourt la liste cha�n�e pour trouver la position d'insertion.
		Position *positionTemp = listeP->debut; // It�rateur

		while(positionTemp->suivant != NULL) { // Tant que nous ne sommes pas au bout de la ListePosition
			 if (positionTemp->numero_ligne <= nouvelle_position->numero_ligne && positionTemp->ordre <= nouvelle_position->ordre) { // L'�lement suivant a �t� trouv�, on ins�re la nouvelle position juste avant celui-ci.
				nouvelle_position->suivant = positionTemp->suivant;
				positionTemp->suivant = nouvelle_position;
				listeP->nb_elements++;
				return 1;
			}

			positionTemp = positionTemp->suivant;
		}

		if (positionTemp->suivant == NULL) { // Ajout de la position en queue de liste
			positionTemp->suivant = nouvelle_position;
			listeP->nb_elements++;
			return 1;
		}

		return 0;
	}
}
