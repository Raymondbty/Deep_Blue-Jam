/*
** EPITECH PROJECT, 2022
** end_simulation.c
** File description:
** boom
*/
#include "n4s.h"

static void strcmp_end_message(char *infos, char *phrase, counter_t *counters)
{
    while (infos[counters->k] && phrase[counters->j]) {
        if (infos[counters->k] != phrase[counters->j]) {
            break;
        }
        ++counters->k;
        ++counters->j;
    }
}

static int is_simulation_finished(char *infos, char *phrase,
                                counter_t *counters)
{
    if (infos[counters->i] == phrase[counters->j]) {
        counters->k = counters->i;
        counters->j = 0;
        strcmp_end_message(infos, phrase, counters);
        if (!phrase[counters->j]) {
            return 0;
        }
    }
    return (1);
}

int simulation_finished(char *infos)
{
    char msg_return[] = "Track Cleared";
    int a = 0;
    int b = 0;
    int c = 0;

    for (a = 0; infos[a]; a++) {
        if (infos[a] == msg_return[b]) {
            for (c = a, b = 0; infos[c] && msg_return[b]; b++, c++)
                if (infos[c] != msg_return[b])
                    break;
            if (!msg_return[b]) {
                return 0;
            }
        }
    }
    return 1;
}

int stop_simulation(n4s_t *n4s)
{
    size_t alloc_memory = n4s->size;
    char *lidar = (char *) malloc (alloc_memory * sizeof(char));
    int limitation = 0;
    int maximum = 32;
    int boucle = 0;

    for (boucle = 0; limitation <= maximum; boucle++) {
        if (n4s->input[limitation] > 2500)
            return 0;
        limitation = limitation + 1;
    }
    dprintf(1, "WHEELS_DIR:0.0\n");
    getline(&lidar, &alloc_memory, stdin);
    dprintf(1, "STOP_SIMULATION\n");
    getline(&lidar, &alloc_memory, stdin);
    return 0;
}
