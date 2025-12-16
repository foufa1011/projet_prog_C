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
	
}reservation_equipement;

enum
{
	ID_EQUIPEMENT,
	NOM_EQUIPEMENT,
	CATEGORIE,
	ANNEE_ACHAT,
	MOIS_ACHAT,
	JOUR_ACHAT,
	ETAT,
	QUANTITE,
	COLUMNS_EQUIPEMENT
};

int ajouter_equipement(char *f, equipement e);
int modifier_equipement(char *f, int id, equipement e);
int supprimer_equipement(char *f, int id);
equipement chercher_equipement(char *f, int id);
void afficher_equipement(GtkWidget *liste);
void vider_equipement(GtkWidget *liste);

#endif  //EQUIPEMENT_H_INCLUDED
