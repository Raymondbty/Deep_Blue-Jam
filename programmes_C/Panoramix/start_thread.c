/*
** EPITECH PROJECT, 2023
** start_thread.c
** File description:
** lol
*/
#include "pano.h"

void create_thread(int id, Game *game)
{
    if (game->pot_servings_remaining > 0) {
        game->pot_servings_remaining--;
        printf("Villager %d: I need a drink... I see %d servings left.\n",
            id, game->pot_servings_remaining);
        int sleep_time = rand() % 1;
        usleep(sleep_time);
    } else {
        printf("Villager %d: Hey Pano wake up! We need more potion.\n", id);
        int sleep_time = rand() % 5;
        usleep(sleep_time);
    }
}

void launch_mutex(Game *game)
{
    printf("Druid : Ah! Yes, yes, I'm awake! Working on it! Beware I ");
    printf("can only make %d more refills after this one.\n",
    game->num_refills - 1);
}

int set_potion(Game *game)
{
    game->num_fights = game->pot_capacity;
    game->num_villagers = game->pot_servings_remaining;
    game->num_refills = game->num_refills;

    if (game->num_fights <= 0 || game->num_refills <= 0 ||
        game->pot_capacity <= 0 || game->num_villagers <= 0) {
        printf("Values must be >0.\n");
        return 84;
    }
    return 0;
}

void *start_thread_mutex(void *arg)
{
    Game *game = (Game*)arg;
    int id = *(int*)arg;

    printf("Villager %d: Going into battle!\n", id);
    while (game->num_fights > 0) {
        launch_mutex(game);
        if (game->num_refills == 0) {
            continue;
        }
        printf("Villager %d: Take that roman scum! Only %d left.\n",
            id, game->num_villagers - 1);
        game->num_villagers--;
        game->num_fights--;
    }
    printf("Villager %d: I'm going to sleep now.\n", id);
    return NULL;
}

void print_status(int *villagers_fights_remaining, int pot_servings_remaining)
{
    printf("Villagers' fights remaining:\n");
    for (int i = 0; i < 1; i++) {
        printf("Villager %d: %d\n", i, villagers_fights_remaining[i]);
    }
    printf("Pot servings remaining: %d\n", pot_servings_remaining);
}
