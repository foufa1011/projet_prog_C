#ifndef MEMBRE_H_INCLUDED
#define MEMBRE_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	char prenom[30];
	char email[30];
	char telephone[30];
	char adresse[30];
	char ville[30];
	int genre;
	int date_jour;
	int date_mois;
	int date_annee;
	char code_postal[30];
	int poids;
	int taille;
}membre;

enum
{
	ID_MEMBRE,
	NOM_MEMBRE,
	PRENOM_MEMBRE,
	EMAIL_MEMBRE,
	TELEPHONE_MEMBRE,
	ADRESSE_MEMBRE,
	VILLE_MEMBRE,
	GENRE_MEMBRE,
	DATE_JOUR_MEMBRE,
	DATE_MOIS_MEMBRE,
	DATE_ANNEE_MEMBRE,
	CODE_POSTAL_MEMBRE,
	POIDS_MEMBRE,
	TAILLE_MEMBRE,
	COLUMNS_MEMBRE
};

int ajouter_membre(char *f, membre m);
int modifier_membre(char *f, int id, membre m);
int supprimer_membre(char *f, int id);
membre chercher_membre(char *f, int id);
int inscription_membre(char *f2, int m_id, int e_id);
void afficher_membre(GtkWidget *liste);
void vider_membre(GtkWidget *liste);

#endif  //MEMBRE_H_INCLUDED
