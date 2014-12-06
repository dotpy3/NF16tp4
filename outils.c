#include "outils.h"

int charger_fichier(ArbreBR *arbre, char *filename) {
	FILE *fichier = fopen(filename, "r");

	if(fichier != NULL) { // Fichier ouvert avec succ�s.
		char mot[100]; // Longueur maximale d'un mot.
		char c;
		int nombre_mots = 0, numero_ligne = 0, numero_mot = 0;

		do {
			c = fscanf(fichier, "%s", mot); // R�cup�re un mot.
			printf("Mot : %s\t\t\t\t\tNumero : %d\tLigne : %d\tPosition : %d\n", mot, nombre_mots, numero_ligne, numero_mot); // Affiche ce mot.

			if (c == '\n')
		        numero_ligne++;

			nombre_mots++;
		} while (c != EOF); // Arr�te la lecture � la fin du fichier.

		printf("Ok\n");

		fclose(fichier); // Fermeture du flux vers le fichier.

		return nombre_mots;
	} else { // Erreur d'ouverture du fichier.
		printf("Erreur de lecture du fichier %s.\n", filename);
		fclose(fichier); // Fermeture du flux vers le fichier.

		return 0;
	}
}