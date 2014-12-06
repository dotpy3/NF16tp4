// Définition du type Position correspondant à une structure qui contient les différentes informations de caractérisation de la position d'un mot dans le texte.
typedef struct Position {
	int numero_ligne;
	int ordre;
	int numero_phrase;
	struct Position *suivant;
} Position;

// Définition du type ListePosition correspondant à une structure permettant de regrouper la liste de positions de toutes les occurences d'un mot dans un texte.
typedef struct ListePosition {
	struct Position *debut;
	int nb_elements;
} ListePosition;

// Définition des prototypes de fonction ayant trait au traitementt des positions et listes de positions.
ListePosition *creer_liste_positions();
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int numero_phrase);