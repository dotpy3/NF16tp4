// D�finition du type Position correspondant � une structure qui contient les diff�rentes informations de caract�risation de la position d'un mot dans le texte.
typedef struct Position {
	int numero_ligne;
	int ordre;
	int numero_phrase;
	struct Position *suivant;
} Position;

// D�finition du type ListePosition correspondant � une structure permettant de regrouper la liste de positions de toutes les occurences d'un mot dans un texte.
typedef struct ListePosition {
	struct Position *debut;
	int nb_elements;
} ListePosition;

// D�finition des prototypes de fonction ayant trait au traitementt des positions et listes de positions.
ListePosition *creer_liste_positions();
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int numero_phrase);
