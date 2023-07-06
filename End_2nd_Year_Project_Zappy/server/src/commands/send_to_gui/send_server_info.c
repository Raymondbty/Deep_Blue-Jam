/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_server_info.c
*/

#include "server.h"

void send_end_game_gui(team_t *team, int fd)
{
    dprintf(fd, "seg %s\n", team->name);
}

void send_message_from_server_gui(char *msg, int fd)
{
    dprintf(fd, "smg %s\n", msg);
}

void send_unknown_command_gui(int fd)
{
    dprintf(fd, "suc\n");
}

void send_command_parameter_gui(int fd)
{
    dprintf(fd, "sbp\n");
}
