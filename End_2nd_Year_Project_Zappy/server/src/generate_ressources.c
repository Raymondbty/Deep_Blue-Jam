/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** generate_ressources.c
*/

#include "map.h"

void set_ressources_v2(tile_t *tile, int ressource)
{
    switch (ressource) {
        case MENDIANE:
            ++tile->ressources->nbr_mendiane;
            break;
        case PHIRAS:
            ++tile->ressources->nbr_phiras;
            break;
        case THYSTAME:
            ++tile->ressources->nbr_thystame;
            break;
        default:
            break;
    }
}

void set_ressource(tile_t *tile, int ressource)
{
    switch (ressource) {
        case FOOD:
            tile->ressources->nbr_food += 1;
            break;
        case LINEMATE:
            ++tile->ressources->nbr_linemate;
            break;
        case DERAUMERE:
            ++tile->ressources->nbr_deraumere;
            break;
        case SIBUR:
            ++tile->ressources->nbr_sibur;
            break;
        default:
            set_ressources_v2(tile, ressource);
            break;
    }
}

void set_ressources_at_tile(map_t *map, int case_file, int ressources)
{
    int x = 0;
    int y = 0;

    for (; x + (map->width * y) < case_file; ++x) {
        if (x >= map->width) {
            x = x - map->width;
            ++y;
        }
    }
    if (x >= map->width) {
        x = x - map->width;
        ++y;
    }
    set_ressource(map->tiles[y][x], ressources);
}

int generate_ressources(map_t *map, int type, float freq,
int nbr_already_set)
{
    int nbr_case_to_file = (map->width * map->height) * freq;
    int case_file = 0;
    int i = nbr_already_set;

    for (; i < nbr_case_to_file; ++i) {
        case_file = rand() % (map->width * map->height);
        set_ressources_at_tile(&map[0], case_file, type);
    }
    return i;
}
