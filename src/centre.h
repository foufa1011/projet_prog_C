#ifndef CENTRE_H_INCLUDED
#define CENTRE_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	char ville[30];
	int horaire_ouverture;
	int horaire_fermeture;
	int membre_limit;
	int type;
	int activites;
}centre;

enum
{
	ID,
	NOM,
	VILLE,
	HORAIRE_OUVERTURE,
	HORAIRE_FERMETURE,
	MEMBRE_LIMIT,
	TYPE,
	ACTIVITES,
	COLUMNS
};

int ajouter(char *f, centre c);
int modifier(char *f, int id, centre c);
int supprimer(char *f, int id);
centre chercher(char *f, int id);
int inscription(char *f2, int c_id, int e_id);
void afficher(GtkWidget *liste);
void vider(GtkWidget *liste);

#endif  //CENTRE_H_INCLUDED
