/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** commands.c
*/

#include "server.h"
#include "utils.h"

void check_basic_comm_if_check_team(team_t *teams_cli, server_t *server,
    client_t *client, egg_t *egg)
{
    teams_cli = get_team(client->actual_team, server->teams);
    dprintf(client->fd, "%d\n", teams_cli->nb_unused_slots);
    if (teams_cli->nbr_eggs > 0) {
        egg = get_egg_from_team(teams_cli, server->eggs);
        teams_cli->nbr_eggs--;
    }
    set_client_ressources(client);
    spawn_client(client, server->map, server, egg);
    dprintf(client->fd, "%d %d\n", server->map->height, server->map->width);
    if (egg != NULL) {
        destroy_egg(egg, server->eggs);
    }
}

void check_basic_command_v2(char **cmd, server_t *server, client_t *client)
{
    team_t *teams_cli;
    egg_t *egg = NULL;

    if (check_team(cmd, server, client) == 0) {
        check_basic_comm_if_check_team(teams_cli, server, client, egg);
        return;
    }
    dprintf(client->fd, "ko\n");
}

void check_basic_command(char **cmd, server_t *server, client_t *client)
{
    team_t *teams_cli;

    if (cmd[1] != NULL) {
        dprintf(client->fd, "ko\n");
        return;
    }
    if (strcmp(cmd[0], "GUI") == 0) {
        client->type = GUI;
        server->gui = &client[0];
        send_all_eggs_gui(server->eggs, server->gui->fd);
        send_pos_all_player(server->clients, server->gui->fd);
        dprintf(client->fd, "GUI Connected\n");
        return;
    } else if (strcmp(cmd[0], AI) == 0) {
        client->type = AI;
        dprintf(client->fd, "AI Connected\n");
        return;
    }
    check_basic_command_v2(cmd, server, client);
}
