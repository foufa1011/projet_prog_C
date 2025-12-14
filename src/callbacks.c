#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"


int type = 1;
int activites[] = {0, 0};

void
on_nl_gestion_centre_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	centre c;
	c.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_nomcentre_entry");
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *ville_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_localisation_comboboxentry");
	strcpy(c.ville,gtk_combo_box_get_active_text(GTK_COMBO_BOX(ville_input)));

	GtkWidget *horaire_ouverture_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_ouverture_spinbutton");
	c.horaire_ouverture = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(horaire_ouverture_input));

	GtkWidget *horaire_fermeture_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_fermeture_button");
	c.horaire_fermeture = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(horaire_fermeture_input));

	GtkWidget *membre_limit_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_nblimite_spinbutton");
	c.membre_limit = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(membre_limit_input));

	c.type = type;
	c.activites = activites[0] + activites[1];
	type = 1;
	activites[0] = 0;
	activites[1] = 0;

	char *fichier = "centre.txt";
	int result = ajouter(fichier,c);
}


void
on_nl_gestion_centre_ajouter_community_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type = 1;
}


void
on_nl_gestion_centre_ajouter_training_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type = 2;
}


void
on_nl_gestion_centre_ajouter_entrainement_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		activites[0] = 1;
	}
	else
		activites[0] = 0;
}


void
on_nl_gestion_centre_ajouter_defoulement_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		activites[1] = 2;
	}
	else
		activites[1] = 0;
}

int id = 0;

void
on_nl_gestion_centre_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "centre.txt";
	centre c = chercher(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_nomcentre_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), c.nom);

        GtkWidget *ville_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_ville_comboboxentry");
	char *fichier2 = "villes.txt";
	FILE *f = fopen(fichier2, "r");
	char ville[100];
	int i = 0;
	if(f!=NULL)
	{
		while(fscanf(f, "%s\n", ville) != EOF)
		{
			if(strcmp(ville, c.ville) == 0)
				break;
			i++;
		}
		fclose(f);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(ville_input), i);

	GtkWidget *horaire_ouverture_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_horaire_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(horaire_ouverture_input), c.horaire_ouverture);

	GtkWidget *horaire_fermeture_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_fermeture_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(horaire_fermeture_input), c.horaire_fermeture);

	GtkWidget *membre_limit_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_nblimite_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(membre_limit_input), c.membre_limit);

	GtkWidget *type_community_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_community_radiobutton");
	if(c.type == 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_community_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_community_input), FALSE);

	GtkWidget *type_training_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_training_radiobutton");
	if(c.type == 2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_training_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_training_input), FALSE);

	GtkWidget *activites_entrainement_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_entrainement_checkbutton");
	GtkWidget *activites_defoulement_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_defoulement_checkbutton");
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(activites_entrainement_input), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(activites_defoulement_input), FALSE);	
	if(c.activites & 1)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(activites_entrainement_input), TRUE);
	}
	c.activites = c.activites >> 1;
		
	if(c.activites & 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(activites_defoulement_input), TRUE);

	
}


void
on_button144_clicked                   (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	centre c;
	c.id = id;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_nomcentre_entry");
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *ville_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_ville_comboboxentry");
	strcpy(c.ville,gtk_combo_box_get_active_text(GTK_COMBO_BOX(ville_input)));

	GtkWidget *horaire_ouverture_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_horaire_spinbutton");
	c.horaire_ouverture = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(horaire_ouverture_input));

	GtkWidget *horaire_fermeture_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_fermeture_spinbutton");
	c.horaire_fermeture = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(horaire_fermeture_input));

	GtkWidget *membre_limit_input = lookup_widget(objet_graphique, "nl_gestion_centre_modifier_nblimite_spinbutton");
	c.membre_limit = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(membre_limit_input));

	c.type = type;
	c.activites = activites[0] + activites[1];
	type = 1;
	activites[0] = 0;
	activites[1] = 0;

	char *fichier = "centre.txt";
	int result = modifier(fichier, c.id, c);
}


void
on_nl_gestion_centre_modifier_community_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type = 1;
}


void
on_nl_gestion_centre_modifier_training_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type = 2;
}


void
on_nl_gestion_centre_modifier_entrainement_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		activites[0] = 1;
	}
	else
		activites[0] = 0;
}


void
on_nl_gestion_centre_modifier_defoulement_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		activites[1] = 2;
	}
	else
		activites[1] = 0;
}


void
on_nl_gestion_centre_supprimer_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	
}


void
on_nl_gestion_centre_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "nl_gestion_centre_supprimer_rechercher_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "centre.txt";
	supprimer(fichier, id_supp);
}


void
on_nl_gestion_centre_supprimer_annuler_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{

}


void
on_nl_gestion_centre_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "nl_gestion_centre_ajouter_liste_treeview");
	afficher(tree_input);
}


void
on_nl_gestion_centre_ajouter_liste_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	centre c;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID, &c.id, NOM, c.nom, VILLE, c.ville, HORAIRE_OUVERTURE, &c.horaire_ouverture, HORAIRE_FERMETURE, &c.horaire_fermeture, MEMBRE_LIMIT, &c.membre_limit, TYPE, &c.type, ACTIVITES, &c.activites, -1);
		char *fichier = "centre.txt";		
		supprimer(fichier, c.id);
		afficher(GTK_WIDGET(treeview));
	}
}

