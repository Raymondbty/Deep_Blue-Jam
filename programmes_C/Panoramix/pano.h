/*
** EPITECH PROJECT, 2023
** PANO.h
** File description:
** .h
*/
#ifndef PANO_H
    #define PANO_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <pthread.h>
    #include <semaphore.h>
    #include <unistd.h>
    #define MAX_SLEEP_TIME 1

typedef struct {
    int num_villagers;
    int pot_capacity;
    int num_fights;
    int num_refills;
    int *villagers_fights_remaining;
    int pot_servings_remaining;
    sem_t pot_lock;
    sem_t villagers_lock;
    sem_t druid_lock;
    pthread_t *villagers_threads;
    pthread_t druid_thread;
} Game;

void cleanup_resources(void);
void initialize_mutexes(void);
void join_villagers_and_druid(void);
void initialize_villagers(void);
int validate_arguments(int argc, char **argv);
int parse_arguments(char **argv);
int error_handling(int argc, char **argv);
int main(int argc, char **argv);
void drink_potion(int id);
void *villager_func(void *arg);
/*typedef struct {
    int nb_villagers;
    int pot_size;
    int nb_fights;
    int nb_refills;
    int *villagers_fights_left;
    int pot_servings_left;
    sem_t pot_mutex;
    sem_t villagers_mutex;
    sem_t druid_mutex;
    pthread_t *villagers_threads;
    pthread_t druid_thread;
} PotionGame;*/
/*








---------------------------------------












*/
extern int nb_villagers;
extern int pot_size;
extern int nb_fights;
extern int nb_refills;
extern int *villagers_fights_left;
extern int pot_servings_left;
extern sem_t pot_mutex;
extern sem_t villagers_mutex;
extern sem_t druid_mutex;
extern pthread_t *villagers_threads;
extern pthread_t druid_thread;
#endif