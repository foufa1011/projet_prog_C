#include "entraineur.h"
#include <stdio.h>
int ajouter_entraineur(char *filename, entraineur e)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		entraineur temp;
		while(fscanf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", &temp.id, temp.nom, temp.prenom, temp.adresse_postal, temp.adresse_mail, temp.telephone, &temp.genre, &temp.date_nais_jour, &temp.date_nais_mois, &temp.date_nais_annee, &temp.date_deb_jour, &temp.date_deb_mois, &temp.date_deb_annee, &temp.statut) != EOF)
		{
			e.id = temp.id + 1;
		}
		fprintf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, e.genre, e.date_nais_jour, e.date_nais_mois, e.date_nais_annee, e.date_deb_jour, e.date_deb_mois, e.date_deb_annee, e.statut);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier_entraineur(char *filename, int id, entraineur nouv)
{
	int tr=0;
	entraineur e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", &e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, &e.genre, &e.date_nais_jour, &e.date_nais_mois, &e.date_nais_annee, &e.date_deb_jour, &e.date_deb_mois, &e.date_deb_annee, &e.statut) != EOF)
		{
			if(e.id == id)
			{
				fprintf(f2, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", nouv.id, nouv.nom, nouv.prenom, nouv.adresse_postal, nouv.adresse_mail, nouv.telephone, nouv.genre, nouv.date_nais_jour, nouv.date_nais_mois, nouv.date_nais_annee, nouv.date_deb_jour, nouv.date_deb_mois, nouv.date_deb_annee, nouv.statut);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n",e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, e.genre, e.date_nais_jour, e.date_nais_mois, e.date_nais_annee, e.date_deb_jour, e.date_deb_mois, e.date_deb_annee, e.statut);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

int supprimer_entraineur(char *filename, int id)
{
	int tr = 0;
	entraineur e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", &e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, &e.genre, &e.date_nais_jour, &e.date_nais_mois, &e.date_nais_annee, &e.date_deb_jour, &e.date_deb_mois, &e.date_deb_annee, &e.statut) != EOF)
		{
			if(e.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, e.genre, e.date_nais_jour, e.date_nais_mois, e.date_nais_annee, e.date_deb_jour, e.date_deb_mois, e.date_deb_annee, e.statut);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

entraineur chercher_entraineur(char *filename, int id)
{
	entraineur e;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", &e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, &e.genre, &e.date_nais_jour, &e.date_nais_mois, &e.date_nais_annee, &e.date_deb_jour, &e.date_deb_mois, &e.date_deb_annee, &e.statut) != EOF)
		{
			if(e.id == id)
			{
				tr = 1;
			}
		}
		fclose(f);
	}
	if(tr == 0)
		e.id = -1;
	return e;
}

int inscription_entraineur(char *filename, int centre_id, int entraineur_id)
{
	FILE *f = fopen(filename, "a");
	if(f != NULL)
	{
		fprintf(f, "%d %d\n", entraineur_id, entraineur_id);
		fclose(f);
		return 1;
	}
	return 0;
}



void afficher_entraineur(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	entraineur e;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse_postal", renderer, "text", ADRESSE_POSTAL_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse_mail", renderer, "text", ADRESSE_MAIL_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("telephone", renderer, "text", TELEPHONE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("genre", renderer, "text", GENRE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_jour", renderer, "text", DATE_NAIS_JOUR_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_mois", renderer, "text", DATE_NAIS_MOIS_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_annee", renderer, "text", DATE_NAIS_ANNEE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_jour", renderer, "text", DATE_DEB_JOUR_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_mois", renderer, "text", DATE_DEB_MOIS_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_annee", renderer, "text", DATE_DEB_ANNEE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("statut", renderer, "text", STATUT_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


	}
	store = gtk_list_store_new(COLUMNS_ENTRAINEUR, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("entraineur.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("entraineur.txt", "a+");
		while(fscanf(f, "%d %s %s %s %s %s %d %d %d %d %d %d %d %d\n", &e.id, e.nom, e.prenom, e.adresse_postal, e.adresse_mail, e.telephone, &e.genre, &e.date_nais_jour, &e.date_nais_mois, &e.date_nais_annee, &e.date_deb_jour, &e.date_deb_mois, &e.date_deb_annee, &e.statut) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID_ENTRAINEUR, e.id, NOM_ENTRAINEUR, e.nom, PRENOM_ENTRAINEUR, e.prenom, ADRESSE_POSTAL_ENTRAINEUR, e.adresse_postal, ADRESSE_MAIL_ENTRAINEUR, e.adresse_mail, TELEPHONE_ENTRAINEUR, e.telephone, GENRE_ENTRAINEUR, e.genre, DATE_NAIS_JOUR_ENTRAINEUR, e.date_nais_jour, DATE_NAIS_MOIS_ENTRAINEUR, e.date_nais_mois, DATE_NAIS_ANNEE_ENTRAINEUR, e.date_nais_annee, DATE_DEB_JOUR_ENTRAINEUR, e.date_deb_jour, DATE_DEB_MOIS_ENTRAINEUR, e.date_deb_mois, DATE_DEB_ANNEE_ENTRAINEUR, e.date_deb_annee, STATUT_ENTRAINEUR, e.statut, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

void vider_entraineur(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	entraineur e;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse_postal", renderer, "text", ADRESSE_POSTAL_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse_mail", renderer, "text", ADRESSE_MAIL_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("telephone", renderer, "text", TELEPHONE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("genre", renderer, "text", GENRE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_jour", renderer, "text", DATE_NAIS_JOUR_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_mois", renderer, "text", DATE_NAIS_MOIS_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_nais_annee", renderer, "text", DATE_NAIS_ANNEE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_jour", renderer, "text", DATE_DEB_JOUR_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_mois", renderer, "text", DATE_DEB_MOIS_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_deb_annee", renderer, "text", DATE_DEB_ANNEE_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("statut", renderer, "text", STATUT_ENTRAINEUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS_ENTRAINEUR, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);
}

