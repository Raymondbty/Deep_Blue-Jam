/*
** EPITECH PROJECT, 2022
** parsing_info_lidar.c
** File description:
** lol
*/
#include "n4s.h"

int make_rays(n4s_t *n4s)
{
    int a = 0;
    int max = n4s->size;

    n4s->input = malloc(sizeof(float) * n4s->size);
    for (a = 0; a <= max - 1; a++)
        n4s->input[a] = atof(n4s->infos[a]);
    return 0;
}

char *string_free(char *str)
{
    char *string_free = malloc(sizeof(char) * 230);
    int l_string = 22;
    int b = 0;

    for (b = 0; str[l_string + 1] > 122 || str[l_string + 1] < 65; b++) {
        string_free[b] = str[l_string];
        l_string = l_string + 1;
    }
    string_free[b] = 0;
    return string_free;
}

int do_parse(n4s_t *n4s)
{
    size_t lidar = n4s->size;
    char *infos = (char *)malloc(lidar * sizeof(char));

    if (getline(&infos, &lidar, stdin) == -1) {
        return -1;
    } else if (my_strlen(infos) < 90) {
        return -1;
    }
    if (simulation_finished(infos) == 0) {
        stop_simulation(n4s);
    }
    infos = string_free(infos);
    n4s->infos = str_to_word_array(infos, ':');
    make_rays(n4s);
    return 0;
}
