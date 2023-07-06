/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_map_info.c
*/

#include "server.h"

void send_map_size_gui(client_t *client, map_t *map)
{
    dprintf(client->fd, "msz %d %d\n", map->width, map->height);
}

void send_tile_content_gui(client_t *client, map_t *map, int x, int y)
{
    dprintf(client->fd, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
    map->tiles[y][x]->ressources->nbr_food,
    map->tiles[y][x]->ressources->nbr_linemate,
    map->tiles[y][x]->ressources->nbr_deraumere,
    map->tiles[y][x]->ressources->nbr_sibur,
    map->tiles[y][x]->ressources->nbr_mendiane,
    map->tiles[y][x]->ressources->nbr_phiras,
    map->tiles[y][x]->ressources->nbr_thystame);
}

void send_all_map_content_gui(client_t *client, map_t *map)
{
    for (int i = 0; i < map->height; ++i)
        for (int j = 0; j < map->width; ++j)
            send_tile_content_gui(client, map, j, i);
}
