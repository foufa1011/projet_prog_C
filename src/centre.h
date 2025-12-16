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
	ID_CENTRE,
	NOM_CENTRE,
	VILLE,
	HORAIRE_OUVERTURE,
	HORAIRE_FERMETURE,
	MEMBRE_LIMIT,
	TYPE,
	ACTIVITES,
	COLUMNS_CENTRE
};

int ajouter_centre(char *f, centre c);
int modifier_centre(char *f, int id, centre c);
int supprimer_centre(char *f, int id);
centre chercher_centre(char *f, int id);
int inscription_centre(char *f2, int c_id, int e_id);
void afficher_centre(GtkWidget *liste);
void vider_centre(GtkWidget *liste);

#endif  //CENTRE_H_INCLUDED
