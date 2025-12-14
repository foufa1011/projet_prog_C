#ifndef TRAINERS_H
#define TRAINERS_H

#include <gtk/gtk.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct Trainer {
    char id[20];
    char full_name[100];
    char gender[10];
    char phone[20];
    char email[100];
    char address[200];
    Date birth_date;
    Date start_date;
    char specialty[50];
    char status[10];
    struct Trainer *next;
} Trainer;

typedef struct {
    Trainer *head;
    int count;
} TrainerList;

/* Trainer list management */
TrainerList* create_trainer_list();
void free_trainer_list(TrainerList *list);
int add_trainer(TrainerList *list, Trainer *trainer);
int update_trainer(TrainerList *list, const char *id, Trainer *new_data);
int delete_trainer(TrainerList *list, const char *id);
Trainer* find_trainer(TrainerList *list, const char *id);
void display_all_trainers(TrainerList *list);

/* File operations */
int save_trainers_to_file(TrainerList *list, const char *filename);
int load_trainers_from_file(TrainerList *list, const char *filename);

/* Validation functions */
int is_valid_email(const char *email);
int is_valid_phone(const char *phone);
int is_valid_date(Date date);
int is_id_unique(TrainerList *list, const char *id);

#endif

