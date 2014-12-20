ArbreBR *creer_abr() {
	/* Créé un nouvel ABR vide.
       Retourne un pointeur vers celui-ci ou NULL en cas d'échec. */

	ArbreBR *arbre = (ArbreBR *)malloc(sizeof(ArbreBR));

	if (arbre != NULL) {
		arbre->nb_mots_differents = 0;
		arbre->nb_mots_total      = 0;
		arbre->racine             = NULL;
		return arbre;
	}

	return NULL;
}

int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre, int numPhrase) {
	/* Ajoute un noeud à l'ABR.
       Retourne 1 en cas de succès, sinon 0. */

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
		} else if (strcmp(iter->mot,mot) > 0){
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
		} else if (strcmp(iter->mot,mot) < 0){

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

NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot) {
	/* Recherche un noeud dans l'ABR.
       Retourne un pointeur vers le celui-ci ou NULL en cas d'échec. */

	NoeudABR *iter=arbre->racine;

	if (iter==NULL) return NULL;

	while(strcmp(iter->mot,mot) != 0){
		if(strcmp(iter->mot,mot) > 0){
			if(iter->filsGauche == NULL) return NULL;
			else iter=iter->filsGauche;
		} else {
			if(iter->filsDroit == NULL) return NULL;
			else iter=iter->filsDroit;
		}
	}

	return iter;
}

void afficher_noeud(NoeudABR noeud) {
	// idem que afficher_noeuds, mais sans la récurrence
	printf("==> MOT : %s\n",noeud.mot);
	Position *iter=(noeud.positions).debut;
	while(iter != NULL){
		printf("Ligne n°%d, Phrase n°%d, Occurence n°%d.\n", iter->numero_ligne, iter->numero_phrase, iter->ordre);
		iter=iter->suivant;
	}
	printf("\n");
}

void afficher_noeuds(NoeudABR noeud) {
	if (noeud.filsGauche != NULL)
		afficher_noeuds(*(noeud.filsGauche));
	afficher_noeud(noeud);
	if (noeud.filsDroit != NULL)
		afficher_noeuds(*(noeud.filsDroit));
	return;
}

void afficher_arbre(ArbreBR arbre) {
	if (arbre.racine == NULL) return;
	afficher_noeuds(*(arbre.racine));
}

int nb_descendents(NoeudABR noeud) {
	// pour un nœud défini, rend le nombre de descendents
	int nbDesc=0;
	if (noeud.filsGauche != NULL){
		nbDesc = nbDesc+1+nb_descendents(*(noeud.filsGauche));
	}
	if (noeud.filsDroit != NULL){
		nbDesc = nbDesc+1+nb_descendents(*(noeud.filsDroit));
	}
	return nbDesc;
}

int hauteur(NoeudABR noeud) {
	// pour un nœud défini, rend la hauteur (qui commence à 0)
	int fG, fD, hau;
	if (noeud.filsGauche == NULL){
		if (noeud.filsDroit == NULL) {
			return 0;
		}
		else {
			hau = hauteur(*(noeud.filsDroit))+1;
			return hau;
		}
	} else if (noeud.filsDroit == NULL) {
		hau = hauteur(*(noeud.filsGauche))+1;
		return hau;
	}
	else {
		fG = hauteur(*(noeud.filsGauche))+1;
		fD = hauteur(*(noeud.filsDroit))+1;
		if (fG > fD) {
			return fG;
		}
		else {
			return fD;
		}
	}
}

int equNoeud(NoeudABR noeud) {
	// rend 1 si le nœud est équilibré
	// rend 0 si le nœud n'est pas équilibré
	if(noeud.filsGauche == NULL){
		if(noeud.filsDroit == NULL || hauteur(*(noeud.filsDroit)) == 0) return 1;
		else return 0;
	} else if(noeud.filsDroit == NULL){
		if(noeud.filsGauche == NULL || hauteur(*(noeud.filsGauche)) == 0) return 1;
		else return 0;
	} else {
		int hG =hauteur(*(noeud.filsGauche)), hD = hauteur(*(noeud.filsDroit));
		if ((hG - hD) >= -1 && (hG - hD) <= 1) return 1;
		else return 0;
	}
}

int equNoeudRec(NoeudABR noeud) {
	// rend 1 si le nœud et tous ses descendents sont équilibrés
	// rend 0 sinon
	if (equNoeud(noeud) == 0) return 0;
	else {
		if (noeud.filsGauche == NULL && noeud.filsDroit == NULL) return 1;
		else if (noeud.filsGauche == NULL) return equNoeudRec(*(noeud.filsDroit));
		else if (noeud.filsDroit == NULL) return equNoeudRec(*(noeud.filsGauche));
		else if (equNoeudRec(*(noeud.filsGauche)) == 1 && equNoeudRec(*(noeud.filsDroit)) == 1) return 1;
		else return 0;
	}
}

int equilibre(ArbreBR arbre) {
	// On considère qu'un arbre est équilibré si en tout nœud x, |hauteur(droit(x))-hauteur(gauche(x))| <= 1.
	// rend 1 si l'arbre est équilibré
	// rend 0 sinon
	return equNoeudRec(*(arbre.racine));
}

void rechPhrase(ArbreBR arbre, char* str1, char* str2, char* nomfichier) {
	// Cette phrase affiche toutes les phrases contenant les 2 mots saisis.

	racine init=malloc(sizeof(struct listeC)),iter;
	init->val=-1;
	init->suiv=NULL;

	NoeudABR *noeud1 = rechercher_noeud(&arbre,str1);
	NoeudABR *noeud2 = rechercher_noeud(&arbre,str2);

	if(noeud1 == NULL || noeud2 == NULL) {
		printf("Un ou plusieurs mots n'a pas été trouvé.\n\n");
		return;
	}

	// à ce stade on trouve bien les deux mots dans le texte, on va donc chercher dans quelles phrases ils se trouvent
	struct Position *posmot1=(noeud1->positions).debut;
	struct Position *posmot2;
	while(posmot1 != NULL){
		posmot2 =(noeud2->positions).debut;
		while(posmot2 != NULL){
			if(posmot1->numero_phrase == posmot2->numero_phrase){
				 iter=init;
				 while(iter != NULL && iter->val != posmot1->numero_phrase) iter=iter->suiv;
				 if(iter == NULL){
				 		afficher_phrase(posmot1->numero_phrase,nomfichier);
						printf("\n");
						iter=init;
						while(iter->suiv != NULL) iter=iter->suiv;
						iter->suiv = malloc(sizeof(struct listeC));
						iter->suiv->val=posmot1->numero_phrase;
						iter->suiv->suiv=NULL;
					}
			}
			posmot2=posmot2->suivant;
		}
		posmot1=posmot1->suivant;
	}

	return;
}

void afficher_phrase(int nb,char* filename) {
    FILE * fichier = fopen(filename, "r");
	char * buf = (char *)malloc(sizeof(char)); // Buffer de la taille d'un caractère
	int numLigne = 1, ordreMot = 1, numPhrase = 1, i = 0;

	while(!feof(fichier)) {
		fread(buf, 1, 1, fichier);
		if(buf[0] == '\n') {
            if (numPhrase == nb) printf(" ");
		    if (i != 0) {
                numLigne++;
                ordreMot = 1;
                i = 0;
		    }
		} else if (buf[0] == '.') {
            if (numPhrase == nb) printf("%c",buf[0]);
		    if (i != 0) {
                numPhrase++;
                i = 0;
            }
        } else {
            if (numPhrase == nb) printf("%c",buf[0]);
            i++;
		}
	}
	printf("\n");
	return;
}

void supprimer_arbre(ArbreBR* arbre) {
	/* Libère la mémoire associée à l'élément ArbreBR. */

	if (arbre->racine != NULL) supprimer_noeuds(arbre->racine);
	free(arbre);
}

void supprimer_noeuds(NoeudABR* noeud) {
	/* Libère la mémoire associée à chaque noeuds de l'ABR. */

	if(noeud->filsGauche != NULL) supprimer_noeuds(noeud->filsGauche);
	if(noeud->filsDroit != NULL) supprimer_noeuds(noeud->filsDroit);
	supprimer_listePositions(noeud);
	free(noeud->mot);
	free(noeud);
}

void supprimer_listePositions(NoeudABR* noeud) {
	/* Libère la mémoire associée à la liste de positions d'un noeud. */

	struct Position* iter1, *iter2;
	iter1=(noeud->positions).debut;
	iter2=iter1->suivant;
	while(iter2 != NULL){
		free(iter1);
		iter1=iter2;
		iter2=iter2->suivant;
	}
	free(iter1);
}

NoeudABR* pere(ArbreBR *arbre, NoeudABR* noeud) {
	/* Récupère le père d'un noeud.
	   Retourne le noeud père si celui-ci existe ou NULL dans le cas opposé. */

	return recupPere(arbre->racine,noeud);
}

NoeudABR* recupPere(NoeudABR* noeudEtu, NoeudABR* noeud) {
	/* Récupère le père d'un noeud.
	   Retourne le noeud père si celui-ci existe ou NULL dans le cas opposé. */

	if (noeudEtu == NULL) return NULL;

	NoeudABR* fG = noeudEtu->filsGauche;
	NoeudABR* fD = noeudEtu->filsDroit;

	if (fG == noeud || fD == noeud) return noeudEtu;
	else {
		fG = recupPere(fG, noeud);
		fD = recupPere(fD, noeud);
		if(fG != NULL) return fG;
		else if (fD != NULL) return fD;
		else return NULL;
	}
}

NoeudABR* RotDroite(ArbreBR *arbre, NoeudABR* noeud) {
	/* Cette fonction effectue une rotation droite.
	   Renvoie le nouveau père de noeud ou NULL si la rotation a échoué */

	if (noeud != NULL && noeud->filsGauche != NULL) {
		NoeudABR* y = noeud->filsGauche;
		NoeudABR* c = noeud->filsDroit;
		NoeudABR* pereN = pere(arbre,noeud);
		if(pereN != NULL) {
			if(pereN->filsGauche == noeud) {
				pereN->filsGauche = y;
			} else {
				pereN->filsDroit = y;
			}
		} else arbre->racine = y;
		y->filsDroit = noeud;
		noeud->filsGauche = c;
		return y;
	}

	return NULL;
}

NoeudABR* RotGauche(ArbreBR *arbre, NoeudABR* noeud) {
	/* Cette fonction effectue une rotation gauche.
	   Renvoie le nouveau père de noeud ou NULL si la rotation a échoué */

	if (noeud != NULL && noeud->filsGauche != NULL) {
		NoeudABR* x = noeud->filsDroit;
		NoeudABR* c = noeud->filsGauche;
		NoeudABR* pereN = pere(arbre,noeud);
		if(pereN != NULL) {
			if(pereN->filsGauche == noeud) {
				pereN->filsGauche = x;
			} else {
				pereN->filsDroit = x;
			}
		} else arbre->racine = x;
		x->filsGauche = noeud;
		noeud->filsDroit = c;
		return x;
	}

	return NULL;
}

void equilibrage(ArbreBR* arbre, NoeudABR* noeud) {
	/* Equilibre l'arbre en effectuant une rotation à droite où une rotation à gauche selon la hauteur des sous arbres au noeud donné. */
    if (noeud == NULL) return;

	int hauteurG, hauteurD, diffHauteur;

	if(noeud->filsGauche != NULL) {
		equilibrage(arbre,noeud->filsGauche);
		hauteurG = hauteur(*(noeud->filsGauche));
	} else hauteurG = -1;

	if(noeud->filsDroit != NULL) {
		equilibrage(arbre,noeud->filsDroit);
		hauteurD = hauteur(*(noeud->filsDroit));
	} else hauteurD = -1;

	// on a défini les hauteurs
	diffHauteur = hauteurG - hauteurD;

	if(diffHauteur > 1) {
		// alors l'arbre est trop haut à gauche et pas assez haut à droite
		equilibrage(arbre,RotDroite(arbre,noeud));
	} else if (diffHauteur < -1) {
		equilibrage(arbre,RotGauche(arbre,noeud));
	}
}
