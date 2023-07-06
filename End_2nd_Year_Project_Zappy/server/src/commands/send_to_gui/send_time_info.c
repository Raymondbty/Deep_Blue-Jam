/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_time_info.c
*/

#include "server.h"

void send_time_info_gui(int fd, float time)
{
    dprintf(fd, "sgt %f\n", time);
}

void send_time_modification_gui(int fd, float time)
{
    dprintf(fd, "sst %f\n", time);
}
