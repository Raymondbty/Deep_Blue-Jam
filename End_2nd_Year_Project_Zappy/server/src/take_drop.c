/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** take_drop.c
*/

#include "server.h"

void take_drop_food(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_food > 0) {
        client->ressources.nbr_food += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_food -= 1;
    } else if (!take_drop && client->ressources.nbr_food > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_food += 1;
        client->ressources.nbr_food -= 1;
    }
}

void take_drop_linemate(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_linemate > 0) {
        client->ressources.nbr_linemate += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
    } else if (!take_drop && client->ressources.nbr_linemate > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate += 1;
        client->ressources.nbr_linemate -= 1;
    }
}

void take_drop_deraumere(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_deraumere > 0) {
        client->ressources.nbr_deraumere += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere -=
        1;
    } else if (!take_drop && client->ressources.nbr_deraumere > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere +=
        1;
        client->ressources.nbr_deraumere -= 1;
    }
}

void take_drop_sibur(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_sibur > 0) {
        client->ressources.nbr_sibur += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 1;
    } else if (!take_drop && client->ressources.nbr_sibur > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur += 1;
        client->ressources.nbr_sibur -= 1;
    }
}

void take_drop_mendiane(client_t *client, map_t *map, bool take_drop)
{
    if (take_drop && map->tiles[client->pos.y][client->pos.x]->ressources->
    nbr_mendiane > 0) {
        client->ressources.nbr_mendiane += 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane -= 1;
    } else if (!take_drop && client->ressources.nbr_mendiane > 0) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane += 1;
        client->ressources.nbr_mendiane -= 1;
    }
}
