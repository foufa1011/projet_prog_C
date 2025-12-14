#include <gtk/gtk.h>


void
on_in_gestion_equipement_ajouter_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_in_gestion_equipement_ajouter_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_ajouter_enpanne_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_ajouter_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_modifier_rechercher_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_in_gestion_equipement_modifier_enregistrer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_in_gestion_equipement_modifier_enpanne_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobutton84_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_modifier_disponible_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_supprimer_supprimer_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_in_gestion_equipement_modifier_enmaintenance_radiobutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_in_gestion_equipement_ajouter_actualiser_button_clicked
                                        (GtkWidget       *objet_graphique,
                                        gpointer         user_data);

void
on_in_gestion_equipement_ajouter_liste_treeview_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
