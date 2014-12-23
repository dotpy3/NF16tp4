int charger_fichier(ArbreBR *arbre, char *filename) {
	/* Charge chaque mot d'un fichier dans un ABR.
	   Retourne le nombre de mots traités. */
	
	FILE * fichier = fopen(filename, "r");         // Ouverture du fichier filename
	char * buf = (char *)malloc(sizeof(char));     // Buffer de la taille d'un caractère
	char * mot  = malloc(TAILLE_MOT*sizeof(char)); // Buffer de la taille d'un mot
	int numLigne = 1, ordreMot = 1, numPhrase = 1, i = 0, nbMots = 0;

	while(!feof(fichier)) { // La boucle s'arrête à la fin du fichier.
		fread(buf, sizeof(unsigned char), 1, fichier); // Lecture d'un caractère du fichier.
		if(buf[0] == '\n') { // Cas de la fin d'une ligne.
		    if (i != 0) { // Si le mot n'est pas vide.
                mot[i] = '\0';
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                numLigne++;
                ordreMot = 1;
                i = 0;
				nbMots++;
		    }
		} else if (buf[0] == '.') { // Cas de la fin d'une phrase.
		    if (i != 0) { // Si le mot n'est pas vide.
		        mot[i] = '\0';
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                numPhrase++;
				ordreMot++;
                i = 0;
				nbMots++;
            }
        } else if (buf[0] == ' ') { // Cas de la fin d'un mot.
            if (i != 0) { // Si le mot n'est pas vide.
                mot[i] = '\0';
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                ordreMot++;
                i = 0;
				nbMots++;
            }
		} else {
			if(buf[0] >= 'A' && buf[0] <= 'Z') { // Majuscule
				// On transforme la majuscule en minuscule.
				mot[i] = buf[0] + 'a' - 'A';
			} else {
				mot[i] = buf[0];
			}
            i++;
		}
	}

	fclose(fichier); // Fermeture du flux vers le fichier.
	return nbMots;   // Renvoie le nombre de mots lus.
}
