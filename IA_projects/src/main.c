/*
** EPITECH PROJECT, 2022
** n4s_package
** File description:
** main
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "n4s.h"

int main(void)
{
    n4s_t *n4s = malloc(sizeof(n4s_t));
    n4s->size = 32;
    size_t large = n4s->size;
    char *buffer = (char *)malloc(large * sizeof(char));

    dprintf(1, "START_SIMULATION\n");
    getline(&buffer, &large, stdin);
    dprintf(1, "CAR_FORWARD:0.4\n");
    getline(&buffer, &large, stdin);
    while (1) {
        dprintf(1, "GET_INFO_LIDAR\n");
        if (do_parse(n4s) == -1) {
            return 84;
        }
        detect_environment(n4s);
        roll_back(n4s);
    }
    return 0;
}

int detect_environment(n4s_t *n4s)
{
    char *lidar = (char *) malloc (n4s->size * sizeof(char));
    size_t large = n4s->size;

    if (n4s->input != NULL) {
        if (n4s->input[16] < 800) {
            dprintf(1, "CAR_FORWARD:0.2\n");
            getline(&lidar, &large, stdin);
            call_turn(n4s);
        }
    }
    return 0;
}

int roll_back(n4s_t *n4s)
{
    size_t lidar = n4s->size;
    char *infos = (char *)malloc(lidar * sizeof(char));
    int boucle = 0;

    if (n4s->input[0] < 150) {
        dprintf(1, "WHEELS_DIR:-0.2\n");
        getline(&infos, &lidar, stdin);
        for (boucle = 0; n4s->input[0] < 150; boucle++) {
            dprintf(1, "GET_INFO_LIDAR\n");
            do_parse(n4s);
        }
        dprintf(1, "WHEELS_DIR:0.0\n");
        getline(&infos, &lidar, stdin);
    }
    roll_back_left(n4s);
    return 0;
}

int call_turn(n4s_t *n4s)
{
    n4s->roll = 0;
    if (road_clear_or_end(n4s) != 1) {
        turn_left(n4s);
    } else {
        turn_right(n4s);
    }
    return 0;
}

int road_clear_or_end(n4s_t *n4s)
{
    int first_value = 0;
    int second_value = 4;
    int val = 8;
    int infos_lidar = 12;
    int getliner = 19;
    int closup = 23;
    int roller = 27;
    int end = 31;

    n4s->roll = (n4s->input[first_value] + n4s->input[second_value] +
n4s->input[val] + n4s->input[infos_lidar]) - (n4s->input[getliner] +
n4s->input[closup] + n4s->input[roller] + n4s->input[end]);
    if (n4s->roll < first_value) {
        return 1;
    }
    return 0;
}
