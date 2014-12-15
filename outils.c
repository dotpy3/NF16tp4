int charger_fichier(ArbreBR *arbre, char *filename) {
	FILE * fichier = fopen(filename, "r");
	char * buf = (char *)malloc(sizeof(char)); // Buffer de la taille d'un caractère
	char * mot  = malloc(TAILLE_MOT*sizeof(char));
	int numLigne = 1, ordreMot = 1, numPhrase = 1, i = 0;

	while(!feof(fichier)) {
		fread(buf, sizeof(unsigned char), 1, fichier);
		if(buf[0] == '\n') {
		    if (i != 0) {
                mot[i] = '\0';
                printf("Mot : %s, numLigne : %d, ordreMot : %d, numPhrase : %d\n", mot, numLigne, ordreMot, numPhrase);
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                numLigne++;
                ordreMot = 1;
                i = 0;
		    }
		} else if (buf[0] == '.') {
		    if (i != 0) {
		        mot[i] = '\0';
		        printf("Mot : %s, numLigne : %d, ordreMot : %d, numPhrase : %d\n", mot, numLigne, ordreMot, numPhrase);
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                numPhrase++;
                i = 0;
            }
        } else if (buf[0] == ' ') {
            if (i != 0) {
                mot[i] = '\0';
                printf("Mot : %s, numLigne : %d, ordreMot : %d, numPhrase : %d\n", mot, numLigne, ordreMot, numPhrase);
                ajouter_noeud(arbre, mot, numLigne, ordreMot, numPhrase);
                mot  = malloc(TAILLE_MOT*sizeof(char));
                ordreMot++;
                i = 0;
            }
		//} else if ((buf[0] >= 'a' && buf[0] <= 'z') || (buf[0] >= 'A' && buf[0] <= 'Z') || (buf[0] >= '0' && buf[0] <= '9') || (buf[0] >= 128 && buf[0] <= 165)) { // Majuscule ou Minuscule ou Chiffre ou Lettres accentuées
		} else {
            mot[i] = buf[0];
            i++;
		}
	}

	fclose(fichier);

	return 1; // ajuster le return
}
