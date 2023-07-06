/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** find_element_on_tile.c
*/

#include "server.h"

client_t *find_player_on_tile(client_t *all_clients, client_t *client)
{
    client_t *tmp = all_clients;

    while (tmp) {
        if (tmp->pos.x == client->pos.x && tmp->pos.y == client->pos.y &&
        tmp->id != client->id)
            return (&tmp[0]);
        tmp = tmp->next;
    }
    return (NULL);
}

egg_t *find_egg_on_tile(egg_t *eggs, pos_t pos)
{
    egg_t *tmp = eggs;

    while (tmp) {
        if (tmp->pos.x == pos.x && tmp->pos.y == pos.y)
            return (&tmp[0]);
        tmp = tmp->next;
    }
    return (NULL);
}
