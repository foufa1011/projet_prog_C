#include "membre.h"
#include <stdio.h>
int ajouter_membre(char *filename, membre m)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		membre temp;
		while(fscanf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", &temp.id, temp.nom, temp.prenom, temp.email, temp.telephone, temp.adresse, temp.ville, &temp.genre, &temp.date_jour, &temp.date_mois, &temp.date_annee, temp.code_postal, &temp.poids, &temp.taille) != EOF)
		{
			m.id = temp.id + 1;
		}
		fprintf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, m.genre, m.date_jour, m.date_mois, m.date_annee, m.code_postal, m.poids, m.taille);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier_membre(char *filename, int id, membre nouv)
{
	int tr=0;
	membre m;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", &m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, &m.genre, &m.date_jour, &m.date_mois, &m.date_annee, m.code_postal, &m.poids, &m.taille) != EOF)
		{
			if(m.id == id)
			{
				fprintf(f2, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", nouv.id, nouv.nom, nouv.prenom, nouv.email, nouv.telephone, nouv.adresse, nouv.ville, nouv.genre, nouv.date_jour, nouv.date_mois, nouv.date_annee, nouv.code_postal, nouv.poids, nouv.taille);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, m.genre, m.date_jour, m.date_mois, m.date_annee, m.code_postal, m.poids, m.taille);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

int supprimer_membre(char *filename, int id)
{
	int tr = 0;
	membre m;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", &m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, &m.genre, &m.date_jour, &m.date_mois, &m.date_annee, m.code_postal, &m.poids, &m.taille) != EOF)
		{
			if(m.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, m.genre, m.date_jour, m.date_mois, m.date_annee, m.code_postal, m.poids, m.taille);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

membre chercher_membre(char *filename, int id)
{
	membre m;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", &m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, &m.genre, &m.date_jour, &m.date_mois, &m.date_annee, m.code_postal, &m.poids, &m.taille) != EOF)
		{
			if(m.id == id)
			{
				tr = 1;
			}
		}
		fclose(f);
	}
	if(tr == 0)
		m.id = -1;
	return m;
}

int inscription_membre(char *filename, int membre_id, int entraineur_id)
{
	FILE *f = fopen(filename, "a");
	if(f != NULL)
	{
		fprintf(f, "%d %d\n", membre_id, entraineur_id);
		fclose(f);
		return 1;
	}
	return 0;
}



void afficher_membre(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	membre m;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("email", renderer, "text", EMAIL_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("telephone", renderer, "text", TELEPHONE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text", ADRESSE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", VILLE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("genre", renderer, "text", GENRE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_jour", renderer, "text", DATE_JOUR_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_mois", renderer, "text", DATE_MOIS_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_annee", renderer, "text", DATE_ANNEE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("code_postal", renderer, "text", CODE_POSTAL_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("poids", renderer, "text", POIDS_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("taille", renderer, "text", TAILLE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);


	}
	store = gtk_list_store_new(COLUMNS_MEMBRE, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("membre.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("membre.txt", "a+");
		while(fscanf(f, "%d %s %s %s %s %s %s %d %d %d %d %s %d %d\n", &m.id, m.nom, m.prenom, m.email, m.telephone, m.adresse, m.ville, &m.genre, &m.date_jour, &m.date_mois, &m.date_annee, m.code_postal, &m.poids, &m.taille) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID_MEMBRE, m.id, NOM_MEMBRE, m.nom, PRENOM_MEMBRE, m.prenom, EMAIL_MEMBRE, m.email, TELEPHONE_MEMBRE, m.telephone, ADRESSE_MEMBRE, m.adresse, VILLE_MEMBRE, m.ville, GENRE_MEMBRE, m.genre, DATE_JOUR_MEMBRE, m.date_jour, DATE_MOIS_MEMBRE, m.date_mois, DATE_ANNEE_MEMBRE, m.date_annee, CODE_POSTAL_MEMBRE, m.code_postal, POIDS_MEMBRE, m.poids, TAILLE_MEMBRE, m.taille, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

void vider_membre(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	membre m;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text", PRENOM_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("email", renderer, "text", EMAIL_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("telephone", renderer, "text", TELEPHONE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text", ADRESSE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", VILLE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("genre", renderer, "text", GENRE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_jour", renderer, "text", DATE_JOUR_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_mois", renderer, "text", DATE_MOIS_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_annee", renderer, "text", DATE_ANNEE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("code_postal", renderer, "text", CODE_POSTAL_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("poids", renderer, "text", POIDS_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("taille", renderer, "text", TAILLE_MEMBRE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS_MEMBRE, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);
}

