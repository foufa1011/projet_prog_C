#ifndef EQUIPEMENT_H_INCLUDED
#define EQUIPEMENT_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	char categorie[30];
	int annee_achat;
	int mois_achat;
	int jour_achat;
	int etat;
	int quantite;
	
}equipement;

enum
{
	ID,
	NOM,
	CATEGORIE,
	ANNEE_ACHAT,
	MOIS_ACHAT,
	JOUR_ACHAT,
	ETAT,
	QUANTITE,
	COLUMNS
};

int ajouter(char *f, equipement e);
int modifier(char *f, int id, equipement e);
int supprimer(char *f, int id);
equipement chercher(char *f, int id);
void afficher(GtkWidget *liste);
void vider(GtkWidget *liste);

#endif  //EQUIPEMENT_H_INCLUDED
