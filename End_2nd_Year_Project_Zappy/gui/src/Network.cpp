/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** network.cpp
*/

#include "../includes/Render.hpp"
#include "../includes/Network.hpp"

client_t start_client(client_t client)
{
    int status;

    if ((client.sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf(SOCKET_FAIL);
        exit(84);
    }
    client.serv_addr.sin_family = AF_INET;
    client.serv_addr.sin_port = htons(client.port);
    if (inet_pton(AF_INET, client.ip.c_str(), &client.serv_addr.sin_addr) <= 0) {
        printf(INVALID_ADDRESS);
        exit(84);
    }
    if ((status = connect(client.sock, (struct sockaddr*)&client.serv_addr, sizeof(client.serv_addr))) < 0) {
        printf(CONNECT_FAIL);
        exit(84);
    }

    int valread;
    char buffer[1024] = {0};
    valread = read(client.sock, buffer, 1024);
    printf("%s\n", buffer);
    send(client.sock, "GUI", 3, 0);
    valread = read(client.sock, buffer, 1024);
    printf("%s\n", buffer);
    return client;
}

std::string getIp(int ac, char **av)
{
    // Get the argument after the -h flag
    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], "-h") == 0) {
            if (i + 1 < ac)
                return av[i + 1];
        }
    }
    return "localhost";
}

int getPort(int ac, char **av)
{
    // Get the argument after the -p flag
    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], "-p") == 0) {
            if (i + 1 < ac)
                return atoi(av[i + 1]);
            else
                exit(84);
        }
    }
    return -1;
}

void Zappy::GUI::getServerTimeUnit(const std::string& timeValue)
{
    std::string command = "sgt " + timeValue + "\n";
    sendCommand(_client, command);
}

void Zappy::GUI::getServerTimeUnitChange(const std::string& timeValue)
{
    std::string command = "sst " + timeValue + "\n";
    sendCommand(_client, command);
}