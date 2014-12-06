typedef struct NoeudABR {
	char *mot;
	ListePosition positions;
	struct NoeudABR *filsGauche;
	struct NoeudABR *filsDroit;
} NoeudABR;

typedef struct ArbreBR {
	struct NoeudABR *racine;
	int nb_mots_differents;
	int nb_mots_total;
} ArbreBR;

ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre, int numPhrase);
NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot);
void afficher_noeud(NoeudABR noeud);
void afficher_noeuds(NoeudABR noeud);
void afficher_arbre(ArbreBR arbre);
