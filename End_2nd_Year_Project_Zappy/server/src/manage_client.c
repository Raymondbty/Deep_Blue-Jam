/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** manage_client.c
*/

#include "server.h"

client_t *get_client_name(client_t *client, int id)
{
    client_t *tmp = client;

    while (tmp != NULL) {
        if (tmp->id == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

client_t *close_client(client_t *client, int id)
{
    client_t *tmp = client->next;

    if (client->id == id) {
        close(client->fd);
        pthread_mutex_destroy(&client->client_mutex);
        pthread_mutex_destroy(&client->queue_mutex);
        if (client->tmp_queue != NULL)
            destroy_queue(client->tmp_queue, true);
        if (client->queue != NULL)
            destroy_queue(client->queue, true);
        if (client->actual_team != NULL)
            free(client->actual_team);
        free(client);
        return tmp;
    }
    client = close_client(client->next, id);
    return client;
}

void spawn_client(client_t *client, map_t *map, server_t *server, egg_t *egg)
{
    client->survive_time = 0;
    client->orientation = rand() % 4 + 1;
    if (egg == NULL) {
        client->pos.x = rand() % map->width;
        client->pos.y = rand() % map->height;
        if (server->gui != NULL)
            send_connection_player_gui(client, server->gui->fd);
    } else {
        client->pos.x = egg->pos.x;
        client->pos.y = egg->pos.y;
        if (server->gui != NULL)
            send_player_connect_to_egg_gui(egg, server->gui->fd);
    }
    map->tiles[client->pos.y][client->pos.x]->nbr_player++;
}

void kill_client(client_t *client, client_t *gui)
{
    if (gui != NULL)
        send_player_death_gui(client, gui->fd);
    send_player_death_ai(client);
    client->actual_team = NULL;
    client->level = 1;
    client->name = "Anonymous";
    client->ressources.nbr_food = 10;
    client->ressources.nbr_linemate = 0;
    client->ressources.nbr_deraumere = 0;
    client->ressources.nbr_sibur = 0;
    client->ressources.nbr_mendiane = 0;
    client->ressources.nbr_phiras = 0;
    client->ressources.nbr_thystame = 0;
    client->survive_time = -1;
}

void reduce_life_time(client_t *client, int time)
{
    if (client->survive_time - time < 0 && client->ressources.nbr_food > 0) {
        client->ressources.nbr_food -= 1;
        client->survive_time = MULTIPLIER_TIME_UNIT + client->survive_time
        - time;
    } else if (client->survive_time - time < 0 &&
    client->ressources.nbr_food == 0) {
        client->survive_time = 0;
    } else
        client->survive_time -= time;
}
