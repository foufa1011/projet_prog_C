#include "cours.h"
#include <stdio.h>
int ajouter_cours(char *filename, cours c)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		cours temp;
		while(fscanf(f, "%d %s %s %d %d %d %d %d %d\n", &temp.id, temp.nom, temp.type, &temp.date_heure	,
			     &temp.date_minute, &temp.date_jour, &temp.date_mois, &temp.date_annee, &temp.duree) != EOF)
		{
			c.id = temp.id + 1;
		}
		fprintf(f, "%d %s %s %d %d %d %d %d %d\n", c.id, c.nom, c.type, c.date_heure,
			c.date_minute, c.date_jour, c.date_mois, c.date_annee, c.duree);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier_cours(char *filename, int id, cours nouv)
{
	int tr=0;
	cours c;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d %d\n", &c.id, c.nom, c.type, &c.date_heure,
			     &c.date_minute, &c.date_jour, &c.date_mois, &c.date_annee, &c.duree) != EOF)
		{
			if(c.id == id)
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d %d\n", nouv.id, nouv.nom, nouv.type, nouv.date_heure,
					nouv.date_minute, nouv.date_jour, nouv.date_mois, nouv.date_annee, nouv.duree);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d %d\n", c.id, c.nom, c.type, c.date_heure,
			c.date_minute, c.date_jour, c.date_mois, c.date_annee, c.duree);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

int supprimer_cours(char *filename, int id)
{
	int tr = 0;
	cours c;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d %d\n", &c.id, c.nom, c.type, &c.date_heure,
			     &c.date_minute, &c.date_jour, &c.date_mois, &c.date_annee, &c.duree) != EOF)
		{
			if(c.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d %d\n", c.id, c.nom, c.type, c.date_heure,
			c.date_minute, c.date_jour, c.date_mois, c.date_annee, c.duree);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

cours chercher_cours(char *filename, int id)
{
	cours c;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %s %d %d %d %d %d %d\n", &c.id, c.nom, c.type, &c.date_heure,
			     &c.date_minute, &c.date_jour, &c.date_mois, &c.date_annee, &c.duree) != EOF)
		{
			if(c.id == id)
			{
				tr = 1;
			}
		}
		fclose(f);
	}
	if(tr == 0)
		c.id = -1;
	return c;
}



void afficher_cours(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	cours c;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", TYPE_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_heure", renderer, "text", DATE_HEURE_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_minute", renderer, "text", DATE_MINUTE_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_jour", renderer, "text", DATE_JOUR_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_mois", renderer, "text", DATE_MOIS_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_annee", renderer, "text", DATE_ANNEE_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
		
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("duree", renderer, "text", DUREE_COURS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS_COURS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("cours.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("cours.txt", "a+");
		while(fscanf(f, "%d %s %s %d %d %d %d %d %d\n", &c.id, c.nom, c.type, &c.date_heure,
			     &c.date_minute, &c.date_jour, &c.date_mois, &c.date_annee, &c.duree) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID_COURS, c.id, NOM_COURS, c.nom, TYPE_COURS, c.type, DATE_HEURE_COURS, c.date_heure, DATE_MINUTE_COURS, c.date_minute, DATE_JOUR_COURS, c.date_jour, DATE_MOIS_COURS, c.date_mois, DATE_ANNEE_COURS, c.date_annee, DUREE_COURS, c.duree, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

