/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** main.cpp
*/

#include "../includes/Render.hpp"
#include "../includes/Network.hpp"
#include <signal.h>

client_t client;
Zappy::GUI gui;

void help(void)
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
}

client_t parseArguments(int ac, char **av)
{
    client.ip = getIp(ac, av);
    client.port = getPort(ac, av);
    client.sock = socket(AF_INET, SOCK_STREAM, 0);

    return client;
}

void inthandler(int sig)
{
    gui.cleanTextures();
    close(client.sock);
    printf("\nCTRL-C Caught ! Exiting...\n");
    exit(0);
}

void cleanBuffer(char *buffer)
{
    // Check if the buffer has multiple lines, if that's the case, send the commands one by one
    std::string str(buffer);
    std::string command;
    if (str.empty())
        return;
    printf("buffer : %s\n", str.c_str());
    while (str.find('\n') != std::string::npos) {
        command = str.substr(0, str.find('\n'));
        analyseCommand(command, gui);
        str = str.substr(str.find('\n') + 1);
    }
}

void runNetwork()
{
    signal(SIGINT, inthandler);
    printf("Starting Network Thread\n");
    while (gui.getIsRunning()) {
        FD_ZERO(&client.readfds);
        FD_SET(client.sock, &client.readfds);
        select(client.sock + 1, &client.readfds, NULL, NULL, NULL);
        if (FD_ISSET(client.sock, &client.readfds)) {
            char buffer[1024] = {0};
            int valread = read(client.sock, buffer, 1024);
            if (valread == 0) {
                printf("Server disconnected\n");
                exit(0);
            }
            cleanBuffer(buffer);
        }
    }
    printf("GUI stopped running, exiting network thread.\n");
}

void runGUI()
{
    std::thread network(runNetwork);
    gui.setNetworkInfo(client.ip, client.port);
    network.detach();
    gui.getMapSize();
    printf("Getting tile contents\n");
    gui.getAllTileContent();
    printf("Got Tile contents\n");
    printf("Getting teams\n");
    gui.getTeams();
    printf("Got teams\n");
    gui.run();
}

int main(int ac, char **av)
{
    if (ac < 2 || strcmp(av[1], "-help") == 0 || strcmp(av[1], "--help") == 0) {
        help();
        return 84;
    }
    SetTraceLogLevel(LOG_NONE);
    parseArguments(ac, av);
    client = start_client(client);
    gui.setClient(client);
    runGUI();
    return 0;
}
