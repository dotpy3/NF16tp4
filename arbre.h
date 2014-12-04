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