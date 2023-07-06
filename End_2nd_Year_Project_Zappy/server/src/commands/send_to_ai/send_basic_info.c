/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_basic_info.c
*/

#include "server.h"

void send_ok_ai(int fd)
{
    write(fd, "ok\n", 3);
}

void send_ko_ai(int fd)
{
    write(fd, "ko\n", 3);
}
