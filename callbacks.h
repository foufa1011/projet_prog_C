#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include "trainers.h"

/* Global trainer list */
extern TrainerList *trainer_list;

/* main cruds functions */
void on_ft_gestion_entraineur_ajouter_enregistrer_button_clicked(GtkButton *button, gpointer user_data);
void on_ft_gestion_entraineur_modifier_rechercher_button_clicked(GtkButton *button, gpointer user_data);
void on_ft_gestion_entraineur_modifier_enregistrer_button_clicked(GtkButton *button, gpointer user_data);
void on_ft_gestion_entraineur_supprimer_rechercher_button_clicked(GtkButton *button, gpointer user_data);
void on_ft_gestion_entraineur_supprimer_supprimer_button_clicked(GtkButton *button, gpointer user_data);
void on_ft_gestion_entraineur_supprimer_annuler_button_clicked(GtkButton *button, gpointer user_data);

/* Field validation */
void on_ft_gestion_entraineur_ajouter_id_entry_changed(GtkEditable *editable, gpointer user_data);

/* Dashboard functions */
void initialize_dashboard(GtkWidget *treeview);
void refresh_dashboard(GtkWidget *treeview);

/* Utility functions */
void set_message_style(GtkWidget *label, const char *message, const char *color);
void update_specialty_display(GtkComboBox *combo, const char *specialty);
void load_specialties_to_combobox(GtkComboBox *combo);

/* New TR ID and login functions */
void generate_tr_id(GtkWidget *window);
int is_tr_id_unique(TrainerList *list, const char *id);
void generate_random_password(char *password, int length);
void save_trainer_login(const char *trainer_id, const char *password);
void remove_trainer_login(const char *trainer_id);
void initialize_add_trainer_tab(GtkWidget *window);

/* Form management */
void clear_add_form(GtkWidget *window);
void clear_modify_form(GtkWidget *window);
void clear_delete_form(GtkWidget *window);

/* Cell data functions */
void gender_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                          GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data);
void status_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                          GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data);
void name_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                        GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data);



/* Ajouter Tab - Entry Changes */
void on_ft_gestion_entraineur_ajouter_nomcomplet_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_adressepostale_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_adressemail_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_telephone_entry_changed(GtkEditable *editable, gpointer user_data);

/* Ajouter Tab - SpinButton Changes */
void on_ft_gestion_entraineur_ajouter_datedebut_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_datedebut_mois_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_datedebut_annee_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_dnd_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_dnd_mois_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_dnd_annee_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);

/* Ajouter Tab - Radio/Check Buttons */
void on_ft_gestion_entraineur_ajouter_femme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_actif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_inactif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_specialite_comboboxentry_changed(GtkComboBox *combobox, gpointer user_data);
void on_ft_gestion_entraineur_ajouter_homme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* Modifier Tab - Entry Changes */
void on_ft_gestion_entraineur_modifier_nomcomplet_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_adressepostale_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_adressemail_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_telephone_entry_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_rechercher_entry_changed(GtkEditable *editable, gpointer user_data);

/* Modifier Tab - SpinButton Changes */
void on_ft_gestion_entraineur_modifier_datedebut_jour_spinbutton_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_datedebut_mois_spinbutton_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_datedebut_annee_spinbutton_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_dnd_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data);
void on_ft_gestion_entraineur_modifier_dnd_mois_spinbutton_changed(GtkEditable *editable, gpointer user_data);
void on_ft_gestion_entraineur_modifier_dnd_annee_spinbutton_changed(GtkEditable *editable, gpointer user_data);

/* Modifier Tab - Radio/Check Buttons */
void on_ft_gestion_entraineur_modifier_specialite_comboboxentry_changed(GtkComboBox *combobox, gpointer user_data);
void on_ft_gestion_entraineur_modifier_actif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_modifier_inactif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_modifier_femme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);
void on_ft_gestion_entraineur_modifier_homme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);

/* Supprimer Tab */
void on_ft_gestion_entraineur_supprimer_id_entry_changed(GtkEditable *editable, gpointer user_data);

/* Login Window */
void on_login_mpoublie_button_clicked(GtkButton *button, gpointer user_data);
void on_login_connexion_button_clicked(GtkButton *button, gpointer user_data);
void on_login_showpassword_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data);

#endif




