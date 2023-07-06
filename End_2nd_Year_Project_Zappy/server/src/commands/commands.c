/*
** EPITECH PROJECT, 2022
** B-NWP-400-PAR-4-1-myteams-mathieu.nowakowski
** File description:
** commands.c
*/

#include "server.h"
#include "utils.h"

void set_client_ressources(client_t *client)
{
    client->ressources.nbr_food = 10;
    client->ressources.nbr_linemate = 0;
    client->ressources.nbr_deraumere = 0;
    client->ressources.nbr_sibur = 0;
    client->ressources.nbr_mendiane = 0;
    client->ressources.nbr_phiras = 0;
    client->ressources.nbr_thystame = 0;
}

int check_team(char **cmd, server_t *server, client_t *client)
{
    team_t *team;

    team = get_team(cmd[0], server->teams);
    if (team != NULL) {
        if (team->nb_unused_slots > 0) {
            team->nb_unused_slots--;
            team->clients[team->nb_clients] = client->id;
            team->nb_clients++;
            client->actual_team = strdup(team->name);
            client->type = AI;
            return 0;
        }
    }
    return 84;
}

void check_command_v2(char *command, server_t *server, client_t *client,
char **cmd)
{
    if (client->type != NULL && strcmp(client->type, AI) == 0 &&
    client->actual_team != NULL) {
        check_command_ai(cmd, server, client);
        return;
    }
    check_basic_command(cmd, server, client);
    free_word_array(cmd);
}

void check_command(char *command, server_t *server, client_t *client)
{
    char **cmd = my_str_to_word_array(my_str_to_word_array(command,
    "\n")[0], " ");

    if (cmd[0] == NULL)
        return;
    if (client->type != NULL && strcmp(client->type, GUI) == 0) {
        pthread_mutex_lock(&client->client_mutex);
        check_command_gui(cmd, server, client);
        pthread_mutex_unlock(&client->client_mutex);
        free_word_array(cmd);
        return;
    }
    check_command_v2(command, server, client, cmd);
}
