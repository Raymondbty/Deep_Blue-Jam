/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_broadcast.c
*/

#include "server.h"

void send_message(char *msg, client_t *client, char *pos)
{
    char *str = malloc(sizeof(char) *
    (strlen("message X, ") + strlen(msg) + 1));

    str = strcpy(str, "message ");
    str = strcat(str, pos);
    str = strcat(str, ", ");
    str = strcat(str, msg);
    dprintf(client->fd, "%s\n", str);
    free(str);
}

char ***create_code(char *code)
{
    char ***msg = malloc(sizeof(char **) * 3);
    char **code_tab = my_str_to_word_array(code, " ");
    int y = 0;

    msg[0] = malloc(sizeof(char *) * 3);
    msg[1] = malloc(sizeof(char *) * 3);
    msg[2] = malloc(sizeof(char *) * 3);
    for (int i = 0; code_tab[i] != NULL; i++) {
        if (i % 3 == 0 && i != 0)
            y++;
        msg[y][i % 3] = strdup(code_tab[i]);
    }
    free_word_array(code_tab);
    return (msg);
}

char ***get_code(client_t *client)
{
    if (client->orientation == NORTH)
        return (create_code("2 1 8 3 0 7 4 5 6"));
    if (client->orientation == SOUTH)
        return (create_code("6 5 4 7 0 3 8 1 2"));
    if (client->orientation == EAST)
        return (create_code("4 3 2 5 0 1 6 7 8"));
    if (client->orientation == WEST)
        return (create_code("8 7 6 1 0 5 2 3 4"));
    return (NULL);
}

void destroy_code(char ***code)
{
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 3; y++)
            free(code[i][y]);
        free(code[i]);
    }
    free(code);
}
