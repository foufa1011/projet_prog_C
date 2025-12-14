#include "centre.h"
#include <stdio.h>
int ajouter(char *filename, centre c)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		centre temp;
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &temp.id, temp.nom, temp.ville, &temp.horaire_ouverture,
			     &temp.horaire_fermeture, &temp.membre_limit, &temp.type, &temp.activites) != EOF)
		{
			c.id = temp.id + 1;
		}
		fprintf(f, "%d %s %s %d %d %d %d %d\n", c.id, c.nom, c.ville, c.horaire_ouverture,
			c.horaire_fermeture, c.membre_limit, c.type, c.activites);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier(char *filename, int id, centre nouv)
{
	int tr=0;
	centre c;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &c.id, c.nom, c.ville, &c.horaire_ouverture,
			     &c.horaire_fermeture, &c.membre_limit, &c.type, &c.activites) != EOF)
		{
			if(c.id == id)
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", nouv.id, nouv.nom, nouv.ville, nouv.horaire_ouverture,
					nouv.horaire_fermeture, nouv.membre_limit, nouv.type, nouv.activites);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", c.id, c.nom, c.ville, c.horaire_ouverture,
					c.horaire_fermeture, c.membre_limit, c.type, c.activites);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

int supprimer(char *filename, int id)
{
	int tr = 0;
	centre c;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &c.id, c.nom, c.ville, &c.horaire_ouverture,
		      &c.horaire_fermeture, &c.membre_limit, &c.type, &c.activites) != EOF)
		{
			if(c.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", c.id, c.nom, c.ville, c.horaire_ouverture,
					c.horaire_fermeture, c.membre_limit, c.type, c.activites);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

centre chercher(char *filename, int id)
{
	centre c;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %s %d %d %d %d %d\n", &c.id, c.nom, c.ville, &c.horaire_ouverture,
					&c.horaire_fermeture, &c.membre_limit, &c.type, &c.activites) != EOF)
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

int inscription(char *filename, int centre_id, int entraineur_id)
{
	FILE *f = fopen(filename, "a");
	if(f != NULL)
	{
		fprintf(f, "%d %d\n", centre_id, entraineur_id);
		fclose(f);
		return 1;
	}
	return 0;
}



void afficher(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	centre c;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", VILLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("horaire_ouverture", renderer, "text", HORAIRE_OUVERTURE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("horaire_fermeture", renderer, "text", HORAIRE_FERMETURE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("membre_limit", renderer, "text", MEMBRE_LIMIT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", TYPE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("activites", renderer, "text", ACTIVITES, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("centre.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("centre.txt", "a+");
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &c.id, c.nom, c.ville, &c.horaire_ouverture,
		     &c.horaire_fermeture, &c.membre_limit, &c.type, &c.activites) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID, c.id, NOM, c.nom, VILLE, c.ville, HORAIRE_OUVERTURE, c.horaire_ouverture, HORAIRE_FERMETURE, c.horaire_fermeture, MEMBRE_LIMIT, c.membre_limit, TYPE, c.type, ACTIVITES, c.activites, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

void vider(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	centre c;

	FILE *f;
	store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));
	if(store == NULL)
	{
		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("id", renderer, "text", ID, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text", NOM, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("ville", renderer, "text", VILLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("horaire_ouverture", renderer, "text", HORAIRE_OUVERTURE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("horaire_fermeture", renderer, "text", HORAIRE_FERMETURE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("membre_limit", renderer, "text", MEMBRE_LIMIT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("type", renderer, "text", TYPE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("activites", renderer, "text", ACTIVITES, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
	g_object_unref(store);
}

