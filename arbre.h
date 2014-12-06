// Définition du type NoeudABR correspondant à une structure qui contient les deux fils du noeud d'un arbre, le mot qu'elle représente et un lien vers la liste des positions de ce mot.
typedef struct NoeudABR {
	char *mot;
	ListePosition positions;
	struct NoeudABR *filsGauche;
	struct NoeudABR *filsDroit;
} NoeudABR;

// Définition du type ArbreBR correspondant à une structure qui contient différentes informations sur les mots du texte et un lien vers le noeud racine.
typedef struct ArbreBR {
	struct NoeudABR *racine;
	int nb_mots_differents;
	int nb_mots_total;
} ArbreBR;

// Définition des prototypes de fonction ayant trait aux ABR, aux noeuds de l'ABR ou encore à son affichage.
ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre, int numPhrase);
NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot);
void afficher_noeuds(NoeudABR noeud);
void afficher_arbre(ArbreBR arbre);