/*
** EPITECH PROJECT, 2022
** zappie
** File description:
** send_broadcast.c
*/

#include "server.h"

void send_normal(client_t *client, char *str, client_t *sender, char ***code)
{
    if (client->pos.x > sender->pos.x && client->pos.y == sender->pos.y)
        send_message(str, client, code[1][2]);
    if (client->pos.x > sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[0][2]);
    if (client->pos.x = sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[0][1]);
    if (client->pos.x < sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[0][0]);
    if (client->pos.x < sender->pos.x && client->pos.y == sender->pos.y)
        send_message(str, client, code[1][0]);
    if (client->pos.x < sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[2][0]);
    if (client->pos.x = sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[2][1]);
    if (client->pos.x > sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[2][2]);
}

void send_top_bottom(client_t *client, char *str, client_t *sender,
    char ***code)
{
    if (client->pos.x < sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[0][2]);
    if (client->pos.x = sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[0][1]);
    if (client->pos.x > sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[0][0]);
    if (client->pos.x < sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[2][2]);
    if (client->pos.x = sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[2][1]);
    if (client->pos.x > sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[2][0]);
}

void send_right_left(client_t *client, char *str, client_t *sender,
    char ***code)
{
    if (client->pos.x < sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[2][0]);
    if (client->pos.x < sender->pos.x && client->pos.y == sender->pos.y)
        send_message(str, client, code[1][0]);
    if (client->pos.x < sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[0][0]);
    if (client->pos.x > sender->pos.x && client->pos.y < sender->pos.y)
        send_message(str, client, code[2][2]);
    if (client->pos.x > sender->pos.x && client->pos.y == sender->pos.y)
        send_message(str, client, code[1][2]);
    if (client->pos.x > sender->pos.x && client->pos.y > sender->pos.y)
        send_message(str, client, code[0][2]);
}

void send_broadcast(client_t *client, char *str, client_t *sender,
    char *where)
{
    char ***code = get_code(client);

    if (code == NULL)
        return;
    if (client->pos.x == sender->pos.x && client->pos.y == sender->pos.y) {
        send_message(str, client, "0");
        return;
    }
    if (strcmp(where, "normal") == 0)
        send_normal(client, str, sender, code);
    if (strcmp(where, "top") == 0 || strcmp(where, "bottom") == 0)
        send_top_bottom(client, str, sender, code);
    if (strcmp(where, "right") == 0 || strcmp(where, "left") == 0)
        send_right_left(client, str, sender, code);
    destroy_code(code);
}
