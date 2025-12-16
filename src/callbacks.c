#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "centre.h"
#include "equipement.h"
#include "membre.h"
#include "entraineur.h"
#include "evenement.h"
#include "cours.h"


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
	int result = ajouter_centre(fichier,c);
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
	centre c = chercher_centre(fichier, id);
	
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
	int result = modifier_centre(fichier, c.id, c);
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
	supprimer_centre(fichier, id_supp);
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
	afficher_centre(tree_input);
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
		gtk_tree_model_get(model, &iter, ID_CENTRE, &c.id, NOM_CENTRE, c.nom, VILLE, c.ville, HORAIRE_OUVERTURE, &c.horaire_ouverture, HORAIRE_FERMETURE, &c.horaire_fermeture, MEMBRE_LIMIT, &c.membre_limit, TYPE, &c.type, ACTIVITES, &c.activites, -1);
		char *fichier = "centre.txt";		
		supprimer_centre(fichier, c.id);
		afficher_centre(GTK_WIDGET(treeview));
	}
}

int etat = 1;

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
		gtk_tree_model_get(model, &iter, ID_EQUIPEMENT, &e.id, NOM_EQUIPEMENT, e.nom, CATEGORIE, e.categorie, ANNEE_ACHAT, &e.annee_achat, MOIS_ACHAT, &e.mois_achat, JOUR_ACHAT, &e.jour_achat, ETAT, &e.etat, QUANTITE, &e.quantite, -1);
		char *fichier = "equipement.txt";		
		supprimer_equipement(fichier, e.id);
		afficher_equipement(GTK_WIDGET(treeview));
	}
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
on_in_gestion_equipement_ajouter_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 3;
}


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

	GtkWidget *jour_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_dateachat_jour_spinbutton");
	e.jour_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour_input));

	GtkWidget *mois_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_dateachat_mois_spinbutton");
	e.mois_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_input));

	GtkWidget *annee_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_dateachat_annee_spinbutton");
	e.annee_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_input));

	e.etat = etat;
	etat = 1;

	char *fichier = "equipement.txt";
	int result = ajouter_equipement(fichier,e);

}


//actualiser tree view
void
on_in_gestion_equipement_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "in_gestion_equipement_ajouter_liste_treeview");
	afficher_equipement(tree_input);
}


void
on_in_gestion_equipement_ajouter_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 1;
}


//retrouver information pour modifier
void
on_in_gestion_equipement_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "equipement.txt";
	equipement e = chercher_equipement(fichier, id);
	
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

	GtkWidget *jour_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(jour_input), e.jour_achat);

	GtkWidget *mois_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_mois_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(mois_input), e.mois_achat);

	GtkWidget *annee_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(annee_input), e.annee_achat);

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

	GtkWidget *jour_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_jour_spinbutton");
	e.jour_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour_input));

	GtkWidget *mois_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_mois_spinbutton");
	e.mois_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_input));

	GtkWidget *annee_input = lookup_widget(objet_graphique, "in_gestion_equipement_modifier_dateachat_annee_spinbutton");
	e.annee_achat = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_input));

	e.etat = etat;
	etat = 1;

	char *fichier = "equipement.txt";
	int result = modifier_equipement(fichier, e.id, e);
}


void
on_in_gestion_equipement_modifier_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 1;
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


//supprimer
void
on_in_gestion_equipement_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "in_gestion_equipement_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "equipement.txt";
	supprimer_equipement(fichier, id_supp);
}


void
on_in_gestion_equipement_modifier_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 3;
}

int genre = 1;

void
on_mbm_gestion_membre_Ajouter_liste_TreeView_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	membre m;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID_MEMBRE, &m.id, NOM_MEMBRE, m.nom, PRENOM_MEMBRE, m.prenom, EMAIL_MEMBRE, m.email, TELEPHONE_MEMBRE, m.telephone, ADRESSE_MEMBRE, m.adresse, VILLE_MEMBRE, m.ville, GENRE_MEMBRE, &m.genre, DATE_JOUR_MEMBRE, &m.date_jour, DATE_MOIS_MEMBRE, &m.date_mois, DATE_ANNEE_MEMBRE, &m.date_annee, CODE_POSTAL_MEMBRE, m.code_postal, POIDS_MEMBRE, &m.poids, TAILLE_MEMBRE, &m.taille, -1);
		char *fichier = "membre.txt";		
		supprimer_membre(fichier, m.id);
		afficher_membre(GTK_WIDGET(treeview));
	}
}


void
on_mbm_gestion_membre_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_liste_TreeView");
	afficher_membre(tree_input);
}

void
on_mbm_gestion_membre_Ajouter_enregistrer_Button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	membre m;
	m.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_nom_entry");
	strcpy(m.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Prenom_entry");
	strcpy(m.prenom,gtk_entry_get_text(GTK_ENTRY(prenom_input)));

	GtkWidget *email_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Email_entry");
	strcpy(m.email,gtk_entry_get_text(GTK_ENTRY(email_input)));

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Telephone_entry");
	strcpy(m.telephone,gtk_entry_get_text(GTK_ENTRY(telephone_input)));

	GtkWidget *adresse_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Adresse_entry");
	strcpy(m.adresse,gtk_entry_get_text(GTK_ENTRY(adresse_input)));

	GtkWidget *ville_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Ville_entry");
	strcpy(m.ville,gtk_entry_get_text(GTK_ENTRY(ville_input)));

	GtkWidget *date_jour_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_dnd_jour_spinbutton");
	m.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour_input));

	GtkWidget *date_mois_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_dnd_mois_spinbutton");
	m.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois_input));

	GtkWidget *date_annee_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_dnd_annee_spinbutton");
	m.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee_input));

	GtkWidget *poids_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_poids_SpinButton");
	m.poids = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(poids_input));

	GtkWidget *taille_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_taille_SpinButton");
	m.taille = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(taille_input));

	GtkWidget *code_postal_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Ajouter_Codepostal_entry");
	strcpy(m.code_postal, gtk_entry_get_text(GTK_ENTRY(code_postal_input)));

	m.genre = genre;

	char *fichier = "membre.txt";
	int result = ajouter_membre(fichier,m);
}


void
on_mbm_gestion_membre_Ajouter_femme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 1;
}


void
on_mbm_gestion_membre_Ajouter_Homme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 2;
}


void
on_mbm_gestion_membre_Modifier_femme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 1;
}


void
on_mbm_gestion_membre_Modifier_homme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 2;
}


void
on_mbm_gestion_membre_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "membre.txt";
	membre m = chercher_membre(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_nom_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), m.nom);

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_prenom_entry");
	gtk_entry_set_text(GTK_ENTRY(prenom_input), m.prenom);

	GtkWidget *email_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_email_entry");
	gtk_entry_set_text(GTK_ENTRY(email_input), m.email);

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_telephone_entry");
	gtk_entry_set_text(GTK_ENTRY(telephone_input), m.telephone);

	GtkWidget *adresse_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_adresse_entry");
	gtk_entry_set_text(GTK_ENTRY(adresse_input), m.adresse);

	GtkWidget *ville_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_ville_entry");
	gtk_entry_set_text(GTK_ENTRY(ville_input), m.ville);

	GtkWidget *code_postal_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_codepostal_entry");
	gtk_entry_set_text(GTK_ENTRY(code_postal_input), m.code_postal);

	GtkWidget *date_jour_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_jour_input), m.date_jour);

	GtkWidget *date_mois_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_mois_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_mois_input), m.date_mois);

	GtkWidget *date_annee_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_annee_input), m.date_annee);

	GtkWidget *poids_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_poids_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(poids_input), m.poids);

	GtkWidget *taille_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_taille_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(taille_input), m.taille);

	GtkWidget *genre_femme_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_femme_radiobutton");
	if(m.genre == 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_femme_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_femme_input), FALSE);

	GtkWidget *genre_homme_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_homme_radiobutton");
	if(m.genre == 2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_homme_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_homme_input), FALSE);
}


void
on_mbm_gestion_membre_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	membre m;
	m.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_nom_entry");
	strcpy(m.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_prenom_entry");
	strcpy(m.prenom,gtk_entry_get_text(GTK_ENTRY(prenom_input)));

	GtkWidget *email_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_email_entry");
	strcpy(m.email,gtk_entry_get_text(GTK_ENTRY(email_input)));

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_telephone_entry");
	strcpy(m.telephone,gtk_entry_get_text(GTK_ENTRY(telephone_input)));

	GtkWidget *adresse_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_adresse_entry");
	strcpy(m.adresse,gtk_entry_get_text(GTK_ENTRY(adresse_input)));

	GtkWidget *ville_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_ville_entry");
	strcpy(m.ville,gtk_entry_get_text(GTK_ENTRY(ville_input)));

	GtkWidget *date_jour_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_jour_spinbutton");
	m.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour_input));

	GtkWidget *date_mois_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_mois_spinbutton");
	m.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois_input));

	GtkWidget *date_annee_input = lookup_widget(objet_graphique, "mbm_gestion_membre_Modifier_dnd_annee_spinbutton");
	m.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee_input));

	GtkWidget *poids_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_poids_spinbutton");
	m.poids = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(poids_input));

	GtkWidget *taille_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_taille_spinbutton");
	m.taille = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(taille_input));

	GtkWidget *code_postal_input = lookup_widget(objet_graphique, "mbm_gestion_membre_modifier_codepostal_entry");
	strcpy(m.code_postal, gtk_entry_get_text(GTK_ENTRY(code_postal_input)));

	m.genre = genre;

	char *fichier = "membre.txt";
	int result = modifier_membre(fichier, m.id, m);
}


void
on_mbm_gestion_membre_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "mbm_gestion_membre_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "membre.txt";
	supprimer_membre(fichier, id_supp);
}

int statut[] = {0, 0};

void
on_ft_gestion_entraineur_dashboard_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	entraineur e;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID_ENTRAINEUR, &e.id, NOM_ENTRAINEUR, e.nom, PRENOM_ENTRAINEUR, e.prenom, ADRESSE_POSTAL_ENTRAINEUR, e.adresse_postal, ADRESSE_MAIL_ENTRAINEUR, e.adresse_mail, TELEPHONE_ENTRAINEUR, e.telephone, GENRE_ENTRAINEUR, &e.genre, DATE_NAIS_JOUR_ENTRAINEUR, &e.date_nais_jour, DATE_NAIS_MOIS_ENTRAINEUR, &e.date_nais_mois, DATE_NAIS_ANNEE_ENTRAINEUR, &e.date_nais_annee, DATE_DEB_JOUR_ENTRAINEUR, &e.date_deb_jour, DATE_DEB_MOIS_ENTRAINEUR, &e.date_deb_mois, DATE_DEB_ANNEE_ENTRAINEUR, &e.date_deb_annee, STATUT_ENTRAINEUR, &e.statut, -1);
		char *fichier = "entraineur.txt";		
		supprimer_entraineur(fichier, e.id);
		afficher_entraineur(GTK_WIDGET(treeview));
	}
}


void
on_ft_gestion_entraineur_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_dashboard_treeview");
	afficher_entraineur(tree_input);
}


void
on_ft_gestion_entraineur_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	entraineur e;
	e.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_nom_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_prenom_entry");
	strcpy(e.prenom,gtk_entry_get_text(GTK_ENTRY(prenom_input)));

	GtkWidget *adresse_postal_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_adressepostale_entry");
	strcpy(e.adresse_postal,gtk_entry_get_text(GTK_ENTRY(adresse_postal_input)));

	GtkWidget *adresse_mail_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_adressemail_entry");
	strcpy(e.adresse_mail,gtk_entry_get_text(GTK_ENTRY(adresse_mail_input)));

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_telephone_entry");
	strcpy(e.telephone,gtk_entry_get_text(GTK_ENTRY(telephone_input)));

	GtkWidget *date_nais_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_dnd_jour_spinbutton");
	e.date_nais_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_jour_input));

	GtkWidget *date_nais_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_dnd_mois_spinbutton");
	e.date_nais_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_mois_input));

	GtkWidget *date_nais_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_dnd_annee_spinbutton");
	e.date_nais_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_annee_input));

	GtkWidget *date_deb_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_datedebut_jour_spinbutton");
	e.date_deb_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_jour_input));

	GtkWidget *date_deb_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_datedebut_mois_spinbutton");
	e.date_deb_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_mois_input));

	GtkWidget *date_deb_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_ajouter_datedebut_annee_spinbutton");
	e.date_deb_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_annee_input));

	e.genre = genre;
	e.statut = statut[0] + statut[1];
	statut[0] = 0;
	statut[1] = 0;

	char *fichier = "entraineur.txt";
	int result = ajouter_entraineur(fichier, e);
}


void
on_ft_gestion_entraineur_ajouter_femme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 1;
}


void
on_ft_gestion_entraineur_ajouter_homme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 2;
}


void
on_ft_gestion_entraineur_ajouter_actif_checkbutton_clicked
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		statut[0] = 1;
	}
	else
		statut[0] = 0;
}


void
on_ft_gestion_entraineur_ajouter_inactif_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		statut[1] = 2;
	}
	else
		statut[1] = 0;
}


void
on_ft_gestion_entraineur_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	entraineur e;
	e.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_nom_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_prenom_entry");
	strcpy(e.prenom,gtk_entry_get_text(GTK_ENTRY(prenom_input)));

	GtkWidget *adresse_postal_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_adressepostale_entry");
	strcpy(e.adresse_postal,gtk_entry_get_text(GTK_ENTRY(adresse_postal_input)));

	GtkWidget *adresse_mail_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_adressemail_entry");
	strcpy(e.adresse_mail,gtk_entry_get_text(GTK_ENTRY(adresse_mail_input)));

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_telephone_entry");
	strcpy(e.telephone,gtk_entry_get_text(GTK_ENTRY(telephone_input)));

	GtkWidget *date_nais_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_jour_spinbutton");
	e.date_nais_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_jour_input));

	GtkWidget *date_nais_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_mois_spinbutton");
	e.date_nais_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_mois_input));

	GtkWidget *date_nais_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_annee_spinbutton");
	e.date_nais_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_nais_annee_input));

	GtkWidget *date_deb_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_jour_spinbutton");
	e.date_deb_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_jour_input));

	GtkWidget *date_deb_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_mois_spinbutton");
	e.date_deb_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_mois_input));

	GtkWidget *date_deb_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_annee_spinbutton");
	e.date_deb_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_deb_annee_input));

	e.genre = genre;
	e.statut = statut[0] + statut[1];
	statut[0] = 0;
	statut[1] = 0;

	char *fichier = "entraineur.txt";
	int result = modifier_entraineur(fichier, e.id, e);
}


void
on_ft_gestion_entraineur_modifier_femme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 1;
}


void
on_ft_gestion_entraineur_modifier_homme_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		genre = 2;
}


void
on_ft_gestion_entraineur_modifier_actif_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		statut[0] = 1;
	}
	else
		statut[0] = 0;
}


void
on_ft_gestion_entraineur_modifier_inactif_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
	{
		statut[1] = 2;
	}
	else
		statut[1] = 0;
}


void
on_ft_gestion_entraineur_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "entraineur.txt";
	supprimer_entraineur(fichier, id_supp);
}


void
on_ft_gestion_entraineur_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "entraineur.txt";
	entraineur e = chercher_entraineur(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_nom_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), e.nom);

	GtkWidget *prenom_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_prenom_entry");
	gtk_entry_set_text(GTK_ENTRY(prenom_input), e.prenom);

	GtkWidget *adresse_postal_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_adressepostale_entry");
	gtk_entry_set_text(GTK_ENTRY(adresse_postal_input), e.adresse_postal);

	GtkWidget *adresse_mail_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_adressemail_entry");
	gtk_entry_set_text(GTK_ENTRY(adresse_mail_input), e.adresse_mail);

	GtkWidget *telephone_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_telephone_entry");
	gtk_entry_set_text(GTK_ENTRY(telephone_input), e.telephone);

	GtkWidget *date_nais_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_nais_jour_input), e.date_nais_jour);

	GtkWidget *date_nais_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_mois_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_nais_mois_input), e.date_nais_mois);

	GtkWidget *date_nais_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_dnd_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_nais_annee_input), e.date_nais_annee);

	GtkWidget *date_deb_jour_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_deb_jour_input), e.date_deb_jour);

	GtkWidget *date_deb_mois_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_mois_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_deb_mois_input), e.date_deb_mois);

	GtkWidget *date_deb_annee_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_datedebut_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_deb_annee_input), e.date_deb_annee);

	GtkWidget *genre_femme_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_femme_radiobutton");
	if(e.genre == 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_femme_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_femme_input), FALSE);

	GtkWidget *genre_homme_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_homme_radiobutton");
	if(e.genre == 2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_homme_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(genre_homme_input), FALSE);

	GtkWidget *statut_actif_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_actif_checkbutton");
	GtkWidget *statut_inactif_input = lookup_widget(objet_graphique, "ft_gestion_entraineur_modifier_inactif_checkbutton");
	
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(statut_actif_input), FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(statut_inactif_input), FALSE);	
	if(e.statut & 1)
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(statut_actif_input), TRUE);
	}
	e.statut = e.statut >> 1;
		
	if(e.statut & 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(statut_inactif_input), TRUE);
}

int type_ev = 1;

void
on_am_gestion_evenement_ajouter_liste_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	evenement e;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID_EVENEMENT, &e.id, NOM_EVENEMENT, e.nom, TYPE_EVENEMENT, &e.type, DATE_JOUR_EVENEMENT, &e.date_jour, DATE_MOIS_EVENEMENT, &e.date_mois, DATE_ANNEE_EVENEMENT, &e.date_annee, DATE_HEURE_EVENEMENT, &e.date_heure, DATE_MINUTE_EVENEMENT, &e.date_minute, -1);
		char *fichier = "evenement.txt";		
		supprimer_evenement(fichier, e.id);
		afficher_evenement(GTK_WIDGET(treeview));
	}
}


void
on_am_gestion_evenement_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_liste_treeview");
	afficher_evenement(tree_input);
}


void
on_am_gestion_evenement_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	evenement e;
	e.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_nomevenement_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *date_jour = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_jour_spinbutton");
	e.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour));

	GtkWidget *date_mois = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_mois_spinbutton");
	e.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois));

	GtkWidget *date_annee = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_annee_spinbutton");
	e.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee));

	GtkWidget *date_heure = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_heure_spinbutton");
	e.date_heure = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_heure));

	GtkWidget *date_minute = lookup_widget(objet_graphique, "am_gestion_evenement_ajouter_minute_spinbutton");
	e.date_minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_minute));

	
	e.type = type_ev;
	type_ev = 1;

	char *fichier = "evenement.txt";
	int result = ajouter_evenement(fichier,e);
}


void
on_am_gestion_evenement_ajouter_sport_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type_ev = 1;
}


void
on_am_gestion_evenement_ajouter_nutrition_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		etat = 2;
}


void
on_am_gestion_evenement_ajouter_bienetre_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type_ev = 3;
}


void
on_am_gestion_evenement_modifier_nutrition_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type_ev = 2;
}


void
on_am_gestion_evenement_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
		GtkWidget *id_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "evenement.txt";
	evenement e = chercher_evenement(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_nomevenement_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), e.nom);

	GtkWidget *date_jour_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_jour_input), e.date_jour);

	GtkWidget *date_mois_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_mois_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_mois_input), e.date_mois);

	GtkWidget *date_annee_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_annee_input), e.date_annee);

	GtkWidget *date_heure_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_heure_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_heure_input), e.date_heure);

	GtkWidget *date_minute_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_minute_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_minute_input), e.date_minute);

	GtkWidget *type_sport_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_sport_radiobutton");
	if(e.type == 1)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_sport_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_sport_input), FALSE);

	GtkWidget *type_nutrition_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_nutrition_radiobutton");
	if(e.type == 2)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_nutrition_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_nutrition_input), FALSE);

	GtkWidget *type_bienetre_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_bienetre_radiobutton");
	if(e.type == 3)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_bienetre_input), TRUE);
	else
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(type_bienetre_input), FALSE);

}


void
on_am_gestion_evenement_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	evenement e;
	e.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_nomevenement_entry");
	strcpy(e.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

	GtkWidget *date_jour = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_jour_spinbutton");
	e.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour));

	GtkWidget *date_mois = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_mois_spinbutton");
	e.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois));

	GtkWidget *date_annee = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_annee_spinbutton");
	e.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee));

	GtkWidget *date_heure = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_heure_spinbutton");
	e.date_heure = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_heure));

	GtkWidget *date_minute = lookup_widget(objet_graphique, "am_gestion_evenement_modifier_minute_spinbutton");
	e.date_minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_minute));

	
	e.type = type_ev;
	type_ev = 1;

	char *fichier = "evenement.txt";
	int result = modifier_evenement(fichier, e.id, e);
}


void
on_am_gestion_evenement_modifier_sport_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type_ev = 1;
}


void
on_am_gestion_evenement_modifier_bienetre_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		type_ev = 3;
}


void
on_am_gestion_evenement_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "am_gestion_evenement_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "evenement.txt";
	supprimer_evenement(fichier, id_supp);
}


void
on_em_gestion_cours_ajouter_liste_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	cours c;

	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model, &iter, path))
	{
		gtk_tree_model_get(model, &iter, ID_COURS, &c.id, NOM_COURS, c.nom, DATE_HEURE_COURS, &c.date_heure, DATE_MINUTE_COURS, &c.date_minute, DATE_JOUR_COURS, &c.date_jour, DATE_MOIS_COURS, &c.date_mois, DATE_ANNEE_COURS, &c.date_annee, DUREE_COURS, &c.duree, TYPE_COURS, &c.type, -1);
		char *fichier = "cours.txt";		
		supprimer_cours(fichier, c.id);
		afficher_cours(GTK_WIDGET(treeview));
	}
}


void
on_em_gestion_cours_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *tree_input = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_liste_treeview");
	afficher_cours(tree_input);
}


void
on_em_gestion_cours_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	cours c;
	c.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_nomcours_entry");
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *type_input = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_typecours_comboboxentry");
	strcpy(c.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_input)));

	GtkWidget *date_heure = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_heurecours_heure_spinbutton");
	c.date_heure = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_heure));

	GtkWidget *date_minute = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_heurecours_minute_spinbutton");
	c.date_minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_minute));

	GtkWidget *date_jour = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_datecours_jour_spinbutton");
	c.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour));

	GtkWidget *date_mois = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_datecours_mois_spinbutton");
	c.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois));

	GtkWidget *date_annee = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_datecours_annee_spinbutton");
	c.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee));

	GtkWidget *duree = lookup_widget(objet_graphique, "em_gestion_cours_ajouter_duree_spinbutton");
	c.duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duree));

	char *fichier = "cours.txt";
	int result = ajouter_cours(fichier,c);
}


void
on_em_gestion_cours_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_rechercher_entry");
	id = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "cours.txt";
	cours c = chercher_cours(fichier, id);
	
	GtkWidget *nom_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_nomcours_entry");
	gtk_entry_set_text(GTK_ENTRY(nom_input), c.nom);

        GtkWidget *type_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_typecours_comboboxentry");
	char *fichier2 = "type_cours.txt";
	FILE *f = fopen(fichier2, "r");
	char type_cours[100];
	int i = 0;
	if(f!=NULL)
	{
		while(fscanf(f, "%s\n", type_cours) != EOF)
		{
			if(strcmp(type_cours, c.type) == 0)
				break;
			i++;
		}
		fclose(f);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(type_input), i);

	GtkWidget *date_heure_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_heurecours_heure_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_heure_input), c.date_heure);

	GtkWidget *date_minute_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_heurecours_minute_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_minute_input), c.date_minute);

	GtkWidget *date_jour_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_jour_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_jour_input), c.date_jour);

	GtkWidget *date_mois_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_mois_spoinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_mois_input), c.date_mois);

	GtkWidget *date_annee_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_annee_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(date_annee_input), c.date_annee);

	GtkWidget *duree_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_duree_spinbutton");
	gtk_spin_button_set_value(GTK_SPIN_BUTTON(duree_input), c.duree);
}


void
on_em_gestion_cours_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	cours c;
	c.id = 0;

	GtkWidget *nom_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_nomcours_entry");
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom_input)));

        GtkWidget *type_input = lookup_widget(objet_graphique, "em_gestion_cours_modifier_typecours_comboboxentry");
	strcpy(c.type,gtk_combo_box_get_active_text(GTK_COMBO_BOX(type_input)));

	GtkWidget *date_heure = lookup_widget(objet_graphique, "em_gestion_cours_modifier_heurecours_heure_spinbutton");
	c.date_heure = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_heure));

	GtkWidget *date_minute = lookup_widget(objet_graphique, "em_gestion_cours_modifier_heurecours_minute_spinbutton");
	c.date_minute = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_minute));

	GtkWidget *date_jour = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_jour_spinbutton");
	c.date_jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_jour));

	GtkWidget *date_mois = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_mois_spoinbutton");
	c.date_mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_mois));

	GtkWidget *date_annee = lookup_widget(objet_graphique, "em_gestion_cours_modifier_datecours_annee_spinbutton");
	c.date_annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(date_annee));

	GtkWidget *duree = lookup_widget(objet_graphique, "em_gestion_cours_modifier_duree_spinbutton");
	c.duree = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(duree));

	char *fichier = "cours.txt";
	int result = modifier_cours(fichier,c.id, c);
}


void
on_em_gestion_cours_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	GtkWidget *id_input = lookup_widget(objet_graphique, "em_gestion_cours_supprimer_id_entry");
	int id_supp = atoi(gtk_entry_get_text(GTK_ENTRY(id_input)));
	
	char *fichier = "cours.txt";
	supprimer_cours(fichier, id_supp);
}


void
on_login_connexion_button_clicked      (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
	char identifiant[30];
	char motdepasse[30];
	GtkWidget *identifiant_input = lookup_widget(objet_graphique, "login_id_entry");
	strcpy(identifiant,gtk_entry_get_text(GTK_ENTRY(identifiant_input)));
	GtkWidget *motdepasse_input = lookup_widget(objet_graphique, "login_password_entry");
	strcpy(motdepasse,gtk_entry_get_text(GTK_ENTRY(motdepasse_input)));

	char id[30];
	char pass[30];
	int type_utilisateur = 0;
	int found = 0;
	GtkWidget *espace_administratif;
  	GtkWidget *espace_membre;
  	GtkWidget *espace_entraineur;

	FILE *f = fopen("login.txt", "a+");
	if(f!=NULL)
	{
		cours temp;
		while(fscanf(f, "%s %s %d\n", id, pass, &type_utilisateur) != EOF)
		{
			if(strcmp(id, identifiant) == 0 && strcmp(pass, motdepasse) == 0)
			{
				found = 1;
				if(type_utilisateur == 0) 
				{
					espace_membre = create_espace_membre ();
  					gtk_widget_show (espace_membre);
				}
				else if(type_utilisateur == 1)
				{
					espace_entraineur = create_espace_entraineur ();
  					gtk_widget_show (espace_entraineur);
				}
				else if(type_utilisateur == 2)
				{
					espace_administratif = create_espace_administratif ();
  					gtk_widget_show (espace_administratif);
				}
			
				break;
			}
		}
		/*if(found == 0)
		{
			fprintf(f, "%s %s %d\n", identifiant, motdepasse, type_utilisateur);
			espace_membre = create_espace_membre ();
  			gtk_widget_show (espace_membre);
		}*/
		GtkWidget *window = lookup_widget(objet_graphique, "login");
		gtk_widget_destroy(window);
		fclose(f);
	}
}


void
on_in_gestion_equipement_reservation_valider_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{



}

