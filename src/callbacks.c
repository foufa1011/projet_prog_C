#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "equipement.h"


int etat = 1;

//enregister ajout
void
on_in_gestion_equipement_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	equipement e;
	e.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_nomequipement_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *categorie_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_categorie_comboboxentry");
	strcpy(e.categorie,gtk_combo_box_get_active_text(GTK_COMBO_BOX(categorie_input)));

	GtkWidget *quantite = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_qtdispo_spinbutton");
	e.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(quantite));

	int year, month, day;

	GtkWidget *calendar = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_dateachat_calendar");

	gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);

	e.etat = etat;
	etat = 1;

	char *fichier = "equipement.txt";
	int result = ajouter(fichier,e);

}


void
on_in_gestion_equipement_ajouter_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 3;
}


void
on_in_gestion_equipement_ajouter_enpanne_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 2;
}


void
on_in_gestion_equipement_ajouter_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 1;
}

int id = 0;

//retrouver information pour modifier
void
on_in_gestion_equipement_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "equipement.txt";
	equipement e = chercher(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_nomequipement_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), e.nom);

        GtkWidget *categorie_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_categorie_comboboxentry");
	char *fichier2 = "categorie.txt";
	FILE *f = fopen(fichier2, "r");
	char categorie[100];
	int i = 0;
	if(f!=NULL)
	{
		while(fscanf(f, "%s\n", categorie) != EOF)
		{
			if(strcmp(categorie, e.categorie) == 0)
				break;
			i++;
		}
		fclose(f);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(categorie_input), i);

	GtkWidget *quantite_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_qtdispo_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(quantite_input), e.quantite);

	GtkWidget *etat_disponible_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_disponible_radiobutton");
	if(e.etat == 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_disponible_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_disponible_input), FALSE);

	GtkWidget *etat_enpanne_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_enpanne_radiobutton");
	if(e.etat == 2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_enpanne_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_enpanne_input), FALSE);

	GtkWidget *etat_enmaintenance_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_enmaintenance_radiobutton");
	if(e.etat == 3)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_enmaintenance_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(etat_enmaintenance_input), FALSE);

}


//enregistrer modifier
void
on_in_gestion_equipement_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	equipement e;
	e.id = id;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_nomequipement_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *categorie_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_categorie_comboboxentry");
	strcpy(e.categorie,gtk_combo_box_get_active_text(GTK_COMBO_BOX(categorie_input)));

	GtkWidget *quantite = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_qtdispo_spinbutton");
	e.quantite = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(quantite));

	e.etat = etat;
	etat = 1;

	char *fichier = "equipement.txt";
	int result = modifier(fichier, e.id, e);
}


void
on_in_gestion_equipement_modifier_enpanne_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 2;
}


void
on_radiobutton84_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_in_gestion_equipement_modifier_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 1;
}


//supprimer
void
on_in_gestion_equipement_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "in_gestion_equipement_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "equipement.txt";
	supprimer(fichier, id_supp);
}


void
on_in_gestion_equipement_modifier_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 3;
}


//actualiser tree view
void
on_in_gestion_equipement_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_liste_treeview");
	afficher(tree_input);
}


//supprimer d'apres le tree view
void
on_in_gestion_equipement_ajouter_liste_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	equipement e;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID, &e.id, NOM, e.nom, CATEGORIE, e.categorie, ANNEE_ACHAT, &e.annee_achat, MOIS_ACHAT, &e.mois_achat, JOUR_ACHAT, &e.jour_achat, ETAT, &e.etat, QUANTITE, &e.quantite, -1);
		char *fichier = "equipement.txt";		
		supprimer(fichier, e.id);
		afficher(GTK_WIDGET(treeview));
	}
}

