/*
** EPITECH PROJECT, 2023
** zappie
** File description:
** parse_flag.c
*/

#include "server.h"

server_t *error_parse(char *error, server_t *server)
{
    printf("Error: %s\n", error);
    free(server);
    return NULL;
}

void parse_flag_end(server_t *server)
{
    server->nb_teams = 0;
    for (; server->teams[server->nb_teams] != NULL; ++server->nb_teams);
    server->nb_clients = 0;
    server->clients = NULL;
    server->eggs = NULL;
}

server_t *parse_flags(char **argv)
{
    server_t *server = malloc(sizeof(server_t));

    server->port = get_flag(argv, "-p");
    if (server->port < 1024 || server->port > 65535)
        return error_parse("Error: port need to be between 1024 and 65535\n",
        server);
    server->map = create_map(get_flag(argv, "-x"), get_flag(argv, "-y"));
    if (server->map == NULL)
        return error_parse("invalid map size", server);
    server->freq = get_flag(argv, "-f");
    server->freq /= 1000;
    if (server->freq <= 0)
        server->freq = DEFAULT_FREQ;
    server->teams = get_teams_names(argv, get_flag(argv, "-c"));
    if (server->teams == NULL || server->teams[0] == NULL)
        return error_parse("Error: no teams", server);
    parse_flag_end(server);
    return (server);
}
