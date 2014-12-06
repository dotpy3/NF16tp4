typedef struct Position {
	int numero_ligne;
	int ordre;
	int numero_phrase;
	struct Position *suivant;
} Position;

typedef struct ListePosition {
	struct Position *debut;
	int nb_elements;
} ListePosition;

ListePosition *creer_liste_positions();
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int numero_phrase);
