/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** check_command_gui.c
*/

#include "server.h"

void launch_command_gui_v3(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 7:
            send_time_info_gui(client->fd, server->freq);
            break;
        case 8:
            server->freq = atoi(command[1]);
            send_time_modification_gui(client->fd, server->freq);
            break;
        default:
            break;
    }
}

void launch_command_gui_v2(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 4:
            send_player_pos_gui(
                get_client_name(server->clients, atoi(command[1])), client->fd);
            break;
        case 5:
            send_player_level_gui(
                get_client_name(server->clients, atoi(command[1])), client->fd);
            break;
        case 6:
            send_player_inventory_gui(
                get_client_name(server->clients, atoi(command[1])), client->fd);
            break;
        default:
            launch_command_gui_v3(command, server, client, j);
            break;
    }
}

void launch_command_gui(char **command, server_t *server, client_t *client,
int j)
{
    switch (j) {
        case 0:
            send_map_size_gui(client, server->map);
            break;
        case 1:
            send_tile_content_gui(client, server->map, atoi(command[1]),
            atoi(command[2]));
            break;
        case 2:
            send_all_map_content_gui(client, server->map);
            break;
        case 3:
            send_teams_info_gui(client, server->teams);
            break;
        default:
            launch_command_gui_v2(command, server, client, j);
            break;
    }
}

void check_command_gui(char **command, server_t *server, client_t *client)
{
    const char *commands_gui[10] = {"msz", "bct", "mct", "tna", "ppo", "plv",
    "pin", "sgt", "sst", NULL};

    for (int j = 0; commands_gui[j] != NULL; j++) {
        if (strcmp(command[0], commands_gui[j]) == 0) {
            launch_command_gui(command, server, client, j);
            return;
        }
    }
    send_unknown_command_gui(client->fd);
}
