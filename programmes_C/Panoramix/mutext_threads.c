/*
** EPITECH PROJECT, 2023
** mutext_threads.c
** File description:
** lol
*/
#include "pano.h"

void initialize_mutexes(void)
{
    sem_init(&pot_mutex, 0, 1);
    sem_init(&villagers_mutex, 0, 1);
    sem_init(&druid_mutex, 0, 1);
}

void initialize_villagers(void)
{
    villagers_fights_left = malloc(nb_villagers * sizeof(int));
    for (int i = 0; i < nb_villagers; i++) {
        villagers_fights_left[i] = nb_fights;
    }
    villagers_threads = malloc(nb_villagers * sizeof(pthread_t));
    int *villager_ids = malloc(nb_villagers * sizeof(int));
    for (int i = 0; i < nb_villagers; i++) {
        villager_ids[i] = i;
        pthread_create(&villagers_threads[i], NULL, villager_func,
    &villager_ids[i]);
    }
}

void join_villagers_and_druid(void)
{
    for (int i = 0; i < nb_villagers; i++) {
        pthread_join(villagers_threads[i], NULL);
    }
    pthread_join(druid_thread, NULL);
}

void cleanup_resources(void)
{
    sem_destroy(&pot_mutex);
    sem_destroy(&villagers_mutex);
    sem_destroy(&druid_mutex);
    free(villagers_fights_left);
    free(villagers_threads);
}