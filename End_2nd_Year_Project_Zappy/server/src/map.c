/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** map.c
*/

#include "server.h"

void create_ressources(tile_t *tile)
{
    tile->ressources = malloc(sizeof(ressources_t));
    tile->ressources->nbr_food = 0;
    tile->ressources->nbr_linemate = 0;
    tile->ressources->nbr_deraumere = 0;
    tile->ressources->nbr_sibur = 0;
    tile->ressources->nbr_mendiane = 0;
    tile->ressources->nbr_phiras = 0;
    tile->ressources->nbr_thystame = 0;
    tile->nbr_player = 0;
    tile->nbr_egg = 0;
}

void add_ressources(map_t *map)
{
    map->ressources = malloc(sizeof(ressources_t));
    srand(time(NULL));
    map->ressources->nbr_food = generate_ressources(&map[0], FOOD,
    MULTIPLIER_FOOD, 0);
    map->ressources->nbr_linemate = generate_ressources(&map[0], LINEMATE ,
    MULTIPLIER_LINEMATE, 0);
    map->ressources->nbr_deraumere = generate_ressources(&map[0], DERAUMERE,
    MULTIPLIER_DERAUMERE, 0);
    map->ressources->nbr_sibur = generate_ressources(&map[0], SIBUR,
    MULTIPLIER_SIBUR, 0);
    map->ressources->nbr_mendiane = generate_ressources(&map[0], MENDIANE,
    MULTIPLIER_MENDIANE, 0);
    map->ressources->nbr_phiras = generate_ressources(&map[0], PHIRAS,
    MULTIPLIER_PHIRAS, 0);
    map->ressources->nbr_thystame = generate_ressources(&map[0], THYSTAME,
    MULTIPLIER_THYSTAME, 0);
}

map_t *create_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    if (width <= 0 || height <= 0) {
        free(map);
        return NULL;
    }
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t **) * (height + 1));
    for (int i = 0; i < height; ++i) {
        map->tiles[i] = malloc(sizeof(tile_t *) * (width + 1));
        for (int j = 0; j < width; ++j) {
            map->tiles[i][j] = malloc(sizeof(tile_t));
            create_ressources(map->tiles[i][j]);
        }
        map->tiles[i][width] = NULL;
    }
    map->tiles[height] = NULL;
    add_ressources(map);
    return map;
}

tile_t *get_tile(map_t *map, int x, int y)
{
    if (x < 0)
        x = map->width + x;
    else if (x >= map->width)
        x = x - map->width;
    if (y < 0)
        y = map->height + y;
    else if (y >= map->height)
        y = y - map->height;
    return map->tiles[y][x];
}

void destroy_map(map_t *map)
{
    for (int i = 0; i < map->height; ++i)
        free(map->tiles[i]);
    free(map->tiles);
    free(map);
}
