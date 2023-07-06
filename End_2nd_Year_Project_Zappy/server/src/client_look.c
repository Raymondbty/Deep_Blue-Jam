/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** client_look.c
*/

#include "server.h"

void check_line(client_t *client, map_t *map, tile_t **front, int *info)
{
    for (int j = 0; j < info[0] * 2 + 1; ++j) {
        switch (client->orientation) {
            case NORTH:
                front[j + info[1]] = get_tile(map, client->pos.x - info[0] + j,
                client->pos.y - info[0]);
                break;
            case EAST:
                front[j + info[1]] = get_tile(map, client->pos.x + info[0],
                client->pos.y - info[0] + j);
                break;
            case SOUTH:
                front[j + info[1]] = get_tile(map, client->pos.x - info[0] + j,
                client->pos.y + info[0]);
                break;
            case WEST:
                front[j + info[1]] = get_tile(map, client->pos.x - info[0],
                client->pos.y - info[0] + j);
                break;
        }
    }
}

tile_t **look(client_t *client, map_t *map)
{
    tile_t **front;
    int malloc_size = 0;
    int nbr_case = 0;
    int *info = malloc(sizeof(int) * 2);

    for (int i = 0; i < client->level + 1; ++i) {
        malloc_size += i * 2 + 1;
    }
    front = malloc(sizeof(tile_t *) * (malloc_size + 1));
    for (int i = 0; i < client->level + 1; ++i) {
        info[0] = i;
        info[1] = nbr_case;
        check_line(client, map, front, info);
        nbr_case += i * 2 + 1;
    }
    front[malloc_size] = NULL;
    free(info);
    return front;
}
