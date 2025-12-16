#ifndef COURS_H_INCLUDED
#define COURS_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	char type[30];
	int date_heure;
	int date_minute;
	int date_jour;
	int date_mois;
	int date_annee;
	int duree;
	
}cours;

enum
{
	ID_COURS,
	NOM_COURS,
	TYPE_COURS,
	DATE_HEURE_COURS,
	DATE_MINUTE_COURS,
	DATE_JOUR_COURS,
	DATE_MOIS_COURS,
	DATE_ANNEE_COURS,
	DUREE_COURS,
	COLUMNS_COURS
};

int ajouter_cours(char *f, cours c);
int modifier_cours(char *f, int id, cours c);
int supprimer_cours(char *f, int id);
cours chercher_cours(char *f, int id);
void afficher_cours(GtkWidget *liste);
void vider_cours(GtkWidget *liste);

#endif  //COURS_H_INCLUDED
