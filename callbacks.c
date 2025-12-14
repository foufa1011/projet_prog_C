#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "trainers.h"



/* Utility function for styled messages */
void set_message_style(GtkWidget *label, const char *message, const char *color) {
    if (!label) return;
    
    char styled_message[512];
    if (strcmp(color, "red") == 0) {
        snprintf(styled_message, sizeof(styled_message), "<span foreground='red' weight='bold'>%s</span>", message);
    } else if (strcmp(color, "green") == 0) {
        snprintf(styled_message, sizeof(styled_message), "<span foreground='green' weight='bold'>%s</span>", message);
    } else {
        strcpy(styled_message, message);
    }
    
    gtk_label_set_markup(GTK_LABEL(label), styled_message);
}

/* Utility function for specialty combobox */
void update_specialty_display(GtkComboBox *combo, const char *specialty) {
    if (!combo || !specialty) return;
    
    GtkTreeModel *model = gtk_combo_box_get_model(combo);
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    gboolean found = FALSE;
    
    while (valid) {
        gchar *specialty_text = NULL;
        gtk_tree_model_get(model, &iter, 0, &specialty_text, -1);
        
        if (specialty_text && strcmp(specialty_text, specialty) == 0) {
            gtk_combo_box_set_active_iter(combo, &iter);
            g_free(specialty_text);
            found = TRUE;
            break;
        }
        
        if (specialty_text) g_free(specialty_text);
        valid = gtk_tree_model_iter_next(model, &iter);
    }
    
    if (!found) {
        GtkEntry *entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(combo)));
        if (entry) {
            gtk_entry_set_text(entry, specialty);
        }
    }
}

/* Load specialties to combobox */
void load_specialties_to_combobox(GtkComboBox *combo) {
    GtkListStore *store;
    GtkTreeIter iter;
    
    store = gtk_list_store_new(1, G_TYPE_STRING);
    
    const char *specialties[] = {
        "Fitness", "Yoga", "Pilates", "CrossFit", "Boxe",
        "Natation", "Cardio", "Musculation", "Danse", "Arts Martiaux",
        NULL
    };
    
    for (int i = 0; specialties[i] != NULL; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, specialties[i], -1);
    }
    
    gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
    g_object_unref(store);
}



/* Generate a random password of specified length */
void generate_random_password(char *password, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";
    int charset_size = sizeof(charset) - 1;
    
    // Seed random number generator once
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    
    for (int i = 0; i < length; i++) {
        int key = rand() % charset_size;
        password[i] = charset[key];
    }
    password[length] = '\0';
}

/* Check if ID already exists in trainers list */
int is_tr_id_unique(TrainerList *list, const char *id) {
    if (!list || !id) return 0;
    
    Trainer *current = list->head;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            return 0; // ID already exists
        }
        current = current->next;
    }
    return 1; // ID is unique
}

/* Generate next ID in TR-XXXX format */
void generate_tr_id(GtkWidget *window) {
    GtkWidget *id_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_id_entry");
    if (!id_entry) return;
    
    // Seed random number generator once
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }
    

    char new_id[10];
    int attempts = 0;
    int max_attempts = 100;
    
    do {
        // Generate random 4-digit number
        int random_num = 1000 + (rand() % 9000); // 1000-9999
        snprintf(new_id, sizeof(new_id), "TR-%04d", random_num);
        attempts++;
        
        // If we've tried too many times, add a timestamp-based number
        if (attempts >= max_attempts) {
            int timestamp_num = (time(NULL) % 9000) + 1000;
            snprintf(new_id, sizeof(new_id), "TR-%04d", timestamp_num);
            break;
        }
    } while (!is_tr_id_unique(trainer_list, new_id));
    
    // Set the generated ID in the entry
    gtk_entry_set_text(GTK_ENTRY(id_entry), new_id);
    
    fprintf(stderr, "Auto-generated TR ID: %s (attempts: %d)\n", new_id, attempts);
}


//---------- enregister ent -- trainer_log.txt -----------
void save_trainer_login(const char *trainer_id, const char *password) {
    FILE *file = fopen("trainer_login.txt", "a");
    if (!file) {
        fprintf(stderr, "Error: Cannot open trainer_login.txt for writing\n");
        return;
    }
    
    fprintf(file, "%s | %s\n", trainer_id, password);
    fclose(file);
    
    fprintf(stderr, "Trainer login saved: %s | %s\n", trainer_id, password);
}

//----------- supprimer id ent --- trainer_log.txt ----------
void remove_trainer_login(const char *trainer_id) {
    FILE *file = fopen("trainer_login.txt", "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open trainer_login.txt for reading\n");
        return;
    }
    
    FILE *temp_file = fopen("trainer_login_temp.txt", "w");
    if (!temp_file) {
        fprintf(stderr, "Error: Cannot create temporary file\n");
        fclose(file);
        return;
    }
    
    char line[100];
    int found = 0;
    
    while (fgets(line, sizeof(line), file)) {

        char current_id[10];
        char password[50];
        

        if (sscanf(line, "%9[^|] | %49[^\n]", current_id, password) == 2) {

            for (int i = strlen(current_id) - 1; i >= 0 && current_id[i] == ' '; i--) {
                current_id[i] = '\0';
            }
            

            if (strcmp(current_id, trainer_id) == 0) {
                found = 1;
                fprintf(stderr, "Removing login entry for trainer: %s\n", trainer_id);
                continue; 
            }
        }
        

        fputs(line, temp_file);
    }
    
    fclose(file);
    fclose(temp_file);
    
    // Replace original file with temp file
    remove("trainer_login.txt");
    rename("trainer_login_temp.txt", "trainer_login.txt");
    
    if (found) {
        fprintf(stderr, "Successfully removed login for trainer: %s\n", trainer_id);
    } else {
        fprintf(stderr, "Login entry not found for trainer: %s\n", trainer_id);
    }
}

//---------- tab ajouter ent / enregistrer button ----------
void on_ft_gestion_entraineur_ajouter_enregistrer_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "ADD: Save button clicked\n");
    
    GtkWidget *id_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_id_entry");
    GtkWidget *name_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_nomcomplet_entry");
    GtkWidget *msg_label = lookup_widget(window, "ft_gestion_entraineur_ajouter_msg_label");
    
    if (!id_entry || !name_entry) {
        fprintf(stderr, "Error: Required widgets not found\n");
        return;
    }
    
    const char *id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
    
    // Validate ID format (TR-XXXX)
    if (strlen(id) == 0 || strlen(name) == 0) {
        set_message_style(msg_label, "Erreur: Veuillez remplir tous les champs", "red");
        return;
    }
    
    // Check ID format
    if (strncmp(id, "TR-", 3) != 0 || strlen(id) != 7) {
        set_message_style(msg_label, "Erreur: Format ID invalide. Doit être TR-XXXX (4 chiffres)", "red");
        return;
    }
    
    // Check if last 4 characters are digits
    for (int i = 3; i < 7; i++) {
        if (id[i] < '0' || id[i] > '9') {
            set_message_style(msg_label, "Erreur: Les 4 derniers caractères doivent être des chiffres", "red");
            return;
        }
    }
    
    if (!is_id_unique(trainer_list, id)) {
        set_message_style(msg_label, "Erreur: ID déjà utilisé", "red");
        return;
    }
    
    Trainer new_trainer = {0};
    strcpy(new_trainer.id, id);
    strcpy(new_trainer.full_name, name);
    
    // Get other fields using lookup_widget
    GtkWidget *phone_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_telephone_entry");
    GtkWidget *email_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_adressemail_entry");
    GtkWidget *address_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_adressepostale_entry");
    GtkWidget *male_radio = lookup_widget(window, "ft_gestion_entraineur_ajouter_homme_radiobutton");
    GtkWidget *female_radio = lookup_widget(window, "ft_gestion_entraineur_ajouter_femme_radiobutton");
    GtkWidget *specialty_combo = lookup_widget(window, "ft_gestion_entraineur_ajouter_specialite_comboboxentry");
    GtkWidget *active_check = lookup_widget(window, "ft_gestion_entraineur_ajouter_actif_checkbutton");
    GtkWidget *inactive_check = lookup_widget(window, "ft_gestion_entraineur_ajouter_inactif_checkbutton");
    
    if (phone_entry) strcpy(new_trainer.phone, gtk_entry_get_text(GTK_ENTRY(phone_entry)));
    if (email_entry) strcpy(new_trainer.email, gtk_entry_get_text(GTK_ENTRY(email_entry)));
    if (address_entry) strcpy(new_trainer.address, gtk_entry_get_text(GTK_ENTRY(address_entry)));
    
    // Get gender
    if (male_radio && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(male_radio))) {
        strcpy(new_trainer.gender, "Homme");
    } else if (female_radio && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(female_radio))) {
        strcpy(new_trainer.gender, "Femme");
    } else {
        strcpy(new_trainer.gender, "Non spécifié");
    }
    
    // Get status
    if (active_check && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(active_check))) {
        strcpy(new_trainer.status, "Actif");
    } else if (inactive_check && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inactive_check))) {
        strcpy(new_trainer.status, "Inactif");
    } else {
        strcpy(new_trainer.status, "Inactif");
    }
    
    // Get specialty
    if (specialty_combo) {
        GtkTreeIter iter;
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(specialty_combo), &iter)) {
            GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(specialty_combo));
            gchar *specialty = NULL;
            gtk_tree_model_get(model, &iter, 0, &specialty, -1);
            if (specialty) {
                strcpy(new_trainer.specialty, specialty);
                g_free(specialty);
            }
        } else {
            GtkEntry *entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(specialty_combo)));
            if (entry) {
                const char *specialty_text = gtk_entry_get_text(entry);
                strcpy(new_trainer.specialty, specialty_text);
            }
        }
    }
    
    // Get dates
    GtkWidget *birth_day = lookup_widget(window, "ft_gestion_entraineur_ajouter_dnd_jour_spinbutton");
    GtkWidget *birth_month = lookup_widget(window, "ft_gestion_entraineur_ajouter_dnd_mois_spinbutton");
    GtkWidget *birth_year = lookup_widget(window, "ft_gestion_entraineur_ajouter_dnd_annee_spinbutton");
    GtkWidget *start_day = lookup_widget(window, "ft_gestion_entraineur_ajouter_datedebut_jour_spinbutton");
    GtkWidget *start_month = lookup_widget(window, "ft_gestion_entraineur_ajouter_datedebut_mois_spinbutton");
    GtkWidget *start_year = lookup_widget(window, "ft_gestion_entraineur_ajouter_datedebut_annee_spinbutton");
    
    if (birth_day) new_trainer.birth_date.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_day));
    if (birth_month) new_trainer.birth_date.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_month));
    if (birth_year) new_trainer.birth_date.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_year));
    if (start_day) new_trainer.start_date.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_day));
    if (start_month) new_trainer.start_date.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_month));
    if (start_year) new_trainer.start_date.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_year));
    
    if (add_trainer(trainer_list, &new_trainer) == 0) {
        // Generate and save trainer login
        char password[9];
        generate_random_password(password, 8);
        save_trainer_login(new_trainer.id, password);
        
        set_message_style(msg_label, "Entraîneur ajouté avec succès!", "green");
        clear_add_form(window);
        
        // Generate new TR ID for next entry
        generate_tr_id(window);
        
        // Save trainers to file
        save_trainers_to_file(trainer_list, "trainers.txt");
        
        GtkWidget *treeview = lookup_widget(window, "ft_gestion_entraineur_dashboard_treeview");
        if (treeview) refresh_dashboard(treeview);
    } else {
        set_message_style(msg_label, "Erreur lors de l'ajout", "red");
    }
}

//////////// intialize tab "ajouter" ////////////////////////

void initialize_add_trainer_tab(GtkWidget *window) {
    if (!window) return;
    
    GtkWidget *id_entry = lookup_widget(window, "ft_gestion_entraineur_ajouter_id_entry");
    if (id_entry) {
        generate_tr_id(window);
    }
}

/////////////////// ID FORMAT TR-XXXX /////////////////////
void on_ft_gestion_entraineur_ajouter_id_entry_changed(GtkEditable *editable, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(editable));
    GtkWidget *id_warning = lookup_widget(window, "ft_gestion_entraineur_ajouter_idwarning_label");
    const char *id = gtk_entry_get_text(GTK_ENTRY(editable));
    
    if (id_warning) {
        if (strlen(id) > 0) {
            // Check format
            if (strncmp(id, "TR-", 3) != 0 || strlen(id) != 7) {
                set_message_style(id_warning, "Format invalide. Doit être TR-XXXX (4 chiffres)", "red");
            } else {
                // Check if last 4 characters are digits
                int valid = 1;
                for (int i = 3; i < 7; i++) {
                    if (id[i] < '0' || id[i] > '9') {
                        valid = 0;
                        break;
                    }
                }
                
                if (!valid) {
                    set_message_style(id_warning, "Les 4 derniers caractères doivent être des chiffres", "red");
                } else if (!is_id_unique(trainer_list, id)) {
                    set_message_style(id_warning, "ID déjà existant!", "red");
                } else {
                    gtk_label_set_text(GTK_LABEL(id_warning), "");
                }
            }
        } else {
            gtk_label_set_text(GTK_LABEL(id_warning), "");
        }
    }
}

///------------ button rechercher ent - modifier tab ------------
void on_ft_gestion_entraineur_modifier_rechercher_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "MODIFY: Search button clicked\n");
    
    GtkWidget *search_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_rechercher_entry");
    GtkWidget *id_display = lookup_widget(window, "ft_gestion_entraineur_modifier_id_display_label");
    GtkWidget *msg_label = lookup_widget(window, "ft_gestion_entraineur_modifier_msg_label");
    
    if (!search_entry || !id_display) return;
    
    const char *search_id = gtk_entry_get_text(GTK_ENTRY(search_entry));
    
    if (strlen(search_id) == 0) {
        set_message_style(msg_label, "Veuillez entrer un ID", "red");
        return;
    }
    
    // Search for trainer with ID
    Trainer *trainer = find_trainer(trainer_list, search_id);
    
    if (!trainer) {
        set_message_style(msg_label, "Entraîneur non trouvé", "red");
        gtk_label_set_text(GTK_LABEL(id_display), "");
        clear_modify_form(window);
        return;
    }
    
    gtk_label_set_text(GTK_LABEL(id_display), trainer->id);
    set_message_style(msg_label, "Entraîneur trouvé. Modifiez les champs nécessaires.", "green");
    
    // Populate form fields using lookup_widget
    GtkWidget *name_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_nomcomplet_entry");
    GtkWidget *phone_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_telephone_entry");
    GtkWidget *email_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_adressemail_entry");
    GtkWidget *address_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_adressepostale_entry");
    GtkWidget *male_radio = lookup_widget(window, "ft_gestion_entraineur_modifier_homme_radiobutton");
    GtkWidget *female_radio = lookup_widget(window, "ft_gestion_entraineur_modifier_femme_radiobutton");
    GtkWidget *specialty_combo = lookup_widget(window, "ft_gestion_entraineur_modifier_specialite_comboboxentry");
    GtkWidget *active_check = lookup_widget(window, "ft_gestion_entraineur_modifier_actif_checkbutton");
    GtkWidget *inactive_check = lookup_widget(window, "ft_gestion_entraineur_modifier_inactif_checkbutton");
    
    if (name_entry) gtk_entry_set_text(GTK_ENTRY(name_entry), trainer->full_name);
    if (phone_entry) gtk_entry_set_text(GTK_ENTRY(phone_entry), trainer->phone);
    if (email_entry) gtk_entry_set_text(GTK_ENTRY(email_entry), trainer->email);
    if (address_entry) gtk_entry_set_text(GTK_ENTRY(address_entry), trainer->address);
    
    // Set gender
    if (male_radio && female_radio) {
        if (strcmp(trainer->gender, "Homme") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(male_radio), TRUE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(female_radio), FALSE);
        } else if (strcmp(trainer->gender, "Femme") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(male_radio), FALSE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(female_radio), TRUE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(male_radio), FALSE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(female_radio), FALSE);
        }
    }
    
    // Set status
    if (active_check && inactive_check) {
        if (strcmp(trainer->status, "Actif") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(active_check), TRUE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(inactive_check), FALSE);
        } else {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(active_check), FALSE);
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(inactive_check), TRUE);
        }
    }
    
    // Set specialty
    if (specialty_combo) {
        update_specialty_display(GTK_COMBO_BOX(specialty_combo), trainer->specialty);
    }
    
    // Set dates
    GtkWidget *birth_day = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_jour_spinbutton");
    GtkWidget *birth_month = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_mois_spinbutton");
    GtkWidget *birth_year = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_annee_spinbutton");
    GtkWidget *start_day = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_jour_spinbutton");
    GtkWidget *start_month = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_mois_spinbutton");
    GtkWidget *start_year = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_annee_spinbutton");
    
    if (birth_day) gtk_spin_button_set_value(GTK_SPIN_BUTTON(birth_day), trainer->birth_date.day);
    if (birth_month) gtk_spin_button_set_value(GTK_SPIN_BUTTON(birth_month), trainer->birth_date.month);
    if (birth_year) gtk_spin_button_set_value(GTK_SPIN_BUTTON(birth_year), trainer->birth_date.year);
    if (start_day) gtk_spin_button_set_value(GTK_SPIN_BUTTON(start_day), trainer->start_date.day);
    if (start_month) gtk_spin_button_set_value(GTK_SPIN_BUTTON(start_month), trainer->start_date.month);
    if (start_year) gtk_spin_button_set_value(GTK_SPIN_BUTTON(start_year), trainer->start_date.year);
}

void on_ft_gestion_entraineur_modifier_enregistrer_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "MODIFY: Save button clicked\n");
    
    GtkWidget *id_display = lookup_widget(window, "ft_gestion_entraineur_modifier_id_display_label");
    GtkWidget *msg_label = lookup_widget(window, "ft_gestion_entraineur_modifier_msg_label");
    
    if (!id_display) return;
    
    const char *trainer_id = gtk_label_get_text(GTK_LABEL(id_display));
    if (strlen(trainer_id) == 0) {
        set_message_style(msg_label, "Aucun entraîneur sélectionné", "red");
        return;
    }
    
    Trainer updated_trainer = {0};
    strcpy(updated_trainer.id, trainer_id);
    
    // Get text entries using lookup_widget
    GtkWidget *name_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_nomcomplet_entry");
    GtkWidget *phone_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_telephone_entry");
    GtkWidget *email_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_adressemail_entry");
    GtkWidget *address_entry = lookup_widget(window, "ft_gestion_entraineur_modifier_adressepostale_entry");
    
    if (name_entry) strcpy(updated_trainer.full_name, gtk_entry_get_text(GTK_ENTRY(name_entry)));
    if (phone_entry) strcpy(updated_trainer.phone, gtk_entry_get_text(GTK_ENTRY(phone_entry)));
    if (email_entry) strcpy(updated_trainer.email, gtk_entry_get_text(GTK_ENTRY(email_entry)));
    if (address_entry) strcpy(updated_trainer.address, gtk_entry_get_text(GTK_ENTRY(address_entry)));
    
    // Get gender
    GtkWidget *male_radio = lookup_widget(window, "ft_gestion_entraineur_modifier_homme_radiobutton");
    GtkWidget *female_radio = lookup_widget(window, "ft_gestion_entraineur_modifier_femme_radiobutton");
    
    if (male_radio && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(male_radio))) {
        strcpy(updated_trainer.gender, "Homme");
    } else if (female_radio && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(female_radio))) {
        strcpy(updated_trainer.gender, "Femme");
    } else {
        strcpy(updated_trainer.gender, "Non spécifié");
    }
    
    // Get status
    GtkWidget *active_check = lookup_widget(window, "ft_gestion_entraineur_modifier_actif_checkbutton");
    GtkWidget *inactive_check = lookup_widget(window, "ft_gestion_entraineur_modifier_inactif_checkbutton");
    
    if (active_check && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(active_check))) {
        strcpy(updated_trainer.status, "Actif");
    } else if (inactive_check && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(inactive_check))) {
        strcpy(updated_trainer.status, "Inactif");
    } else {
        strcpy(updated_trainer.status, "Inactif");
    }
    
    // Get specialty
    GtkWidget *specialty_combo = lookup_widget(window, "ft_gestion_entraineur_modifier_specialite_comboboxentry");
    if (specialty_combo) {
        GtkTreeIter iter;
        if (gtk_combo_box_get_active_iter(GTK_COMBO_BOX(specialty_combo), &iter)) {
            GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(specialty_combo));
            gchar *specialty = NULL;
            gtk_tree_model_get(model, &iter, 0, &specialty, -1);
            if (specialty) {
                strcpy(updated_trainer.specialty, specialty);
                g_free(specialty);
            }
        } else {
            GtkEntry *entry = GTK_ENTRY(gtk_bin_get_child(GTK_BIN(specialty_combo)));
            if (entry) {
                const char *specialty_text = gtk_entry_get_text(entry);
                strcpy(updated_trainer.specialty, specialty_text);
            }
        }
    }
    
    // Get dates
    GtkWidget *birth_day = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_jour_spinbutton");
    GtkWidget *birth_month = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_mois_spinbutton");
    GtkWidget *birth_year = lookup_widget(window, "ft_gestion_entraineur_modifier_dnd_annee_spinbutton");
    GtkWidget *start_day = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_jour_spinbutton");
    GtkWidget *start_month = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_mois_spinbutton");
    GtkWidget *start_year = lookup_widget(window, "ft_gestion_entraineur_modifier_datedebut_annee_spinbutton");
    
    if (birth_day) updated_trainer.birth_date.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_day));
    if (birth_month) updated_trainer.birth_date.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_month));
    if (birth_year) updated_trainer.birth_date.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(birth_year));
    if (start_day) updated_trainer.start_date.day = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_day));
    if (start_month) updated_trainer.start_date.month = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_month));
    if (start_year) updated_trainer.start_date.year = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(start_year));
    
    fprintf(stderr, "Updating trainer: %s, Gender: %s, Status: %s, Specialty: %s\n", 
            trainer_id, updated_trainer.gender, updated_trainer.status, updated_trainer.specialty);
    
    if (update_trainer(trainer_list, trainer_id, &updated_trainer) == 0) {
        set_message_style(msg_label, "Entraîneur modifié avec succès!", "green");
        
        // Save trainers to file
        save_trainers_to_file(trainer_list, "trainers.txt");
        
        GtkWidget *treeview = lookup_widget(window, "ft_gestion_entraineur_dashboard_treeview");
        if (treeview) refresh_dashboard(treeview);
    } else {
        set_message_style(msg_label, "Erreur lors de la modification", "red");
    }
}

////////////////////// rechercher l'ent pour supprimer ///////////////////////
void on_ft_gestion_entraineur_supprimer_rechercher_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "DELETE: Search button clicked\n");
    
    GtkWidget *id_entry = lookup_widget(window, "ft_gestion_entraineur_supprimer_id_entry");
    GtkWidget *info_label = lookup_widget(window, "ft_gestion_entraineur_supprimer_coachinfo_label");
    GtkWidget *msg_label = lookup_widget(window, "ft_gestion_entraineur_supprimer_msg_label");
    
    if (!id_entry || !info_label) return;
    
    const char *search_id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    
    if (strlen(search_id) == 0) {
        set_message_style(msg_label, "Veuillez entrer un ID", "red");
        return;
    }
    
    // Search for trainer
    Trainer *trainer = find_trainer(trainer_list, search_id);
    
    if (!trainer) {
        set_message_style(msg_label, "Entraîneur non trouvé", "red");
        gtk_label_set_text(GTK_LABEL(info_label), "");
        return;
    }
    
    char info_text[512];
    snprintf(info_text, sizeof(info_text),
             "Voulez-vous vraiment supprimer cet entraîneur?\n\n"
             "ID: %s\nNom: %s\nGenre: %s\nSpécialité: %s\nStatut: %s",
             trainer->id, trainer->full_name, trainer->gender, trainer->specialty, trainer->status);
    
    gtk_label_set_text(GTK_LABEL(info_label), info_text);
    set_message_style(msg_label, "Entraîneur trouvé. Confirmez la suppression.", "green");
}


////////////////////// supprimer button ///////////////////////
void on_ft_gestion_entraineur_supprimer_supprimer_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "DELETE: Delete button clicked\n");
    
    GtkWidget *id_entry = lookup_widget(window, "ft_gestion_entraineur_supprimer_id_entry");
    GtkWidget *info_label = lookup_widget(window, "ft_gestion_entraineur_supprimer_coachinfo_label");
    GtkWidget *msg_label = lookup_widget(window, "ft_gestion_entraineur_supprimer_msg_label");
    
    if (!id_entry) return;
    
    const char *trainer_id = gtk_entry_get_text(GTK_ENTRY(id_entry));
    
    if (delete_trainer(trainer_list, trainer_id) == 0) {
        set_message_style(msg_label, "Entraîneur supprimé avec succès!", "green");
        if (info_label) gtk_label_set_text(GTK_LABEL(info_label), "");
        gtk_entry_set_text(GTK_ENTRY(id_entry), "");
        
        // Save trainers to file
        save_trainers_to_file(trainer_list, "trainers.txt");
        
        // Remove trainer login from login file
        remove_trainer_login(trainer_id);
        
        GtkWidget *treeview = lookup_widget(window, "ft_gestion_entraineur_dashboard_treeview");
        if (treeview) refresh_dashboard(treeview);
    } else {
        set_message_style(msg_label, "Erreur lors de la suppression", "red");
    }
}

//////////////// annuler button ////////////////////////////////////

void on_ft_gestion_entraineur_supprimer_annuler_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    fprintf(stderr, "DELETE: Cancel button clicked\n");
    clear_delete_form(window);
}

// les fonctions dashboard -- Treeview


void gender_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                          GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data) {
    // Remove all custom styling to make it basic
    g_object_set(renderer, 
                "foreground", NULL,
                "background", NULL,
                "weight", PANGO_WEIGHT_NORMAL,
                NULL);
}

/* Remove colored styling from name column */
void name_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                        GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data) {
    // Remove all custom styling to make it basic
    g_object_set(renderer, 
                "foreground", NULL,
                "background", NULL,
                "weight", PANGO_WEIGHT_NORMAL,
                NULL);
}

/* Remove colored styling from status column */
void status_cell_data_func(GtkTreeViewColumn *col, GtkCellRenderer *renderer, 
                          GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data) {
    // Remove all custom styling to make it basic
    g_object_set(renderer, 
                "foreground", NULL,
                "background", NULL,
                "weight", PANGO_WEIGHT_NORMAL,
                NULL);
}


/////////////////// dashboard ////////////////////////
void initialize_dashboard(GtkWidget *treeview) {
    if (!treeview) return;
    
 // reation dune liste contenant toutes les info dun ent
    GtkListStore *store = gtk_list_store_new(10, 
        G_TYPE_STRING, // ID
        G_TYPE_STRING, // Nom complet 
        G_TYPE_STRING, // Genre
        G_TYPE_STRING, // Phone
        G_TYPE_STRING, // mail
        G_TYPE_STRING, // Addresse postale
        G_TYPE_STRING, // date de naissance
        G_TYPE_STRING, // date debut 
        G_TYPE_STRING, // Specialité
        G_TYPE_STRING  // Statut
    );
    
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    // creer les colonnes 
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    
    // colonne ID
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "ID");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 0);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne NOM COMPLET 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Nom Complet");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 1);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne GENRE 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Genre");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 2);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne TELEPHONE 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Téléphone");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 3);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne ADRESSE MAIL
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Email");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 4);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne ADRESSE POSTALE
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Adresse");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 5);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne DATE DE NAISSANCE 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Naissance");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 6);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne DATE DE DEBUT 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Début");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 7);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne SPECIALITÉ
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Spécialité");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 8);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    // colonne STATUT 
    column = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(column, "Statut");
    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(column, renderer, TRUE);
    gtk_tree_view_column_add_attribute(column, renderer, "text", 9);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    
    refresh_dashboard(treeview);
}

void refresh_dashboard(GtkWidget *treeview) {
    if (!treeview) return;
    
    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (!model) return;
    
    GtkListStore *store = GTK_LIST_STORE(model);
    gtk_list_store_clear(store);
    
    if (!trainer_list) return;
    
    Trainer *current = trainer_list->head;
    int display_count = 0;
    
    while (current) {
        GtkTreeIter iter;
        char birth_date[20], start_date[20];
        
        // Format dates
        snprintf(birth_date, sizeof(birth_date), "%02d/%02d/%d", 
                 current->birth_date.day, current->birth_date.month, current->birth_date.year);
        snprintf(start_date, sizeof(start_date), "%02d/%02d/%d", 
                 current->start_date.day, current->start_date.month, current->start_date.year);
        
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
            0, current->id,
            1, current->full_name,
            2, current->gender,
            3, current->phone,
            4, current->email,
            5, current->address,
            6, birth_date,
            7, start_date,
            8, current->specialty,
            9, current->status,
            -1);
        
        display_count++;
        current = current->next;
    }
    
    fprintf(stderr, "Displayed %d trainers in dashboard\n", display_count);
}

/////////////////// nett tab ajouter apres enregistrement /////////////
void clear_add_form(GtkWidget *window) {
    GtkWidget *widget;
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_id_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_nomcomplet_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_telephone_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_adressemail_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_adressepostale_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_idwarning_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_ajouter_msg_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
    
    // Generate new TR ID after clearing
    generate_tr_id(window);
}


//////////////// effacer le contenu - tab modifier //////////
void clear_modify_form(GtkWidget *window) {
    GtkWidget *widget;
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_rechercher_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_id_display_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_nomcomplet_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_telephone_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_adressemail_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_adressepostale_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_modifier_msg_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
}

void clear_delete_form(GtkWidget *window) {
    GtkWidget *widget;
    
    widget = lookup_widget(window, "ft_gestion_entraineur_supprimer_id_entry");
    if (widget) gtk_entry_set_text(GTK_ENTRY(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_supprimer_coachinfo_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
    
    widget = lookup_widget(window, "ft_gestion_entraineur_supprimer_msg_label");
    if (widget) gtk_label_set_text(GTK_LABEL(widget), "");
}



/* Ajouter Tab - Entry Changes (Empty) */
void on_ft_gestion_entraineur_ajouter_nomcomplet_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_adressepostale_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_adressemail_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_telephone_entry_changed(GtkEditable *editable, gpointer user_data) {}

/* Ajouter Tab - SpinButton Changes (Empty) */
void on_ft_gestion_entraineur_ajouter_datedebut_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_datedebut_mois_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_datedebut_annee_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_dnd_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_dnd_mois_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_dnd_annee_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}

/* Ajouter Tab - Radio/Check Buttons (Empty) */
void on_ft_gestion_entraineur_ajouter_femme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_actif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_inactif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_specialite_comboboxentry_changed(GtkComboBox *combobox, gpointer user_data) {}
void on_ft_gestion_entraineur_ajouter_homme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}

/* Modifier Tab - Entry Changes (Empty) */
void on_ft_gestion_entraineur_modifier_nomcomplet_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_adressepostale_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_adressemail_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_telephone_entry_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_rechercher_entry_changed(GtkEditable *editable, gpointer user_data) {}

/* Modifier Tab - SpinButton Changes (Empty) */
void on_ft_gestion_entraineur_modifier_datedebut_jour_spinbutton_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_datedebut_mois_spinbutton_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_datedebut_annee_spinbutton_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_dnd_jour_spinbutton_change_value(GtkSpinButton *spinbutton, GtkScrollType scroll, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_dnd_mois_spinbutton_changed(GtkEditable *editable, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_dnd_annee_spinbutton_changed(GtkEditable *editable, gpointer user_data) {}

/* Modifier Tab - Radio/Check Buttons (Empty) */
void on_ft_gestion_entraineur_modifier_specialite_comboboxentry_changed(GtkComboBox *combobox, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_actif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_inactif_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_femme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}
void on_ft_gestion_entraineur_modifier_homme_radiobutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}

/* Supprimer Tab (Empty) */
void on_ft_gestion_entraineur_supprimer_id_entry_changed(GtkEditable *editable, gpointer user_data) {}

/* Login Window (Empty) */
void on_login_mpoublie_button_clicked(GtkButton *button, gpointer user_data) {}
void on_login_connexion_button_clicked(GtkButton *button, gpointer user_data) {}
void on_login_showpassword_checkbutton_toggled(GtkToggleButton *togglebutton, gpointer user_data) {}




