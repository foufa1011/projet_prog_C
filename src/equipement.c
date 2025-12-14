#include "equipement.h"
#include <stdio.h>
int ajouter(char *filename, equipement e)
{
	FILE *f = fopen(filename, "a+");
	if(f!=NULL)
	{
		equipement temp;
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &temp.id, temp.nom, temp.categorie, &temp.annee_achat	,
			     &temp.mois_achat, &temp.jour_achat, &temp.etat, &temp.quantite) != EOF)
		{
			e.id = temp.id + 1;
		}
		fprintf(f, "%d %s %s %d %d %d %d %d\n", e.id, e.nom, e.categorie, e.annee_achat,
			e.mois_achat, e.jour_achat, e.etat, e.quantite);
		fclose(f);
		return 1;
	}
	return 0;
}
int modifier(char *filename, int id, equipement nouv)
{
	int tr=0;
	equipement e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");
	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &e.id, e.nom, e.categorie, &e.annee_achat,
			     &e.mois_achat, &e.jour_achat, &e.etat, &e.quantite) != EOF)
		{
			if(e.id == id)
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", nouv.id, nouv.nom, nouv.categorie, nouv.annee_achat,
					nouv.mois_achat, nouv.jour_achat, nouv.etat, nouv.quantite);
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", e.id, e.nom, e.categorie, e.annee_achat,
					e.mois_achat, e.jour_achat, e.etat, e.quantite);
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
	equipement e;
	FILE *f = fopen(filename, "r");
	FILE *f2 = fopen("temp.txt", "w");

	if(f != NULL && f2 != NULL)
	{
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &e.id, e.nom, e.categorie, &e.annee_achat,
			     &e.mois_achat, &e.jour_achat, &e.etat, &e.quantite) != EOF)
		{
			if(e.id == id)
			{
				tr = 1;
			} else
			{
				fprintf(f2, "%d %s %s %d %d %d %d %d\n", e.id, e.nom, e.categorie, e.annee_achat,
					e.mois_achat, e.jour_achat, e.etat, e.quantite);
			}
		}
		fclose(f);
		fclose(f2);
		remove(filename);
		rename("temp.txt", filename);
	}
	return tr;
}

equipement chercher(char *filename, int id)
{
	equipement e;
	int tr = 0;
	FILE *f = fopen(filename, "r");

	if(f != NULL)
	{
		while(tr == 0 && fscanf(f, "%d %s %s %d %d %d %d %d\n", &e.id, e.nom, e.categorie, &e.annee_achat,
			     &e.mois_achat, &e.jour_achat, &e.etat, &e.quantite) != EOF)
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



void afficher(GtkWidget *liste)
{
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;

	equipement e;

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
		column = gtk_tree_view_column_new_with_attributes("categorie", renderer, "text", CATEGORIE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("annee_achat", renderer, "text", ANNEE_ACHAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("mois_achat", renderer, "text", MOIS_ACHAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("jour_achat", renderer, "text", JOUR_ACHAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("etat", renderer, "text", ETAT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

		renderer = gtk_cell_renderer_text_new();
		column = gtk_tree_view_column_new_with_attributes("quantite", renderer, "text", QUANTITE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

	}
	store = gtk_list_store_new(COLUMNS, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);
		
	f = fopen("equipement.txt", "r");

	if(f == NULL)
	{
		return;
	}
	else
	{
		f = fopen("equipement.txt", "a+");
		while(fscanf(f, "%d %s %s %d %d %d %d %d\n", &e.id, e.nom, e.categorie, &e.annee_achat,
			     &e.mois_achat, &e.jour_achat, &e.etat, &e.quantite) != EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, ID, e.id, NOM, e.nom, CATEGORIE, e.categorie, ANNEE_ACHAT, e.annee_achat, MOIS_ACHAT, e.mois_achat, JOUR_ACHAT, e.jour_achat, ETAT, e.etat, QUANTITE, e.quantite, -1);
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

