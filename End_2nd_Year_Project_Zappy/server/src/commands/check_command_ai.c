/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** check_command_ai.c
*/

#include "server.h"

void check_command_ai(char **command, server_t *server, client_t *client)
{
    const char *commands[13] = {"Forward", "Right", "Left", "Look",
    "Inventory", "Broadcast", "Connect_nbr", "Fork", "Eject",
    "Take", "Set", "Incantation", NULL};

    for (int i = 0; commands[i] != NULL; ++i)
        if (strcmp(command[0], commands[i]) == 0) {
            pthread_mutex_lock(&client->queue_mutex);
            launch_command_ai(command, server, client, i);
            pthread_mutex_unlock(&client->queue_mutex);
            free_word_array(command);
            return;
        }
}
