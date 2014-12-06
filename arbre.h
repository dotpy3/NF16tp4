// D�finition du type NoeudABR correspondant � une structure qui contient les deux fils du noeud d'un arbre, le mot qu'elle repr�sente et un lien vers la liste des positions de ce mot.
typedef struct NoeudABR {
	char *mot;
	ListePosition positions;
	struct NoeudABR *filsGauche;
	struct NoeudABR *filsDroit;
} NoeudABR;

// D�finition du type ArbreBR correspondant � une structure qui contient diff�rentes informations sur les mots du texte et un lien vers le noeud racine.
typedef struct ArbreBR {
	struct NoeudABR *racine;
	int nb_mots_differents;
	int nb_mots_total;
} ArbreBR;

// D�finition des prototypes de fonction ayant trait aux ABR, aux noeuds de l'ABR ou encore � son affichage.
ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, char *mot, int ligne, int ordre, int numPhrase);
NoeudABR *rechercher_noeud(ArbreBR *arbre, char *mot);
void afficher_noeud(NoeudABR noeud);
void afficher_noeuds(NoeudABR noeud);
void afficher_arbre(ArbreBR arbre);
