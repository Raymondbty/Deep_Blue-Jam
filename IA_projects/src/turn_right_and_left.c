/*
** EPITECH PROJECT, 2022
** tokyo_drift
** File description:
** AYayaYAayaYaaaaaaaaaaa
*/
#include "n4s.h"

int turn_right(n4s_t *n4s)
{
    size_t standart = n4s->size;
    char *lidar = (char *)malloc(standart * sizeof(char));
    int boucle = 0;

    dprintf(1, "WHEELS_DIR:-0.3\n");
    getline(&lidar, &standart, stdin);
    for (boucle = 0; n4s->input[16] < 800; boucle++) {
        dprintf(1, "GET_INFO_LIDAR\n");
        do_parse(n4s);
        wall_on_left(n4s);
    }
    dprintf(1, "WHEELS_DIR:0.0\n");
    getline(&lidar, &standart, stdin);
    dprintf(1, "CAR_FORWARD:0.4\n");
    getline(&lidar, &standart, stdin);
    return 0;
}

int turn_left(n4s_t *n4s)
{
    size_t standart = n4s->size;
    char *lidar = (char *)malloc(standart * sizeof(char));
    int boucle = 0;

    dprintf(1, "WHEELS_DIR:0.3\n");
    getline(&lidar, &standart, stdin);
    for (boucle = 0; n4s->input[16] < 800; boucle++) {
        dprintf(1, "GET_INFO_LIDAR\n");
        do_parse(n4s);
        wall_on_right(n4s);
    }
    dprintf(1, "WHEELS_DIR:0.0\n");
    getline(&lidar, &standart, stdin);
    dprintf(1, "CAR_FORWARD:0.4\n");
    getline(&lidar, &standart, stdin);
    return 0;
}

int wall_on_left(n4s_t *n4s)
{
    return 0;
}

int wall_on_right(n4s_t *n4s)
{
    return 0;
}
