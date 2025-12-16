#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	int type;
	int date_jour;
	int date_mois;
	int date_annee;
	int date_heure;
	int date_minute;
	
}evenement;

enum
{
	ID_EVENEMENT,
	NOM_EVENEMENT,
	TYPE_EVENEMENT,
	DATE_JOUR_EVENEMENT,
	DATE_MOIS_EVENEMENT,
	DATE_ANNEE_EVENEMENT,
	DATE_HEURE_EVENEMENT,
	DATE_MINUTE_EVENEMENT,
	COLUMNS_EVENEMENT
};

int ajouter_evenement(char *f, evenement e);
int modifier_evenement(char *f, int id, evenement e);
int supprimer_evenement(char *f, int id);
evenement chercher_evenement(char *f, int id);
void afficher_evenement(GtkWidget *liste);
void vider_evenement(GtkWidget *liste);

#endif  //EVENEMENT_H_INCLUDED
