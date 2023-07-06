/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** network.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

typedef struct client_s {
    std::string ip;
    int port;
    int sock;

    struct sockaddr_in serv_addr;
    fd_set readfds;

} client_t;

namespace Zappy {
    typedef struct neworkInfo_s {
        std::string ip;
        int port;
    } networkInfo_t;
}

client_t start_client(client_t client);
void inthandler(int dummy, int sockfd);
int getPort(int ac, char **av);
std::string getIp(int ac, char **av);

#define SOCKET_FAIL "\n[!] Socket creation error \n"
#define CONNECT_FAIL "\n[!] Connection Failed \n"
#define INVALID_ADDRESS "\n[!] Invalid address/ Address not supported \n"