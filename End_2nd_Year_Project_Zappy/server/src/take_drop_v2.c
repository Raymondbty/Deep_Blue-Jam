/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** take_drop_v2.c
*/

#include "server.h"

void take_drop_phiras(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_phiras > 0) {
        client->ressources.nbr_phiras += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras -= 1;
    } else if (!take_drop && client->ressources.nbr_phiras > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras += 1;
        client->ressources.nbr_phiras -= 1;
    }
}

void take_drop_thystame(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_thystame > 0) {
        client->ressources.nbr_thystame += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_thystame -= 1;
    } else if (!take_drop && client->ressources.nbr_thystame > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_thystame += 1;
        client->ressources.nbr_thystame -= 1;
    }
}
