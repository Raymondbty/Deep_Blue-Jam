/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** map_interaction.c
*/

#include "server.h"

void eject_player(client_t *client, map_t *map, client_t *gui,
client_t *list_clients)
{
    client_t *tmp;

    for (int i = 1;
    i < map->tiles[client->pos.y][client->pos.x]->nbr_player; ++i) {
        tmp = find_player_on_tile(list_clients, client);
        if (client->orientation == NORTH)
            tmp->pos.y = (tmp->pos.y - 1 < 0) ? map->height - 1 :
            tmp->pos.y - 1;
        if (client->orientation == SOUTH)
            tmp->pos.y = (tmp->pos.y + 1 > map->height - 1) ? 0 :
            tmp->pos.y + 1;
        if (client->orientation == EAST)
            tmp->pos.x = (tmp->pos.x + 1 > map->width - 1) ? 0 :
            tmp->pos.x + 1;
        if (client->orientation == WEST)
            tmp->pos.x = (tmp->pos.x - 1 < 0) ? map->width - 1 :
            tmp->pos.x - 1;
        send_player_pos_gui(tmp, gui->id);
    }
}

void eject_egg(client_t *client, map_t *map, client_t *gui, egg_t *eggs)
{
    egg_t *tmp;

    for (int i = 0;
    i < map->tiles[client->pos.y][client->pos.x]->nbr_egg; ++i) {
        tmp = find_egg_on_tile(eggs, client->pos);
        if (tmp == NULL)
            return;
        send_egg_death_gui(tmp, gui->id);
        destroy_egg(tmp, eggs);
    }
}

void *eject(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *client = content->client;
    map_t *map = content->map;
    queue_t *queue = content->queue;
    egg_t *eggs = content->list_eggs;
    client_t *gui = content->gui;
    client_t *list_clients = content->list_clients;

    if (map->tiles[client->pos.y][client->pos.x]->nbr_egg > 0 ||
    map->tiles[client->pos.y][client->pos.x]->nbr_player != 1) {
        eject_player(client, map, gui, list_clients);
        eject_egg(client, map, gui, eggs);
    }
    send_ok_ai(client->fd);
    return NULL;
}
