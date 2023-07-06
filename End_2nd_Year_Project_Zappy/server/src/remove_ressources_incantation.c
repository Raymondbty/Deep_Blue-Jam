/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** remove_ressources_incantation.c
*/

#include "server.h"

void remove_ressources_incantation_v4(client_t *client, map_t *map)
{
    if (client->level == 7) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere
        -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_thystame -= 1;
    }
}

void remove_ressources_incantation_v3(client_t *client, map_t *map)
{
    if (client->level == 5) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere
        -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane -= 3;
    } else if (client->level == 6) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere
        -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 3;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras -= 1;
    } else
        remove_ressources_incantation_v4(client, map);
}

void remove_ressources_incantation_v2(client_t *client, map_t *map)
{
    if (client->level == 3) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras -= 2;
    } else if (client->level == 4) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere
        -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 2;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras -= 1;
    } else
        remove_ressources_incantation_v3(client, map);
}

void remove_ressources_incantation(client_t *client, map_t *map)
{
    if (client->level == 1) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
    } else if (client->level == 2) {
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere
        -= 1;
        map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur -= 1;
    } else
        remove_ressources_incantation_v2(client, map);
}
