#include "trainers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/////////////////liste entraineurs/////////////////////////

TrainerList* create_trainer_list() {
    TrainerList *list = malloc(sizeof(TrainerList));
    if (list) {
        list->head = NULL;
        list->count = 0;
    }
    return list;
}
//////////////////retirer ent dune liste ////////////////////////////

void free_trainer_list(TrainerList *list) {
    if (!list) return;
    
    Trainer *current = list->head;
    while (current) {
        Trainer *next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

///////////////////// ajouter entraineur //////////////////////////////
int add_trainer(TrainerList *list, Trainer *trainer) {
    if (!list || !trainer) return -1;
    
    if (!is_id_unique(list, trainer->id)) {
        return -2;
    }
    
    Trainer *new_trainer = malloc(sizeof(Trainer));
    if (!new_trainer) return -1;
    
    memcpy(new_trainer, trainer, sizeof(Trainer));
    new_trainer->next = list->head;
    list->head = new_trainer;
    list->count++;
    
    return 0;
}

///////////////////////// modifier entraineur ////////////////////
int update_trainer(TrainerList *list, const char *id, Trainer *new_data) {
    if (!list || !id || !new_data) return -1;
    
    Trainer *current = list->head;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            strcpy(current->full_name, new_data->full_name);
            strcpy(current->phone, new_data->phone);
            strcpy(current->email, new_data->email);
            strcpy(current->address, new_data->address);
            strcpy(current->gender, new_data->gender);
            memcpy(&current->birth_date, &new_data->birth_date, sizeof(Date));
            strcpy(current->specialty, new_data->specialty);
            strcpy(current->status, new_data->status);
            memcpy(&current->start_date, &new_data->start_date, sizeof(Date));
            return 0;
        }
        current = current->next;
    }
    return -1;
}


///////////////////////// supprimer entraineur /////////////////////////////
int delete_trainer(TrainerList *list, const char *id) {
    if (!list || !id) return -1;
    
    Trainer *current = list->head;
    Trainer *prev = NULL;
    
    while (current) {
        if (strcmp(current->id, id) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            free(current);
            list->count--;
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}



////////////////////// rechercher ///////////////////////////
Trainer* find_trainer(TrainerList *list, const char *id) {
    if (!list || !id) return NULL;
    
    Trainer *current = list->head;
    while (current) {
        if (strcmp(current->id, id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


//////////////////////// afficher entraineur //////////////////////////
void display_all_trainers(TrainerList *list) {
    if (!list) return;
    
    Trainer *current = list->head;
    while (current) {
        printf("ID: %s, Name: %s, Specialty: %s, Status: %s\n", 
               current->id, current->full_name, current->specialty, current->status);
        current = current->next;
    }
}


////////////////////// sauvegarder fichier ///////////////////////////////
int save_trainers_to_file(TrainerList *list, const char *filename) {
    if (!list || !filename) return -1;
    
    FILE *file = fopen(filename, "w");
    if (!file) return -1;
    
    Trainer *current = list->head;
    while (current) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%d/%d/%d,%d/%d/%d,%s,%s\n",
                current->id,
                current->full_name,
                current->gender,
                current->phone,
                current->email,
                current->address,
                current->birth_date.day, current->birth_date.month, current->birth_date.year,
                current->start_date.day, current->start_date.month, current->start_date.year,
                current->specialty,
                current->status);
        current = current->next;
    }
    
    fclose(file);
    return 0;
}

////////////////////////// import ///////////////////////////////////////////
int load_trainers_from_file(TrainerList *list, const char *filename) {
 if (!list || !filename) return -1;

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file %s\n", filename);
        return -1;
    }

    char line[512];
    int loaded_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Remove newline and trim whitespace
        line[strcspn(line, "\n")] = 0;

        // Skip empty lines or lines that are too short
        if (strlen(line) < 5) { // At least "1,a,b" etc.
            continue;
        }

        Trainer trainer = {0};
        char *token;
        int field = 0;

        token = strtok(line, ",");
        while (token && field < 10) {
            switch (field) {
                case 0: strcpy(trainer.id, token); break;
                case 1: strcpy(trainer.full_name, token); break;
                case 2: strcpy(trainer.gender, token); break;
                case 3: strcpy(trainer.phone, token); break;
                case 4: strcpy(trainer.email, token); break;
                case 5: strcpy(trainer.address, token); break;
                case 6: 
                    if (sscanf(token, "%d/%d/%d", &trainer.birth_date.day, &trainer.birth_date.month, &trainer.birth_date.year) != 3) {
                        fprintf(stderr, "Warning: Invalid birth date format: %s\n", token);
                    }
                    break;
                case 7: 
                    if (sscanf(token, "%d/%d/%d", &trainer.start_date.day, &trainer.start_date.month, &trainer.start_date.year) != 3) {
                        fprintf(stderr, "Warning: Invalid start date format: %s\n", token);
                    }
                    break;
                case 8: strcpy(trainer.specialty, token); break;
                case 9: strcpy(trainer.status, token); break;
            }
            token = strtok(NULL, ",");
            field++;
        }

        // Only add if we got all 10 fields
        if (field == 10) {
            trainer.next = NULL;
            if (add_trainer(list, &trainer) == 0) {
                loaded_count++;
                fprintf(stderr, "✓ Loaded trainer: %s - %s - %s\n", trainer.id, trainer.full_name, trainer.specialty);
            } else {
                fprintf(stderr, "✗ Failed to add trainer (duplicate ID?): %s\n", trainer.id);
            }
        } else {
            fprintf(stderr, "✗ Incomplete trainer data (got %d fields, expected 10): %s\n", field, line);
        }
    }

    fclose(file);
    fprintf(stderr, "=== Total trainers loaded: %d ===\n", loaded_count);
    return (loaded_count > 0) ? 0 : -1;
}




////////////////////// verif adresse mail ////////////////////////
int is_valid_email(const char *email) {
    if (!email || strlen(email) == 0) return 0;
    return strchr(email, '@') != NULL;
}

 
////////////////// verif num tel 8 chiifres //////////////////////
int is_valid_phone(const char *phone) {
    if (!phone) return 0;
    int digit_count = 0;
    for (int i = 0; phone[i]; i++) {
        if (isdigit(phone[i])) digit_count++;
    }
    return (digit_count >= 8);
}



///////////////////////// verif date ///////////////////////////////
int is_valid_date(Date date) {
    if (date.year < 1900 || date.year > 2100) return 0;
    if (date.month < 1 || date.month > 12) return 0;
    if (date.day < 1 || date.day > 31) return 0;
    return 1;
}


/////////////////// verif id existant /////////////////////////////
int is_id_unique(TrainerList *list, const char *id) {
    return (find_trainer(list, id) == NULL);
}


//////////////////// load specialties /////////////////////////////
void load_specialties(GtkComboBox *combo) {
    GtkListStore *store;
    GtkTreeIter iter;
    
    store = gtk_list_store_new(1, G_TYPE_STRING);
    
    const char *specialties[] = {
        "Fitness", "Yoga", "Pilates", "CrossFit", "Boxe",
        "Natation", "Cardio", "Musculation", "Dance", "Arts Martiaux",
        NULL
    };
    
    for (int i = 0; specialties[i]; i++) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, specialties[i], -1);
    }
    
    gtk_combo_box_set_model(combo, GTK_TREE_MODEL(store));
    g_object_unref(store);
    
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo), renderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo), renderer, "text", 0, NULL);
}

