/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** game_time.c
*/

#include "server.h"

void time_pass(client_t *client, clock_t time_pass)
{
    client_t *tmp = client;

    for (; tmp != NULL; tmp = tmp->next) {
        pthread_mutex_lock(&tmp->client_mutex);
        if (tmp->cd_until_next_action > 0)
            tmp->cd_until_next_action -= time_pass;
        if (tmp->survive_time > 0)
            reduce_life_time(tmp, time_pass);
        pthread_mutex_unlock(&tmp->client_mutex);
    }
    return;
}

void check_nbr_time_survive(client_t *client, client_t *gui)
{
    if (client->survive_time == 0 && client->ressources.nbr_food > 0 &&
    strcmp(client->type, AI) == 0) {
        --client->ressources.nbr_food;
        client->survive_time += MULTIPLIER_TIME_UNIT;
    } else if (client->survive_time == 0 && strcmp(client->type, AI) == 0) {
        kill_client(client, gui);
    }
}
