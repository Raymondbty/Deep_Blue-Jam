/*
** EPITECH PROJECT, 2023
** zappie
** File description:
** player_lvl_up.c
*/

#include "server.h"

int check_min(int a, int b)
{
    if (a < b)
        return (a);
    return (b);
}

bool check_cond_lvl_up_v3(client_t *client, map_t *map)
{
    if (client->level == 6 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 6 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 3 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras < 1))
        return false;
    if (client->level == 7 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 6 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_thystame < 1))
        return false;
    return true;
}

bool check_cond_lvl_up_v2(client_t *client, map_t *map)
{
    if (client->level == 4 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 4 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras < 1))
        return false;
    if (client->level == 5 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 4 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_mendiane < 3))
        return false;
    return check_cond_lvl_up_v3(client, map);
}

bool check_cond_lvl_up(client_t *client, map_t *map)
{
    if (client->level == 1 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 1 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 1))
        return false;
    if (client->level == 2 &&
    (map->tiles[client->pos.y][client->pos.x]->nbr_player < 2 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_deraumere < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 1))
        return false;
    if (client->level == 3 && (
    map->tiles[client->pos.y][client->pos.x]->nbr_player < 2 ||
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_linemate < 2 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_sibur < 1 &&
    map->tiles[client->pos.y][client->pos.x]->ressources->nbr_phiras < 2))
        return false;
    return check_cond_lvl_up_v2(client, map);
}
