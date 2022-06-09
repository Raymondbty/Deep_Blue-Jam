/*
** EPITECH PROJECT, 2022
** roll_back.c
** File description:
** rrrrrrrrrr
*/
#include "n4s.h"

void roll_back_left(n4s_t *n4s)
{
    size_t lidar = n4s->size;
    char *infos = (char *)malloc(lidar * sizeof(char));

    if (n4s->input[31] < 150) {
        dprintf(1, "WHEELS_DIR:0.2\n");
        getline(&infos, &lidar, stdin);
        while (n4s->input[0] < 150) {
            dprintf(1, "GET_INFO_LIDAR\n");
            do_parse(n4s);
        }
        dprintf(1, "WHEELS_DIR:0.0\n");
        getline(&infos, &lidar, stdin);
    }
}
