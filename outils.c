int charger_fichier(ArbreBR *arbre, char *filename) {
	FILE *fichier = fopen(filename, "r");

	if(fichier != NULL) { // Fichier ouvert avec succès.
		char mot[100]; // Longueur maximale d'un mot.
		char c;
		int nombre_mots = 0, numero_ligne = 0, numero_mot = 0;

		do {
			c = fscanf(fichier, "%s", mot); // Récupère un mot.
			printf("Mot : %s\t\t\t\t\tNumero : %d\tLigne : %d\tPosition : %d\n", mot, nombre_mots, numero_ligne, numero_mot); // Affiche ce mot.
			ajouter_noeud(arbre, mot, numero_ligne, numero_mot, numero_ligne); // A REVOIR, LES VARIABLES SONT LES MAUVAISES !!!!

			if (c == '\n')
		        numero_ligne++;

			nombre_mots++;
		} while (c != EOF); // Arrête la lecture à la fin du fichier.

		printf("Ok\n");

		fclose(fichier); // Fermeture du flux vers le fichier.

		return nombre_mots;
	} else { // Erreur d'ouverture du fichier.
		printf("Erreur de lecture du fichier %s.\n", filename);
		fclose(fichier); // Fermeture du flux vers le fichier.

		return 0;
	}
}