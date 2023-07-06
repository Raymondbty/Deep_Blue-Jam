/*
** EPITECH PROJECT, 2023
** panoramix.c
** File description:
** ils sont fous ces romains
*/
#include "pano.h"

void drink_potion(int id)
{
    sem_wait(&pot_mutex);
    if (pot_servings_left > 0) {
        pot_servings_left--;
        printf("Villager %d: I need a drink... I see %d servings left.\n",
    id, pot_servings_left);
        sem_post(&pot_mutex);
        int sleep_time = rand() % MAX_SLEEP_TIME;
        usleep(sleep_time);
    } else {
        sem_post(&pot_mutex);
        printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
        int sleep_time = rand() % MAX_SLEEP_TIME;
        usleep(sleep_time);
    }
}

void *villager_func(void *arg)
{
    int id = *(int*)arg;

    printf("Villager %d: Going into battle!\n", id);
    while (villagers_fights_left[id] > 0) {
        drink_potion(id);
        if (pot_servings_left == 0) {
            continue;
        }
        printf("Villager %d: Take that roman scum! Only %d left.\n",
    id, villagers_fights_left[id]-1);
        villagers_fights_left[id]--;
    }
    printf("Villager %d: I'm going to sleep now.\n", id);
    return NULL;
}

int parse_arguments(char **argv)
{
    nb_villagers = atoi(argv[1]);
    pot_size = atoi(argv[2]);
    nb_fights = atoi(argv[3]);
    nb_refills = atoi(argv[4]);

    if (nb_villagers <= 0 || pot_size <= 0 ||
    nb_fights <= 0 || nb_refills <= 0) {
        printf("Values must be >0.\n");
        return 84;
    }
    return 0;
}

void *druid_func(void *arg)
{
    printf("Druid : I'm ready ... but sleepy ...\n");
    while (nb_refills > 0) {
        int sleep_time = rand() % MAX_SLEEP_TIME;
        usleep(sleep_time);
        sem_wait(&druid_mutex);
        if (pot_servings_left == 0) {
    printf("Druid : Ah! Yes, yes, I'm awake! Working on it! Beware I ");
    printf("can only make %d more refills after this one.\n", nb_refills - 1);
            pot_servings_left = pot_size;
            nb_refills--;
        }
        sem_post(&druid_mutex);
    }
    printf("Druid : I'm out of viscum. I'm going back to ... zZz\n");
    return NULL;
}

int main(int argc, char **argv)
{
    int result = error_handling(argc, argv);
    set_potion(argv);

    if (result != 0) {
        return result;
    }
    initialize_mutexes();
    pot_servings_left = pot_size;
    initialize_villagers();
    pthread_create(&druid_thread, NULL, druid_func, NULL);
    join_villagers_and_druid();
    cleanup_resources();

    return 0;
}
