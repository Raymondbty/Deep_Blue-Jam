/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** broadcast.c
*/

#include "server.h"

int get_distance(int player1_coordinate, int player2_coordinate,
int edge_length)
{
    return ((player1_coordinate > player2_coordinate) ?
        player1_coordinate - (edge_length - player2_coordinate) :
        player2_coordinate - (edge_length - player1_coordinate));
}

char *get_closest_pos(int heigth, int width, pos_t player1, pos_t player2)
{
    char *result = "normal";
    int actual_lowest = abs(player1.x - player2.x) +
        abs(player1.y - player2.y);
    int temp = actual_lowest;

    actual_lowest = check_min(actual_lowest, abs(player1.x - player2.x) +
        get_distance(player1.y, player2.y, heigth));
    if (actual_lowest != temp)
        result = "top";
    actual_lowest = check_min(actual_lowest,
    get_distance(player1.x, player2.x, width) + abs(player1.y - player2.y));
    if (actual_lowest != temp)
        result = "left";
    temp = actual_lowest;
    actual_lowest = check_min(actual_lowest,
    get_distance(player1.x, player2.x, width) + abs(player1.y - player2.y));
    if (actual_lowest != temp)
        result = "right";
    return result;
}

char *display_broadcast(client_t *client, client_t *gui, char **command)
{
    char *str;
    int nbr_word = 0;
    int len_word = 0;

    for (; command[nbr_word] != NULL; nbr_word++)
        len_word += strlen(command[nbr_word]);
    str = malloc(sizeof(char) * (len_word + nbr_word));
    str[0] = '\0';
    for (int i = 0; command[i] != NULL; i++) {
        strcat(str, command[i]);
        if (command[i + 1] != NULL)
            strcat(str, " ");
    }
    str[strlen(str)] = '\0';
    if (gui != NULL)
        send_broadcast_gui(client, gui->fd, str);
    return str;
}

void *broadcast(void *data)
{
    content_thread_command_t *content = (content_thread_command_t *)data;
    client_t *clt = content->client;
    client_t *gui = content->gui;
    client_t *list_clients = content->list_clients;
    queue_t *queue = content->queue;
    map_t *m = content->map;
    char **command = content->command;
    char *str;
    char *closest;

    str = display_broadcast(clt, gui, command);
    for (client_t *t = list_clients; t != NULL; t = t->next)
        if (t->id != clt->id && t->orientation != 0) {
            closest = get_closest_pos(m->height, m->width, clt->pos, t->pos);
            send_broadcast(t, str, clt, closest);
        }
    send_ok_ai(clt->fd);
    free(str);
    free_word_array(command);
    return NULL;
}
