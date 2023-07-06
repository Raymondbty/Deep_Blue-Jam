/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** map.h
*/

#ifndef ZAPPY_MAP_H
    #define ZAPPY_MAP_H

    #include "ressources.h"
    #include <stdlib.h>
    #include <time.h>

    #define FOOD 0
    #define LINEMATE 1
    #define DERAUMERE 2
    #define SIBUR 3
    #define MENDIANE 4
    #define PHIRAS 5
    #define THYSTAME 6

    #define MULTIPLIER_FOOD 1
    #define MULTIPLIER_LINEMATE 0.3
    #define MULTIPLIER_DERAUMERE 0.15
    #define MULTIPLIER_SIBUR 0.1
    #define MULTIPLIER_MENDIANE 0.1
    #define MULTIPLIER_PHIRAS 0.08
    #define MULTIPLIER_THYSTAME 0.05

    #define NORTH 1
    #define EAST 2
    #define SOUTH 3
    #define WEST 4

    typedef struct tile_s {
        int nbr_player;
        int nbr_egg;
        ressources_t *ressources;
    } tile_t;

    typedef struct map_s {
        int width;
        int height;
        ressources_t *ressources;
        tile_t ***tiles;
    } map_t;

    /* Manage Map */

    map_t *create_map(int width, int height);
    tile_t *get_tile(map_t *map, int x, int y);
    void destroy_map(map_t *map);

    /* Generate Ressource on random point on map */

    int generate_ressources(map_t *map, int type, float freq,
    int nbr_already_set);

#endif
