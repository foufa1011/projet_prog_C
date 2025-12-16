#ifndef ENTRAINEUR_H_INCLUDED
#define ENTRAINEUR_H_INCLUDED

#include <gtk/gtk.h>

typedef struct
{
	int id;
	char nom[30];
	char prenom[30];
	char adresse_postal[30];
	char adresse_mail[30];
	char telephone[30];
	int genre;
	int date_nais_jour;
	int date_nais_mois;
	int date_nais_annee;
	int date_deb_jour;
	int date_deb_mois;
	int date_deb_annee;
	int statut;
}entraineur;

enum
{
	ID_ENTRAINEUR,
	NOM_ENTRAINEUR,
	PRENOM_ENTRAINEUR,
	ADRESSE_POSTAL_ENTRAINEUR,
	ADRESSE_MAIL_ENTRAINEUR,
	TELEPHONE_ENTRAINEUR,
	GENRE_ENTRAINEUR,
	DATE_NAIS_JOUR_ENTRAINEUR,
	DATE_NAIS_MOIS_ENTRAINEUR,
	DATE_NAIS_ANNEE_ENTRAINEUR,
	DATE_DEB_JOUR_ENTRAINEUR,
	DATE_DEB_MOIS_ENTRAINEUR,
	DATE_DEB_ANNEE_ENTRAINEUR,
	STATUT_ENTRAINEUR,
	COLUMNS_ENTRAINEUR
};

int ajouter_entraineur(char *f, entraineur e);
int modifier_entraineur(char *f, int id, entraineur e);
int supprimer_entraineur(char *f, int id);
entraineur chercher_entraineur(char *f, int id);
int inscription_entraineur(char *f2, int c_id, int e_id);
void afficher_entraineur(GtkWidget *liste);
void vider_entraineur(GtkWidget *liste);

#endif  //ENTRAINEUR_H_INCLUDED
