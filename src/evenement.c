#include "evenement.h"
#include <stdio.h>
int ajouter_evenement(char *filename, evenement e)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		evenement temp;
		while(fscanf(f, "%d %s %d %d %d %d %d %d\n", &temp.id, temp.nom, &temp.type, &temp.date_jour, &temp.date_mois, &temp.date_annee, &temp.date_heure, &temp.date_minute) != EOF)
		{
			e.id = temp.id + 1;
		}
		fprintf(f, "%d %s %d %d %d %d %d %d\n", e.id, e.nom, e.type, e.date_jour, e.date_mois, e.date_annee, e.date_heure, e.date_minute);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier_evenement(char *filename, int id, evenement nouv)
{
	int tr=0;
	evenement e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %d %d %d %d %d %d\n", &e.id, e.nom, &e.type, &e.date_jour, &e.date_mois, &e.date_annee, &e.date_heure, &e.date_minute) != EOF)
		{
			if(e.id == id)
			{
				fprintf(f2, "%d %s %d %d %d %d %d %d\n", nouv.id, nouv.nom, nouv.type, nouv.date_jour,
					nouv.date_mois, nouv.date_annee, nouv.date_heure, nouv.date_minute);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %d %d %d %d %d %d\n", e.id, e.nom, e.type, e.date_jour, e.date_mois, e.date_annee, e.date_heure, e.date_minute);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

int supprimer_evenement(char *filename, int id)
{
	int tr = 0;
	evenement e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %d %d %d %d %d %d\n", &e.id, e.nom, &e.type, &e.date_jour, &e.date_mois, &e.date_annee, &e.date_heure, &e.date_minute) != EOF)
		{
			if(e.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %d %d %d %d %d %d\n", e.id, e.nom, e.type, e.date_jour, e.date_mois, e.date_annee, e.date_heure, e.date_minute);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

evenement chercher_evenement(char *filename, int id)
{
	evenement e;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %d %d %d %d %d %d\n", &e.id, e.nom, &e.type, &e.date_jour, &e.date_mois, &e.date_annee, &e.date_heure, &e.date_minute) != EOF)
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



void afficher_evenement(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	evenement e;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", TYPE_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_jour", renderer, "text", DATE_JOUR_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_mois", renderer, "text", DATE_MOIS_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_annee", renderer, "text", DATE_ANNEE_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_heure", renderer, "text", DATE_HEURE_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("date_minute", renderer, "text", DATE_MINUTE_EVENEMENT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS_EVENEMENT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("evenement.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("evenement.txt", "a+");
		while(fscanf(f, "%d %s %d %d %d %d %d %d\n", &e.id, e.nom, &e.type, &e.date_jour, &e.date_mois, &e.date_annee, &e.date_heure, &e.date_minute) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID_EVENEMENT, e.id, NOM_EVENEMENT, e.nom, TYPE_EVENEMENT, e.type, DATE_JOUR_EVENEMENT, e.date_jour, DATE_MOIS_EVENEMENT, e.date_mois, DATE_ANNEE_EVENEMENT, e.date_annee, DATE_HEURE_EVENEMENT, e.date_heure, DATE_MINUTE_EVENEMENT, e.date_minute, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

