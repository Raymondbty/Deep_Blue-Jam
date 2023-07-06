/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** Commands.cpp
*/

#include "../includes/Network.hpp"
#include "../includes/Render.hpp"

std::vector<std::string> cutCommand(std::string command)
{
    std::vector<std::string> commandVector;
    try {
        std::stringstream ss(command);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        commandVector = std::vector<std::string>(begin, end);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        commandVector.clear();
    }
    return commandVector;
}

void broadCastThread(Zappy::GUI &gui, int id, std::string message)
{
    if (gui.getIsRunning() == false)
        return;
    gui.setBroadcastId(id);
    gui.setBroadcastMessage(message);
    // wait for 5 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    gui.setBroadcastId(-1);
    gui.setBroadcastMessage("");
}

void playerCommands(std::string cmd, std::vector<std::string> commandVector, std::string rawCommand, Zappy::GUI &gui_p)
{
    if (cmd == NEW_PLAYER) {
        std::string n = commandVector[1];
        std::string x = commandVector[2];
        std::string y = commandVector[3];
        std::string o = commandVector[4];
        std::string l = commandVector[5];
        std::string teamName = commandVector[6];

        int id = std::stoi(n);
        int xPos = std::stoi(x);
        int yPos = std::stoi(y);
        int direction = std::stoi(o);
        int level = std::stoi(l);

        gui_p.addPlayer(id, xPos, yPos, direction, level, teamName);
    }
    if (cmd == PLAYER_POSITION) {
        std::string n = commandVector[1];
        std::string x = commandVector[2];
        std::string y = commandVector[3];
        std::string o = commandVector[4];

        int id = std::stoi(n);
        int xPos = std::stoi(x);
        int yPos = std::stoi(y);
        int direction = std::stoi(o);

        gui_p.movePlayer(id, xPos, yPos, direction);
    }
    if (cmd == PLAYER_LEVEL) {
        std::string n = commandVector[1];
        std::string l = commandVector[2];

        int id = std::stoi(n);
        int level = std::stoi(l);

        gui_p.setPlayerLevel(id, level);
    }
    if (cmd == PLAYER_INVENTORY) {
        int n = std::stoi(commandVector[1]);
        int x = std::stoi(commandVector[2]);
        int y = std::stoi(commandVector[3]);
        int q0 = std::stoi(commandVector[4]);
        int q1 = std::stoi(commandVector[5]);
        int q2 = std::stoi(commandVector[6]);
        int q3 = std::stoi(commandVector[7]);
        int q4 = std::stoi(commandVector[8]);
        int q5 = std::stoi(commandVector[9]);
        int q6 = std::stoi(commandVector[10]);

        gui_p.setPlayerInventory(n, x, y, q0, q1, q2, q3, q4, q5, q6);
    }
    if (cmd == PLAYER_EJECT) {
        std::string n = commandVector[1];
        printf("Player %s has been ejected\n", n.c_str());
    }
    if (cmd == PLAYER_BROADCAST) {
        int n = std::stoi(commandVector[1]);
        // cut the first 6 characters of the string to get the message
        std::string m = rawCommand.substr(6);

        std::thread bT(broadCastThread, std::ref(gui_p), n, m);
        bT.detach();
    }
    if (cmd == PLAYER_INCANTATION_START) {
        int posX = std::stoi(commandVector[1]);
        int posY = std::stoi(commandVector[2]);
        int level = std::stoi(commandVector[3]);

        // here it's a vector of player IDs because there can be multiple players for an incantation
        std::vector<int> playerIDs;
        std::string playerList = rawCommand.substr(rawCommand.find('\n') + 1);
        size_t startPos = 0;
        size_t spacePos = playerList.find(' ');

        while (spacePos != std::string::npos) {
            std::string playerIDStr = playerList.substr(startPos, spacePos - startPos);
            int playerID = std::stoi(playerIDStr);
            playerIDs.push_back(playerID);

            startPos = spacePos + 1;
            spacePos = playerList.find(' ', startPos);
        }

        // Handle the last player ID (after the last space)
        std::string playerIDStr = playerList.substr(startPos);
        int playerID = std::stoi(playerIDStr);
        playerIDs.push_back(playerID);

        // Call playerRitualStart for each player in the list
        for (const auto& id : playerIDs) {
            gui_p.playerRitualStart(id);
        }
    }
    if (cmd == PLAYER_INCANTATION_END) {
        std::string x = commandVector[1];
        std::string y = commandVector[2];
        std::string r = commandVector[3];

        int xPos = std::stoi(x);
        int yPos = std::stoi(y);
        int result = std::stoi(r);

        gui_p.playerIncantationEnd(xPos, yPos, result);
    }
    if (cmd == PLAYER_DROP_OBJECT) {
        std::string n = commandVector[1];
        std::string i = commandVector[2];

        gui_p.playerRessourceDrop(std::stoi(n), std::stoi(i));
    }
    if (cmd == PLAYER_TAKE_OBJECT) {
        std::string n = commandVector[1];
        std::string i = commandVector[2];

        gui_p.playerRessourceTake(std::stoi(n), std::stoi(i));
    }
    if (cmd == PLAYER_DEATH) {
        std::string n = commandVector[1];
        gui_p.playerDeath(std::stoi(n));
    }
}

void mapCommands(std::string cmd, std::vector<std::string> commandVector, Zappy::GUI &gui_p)
{
    if (cmd == MAP_SIZE) {
        std::string x = commandVector[1];
        std::string y = commandVector[2];
        printf("Map Size is %s by %s\n", x.c_str(), y.c_str());
        gui_p.setMapSize(std::stoi(x), std::stoi(y));
    }
    if (cmd == TILE_CONTENT) {
        std::string x = commandVector[1];
        std::string y = commandVector[2];
        int q0 = std::stoi(commandVector[3]);
        int q1 = std::stoi(commandVector[4]);
        int q2 = std::stoi(commandVector[5]);
        int q3 = std::stoi(commandVector[6]);
        int q4 = std::stoi(commandVector[7]);
        int q5 = std::stoi(commandVector[8]);
        int q6 = std::stoi(commandVector[9]);

        gui_p.setTileContent(std::stoi(x), std::stoi(y), q0, q1, q2, q3, q4, q5, q6);
    }
    if (cmd == TEAM_NAME) {
        std::string team = commandVector[1];
        printf("Team name command: %s\n", team.c_str());
        gui_p.addTeam(team);
    }
}

void eggCommands(std::string cmd, std::vector<std::string> commandVector, Zappy::GUI &gui_p)
{
    if (cmd == PLAYER_FORK) {
        std::string n = commandVector[1];
        printf("Player fork received : %s\n", n.c_str());
    }
    if (cmd == EGG_LAY) {
        std::string e = commandVector[1];
        std::string n = commandVector[2];
        std::string x = commandVector[3];
        std::string y = commandVector[4];
        gui_p.playerEggLay(std::stoi(e), std::stoi(n), std::stoi(x), std::stoi(y));
    }
    if (cmd == EGG_CONNECT) {
        std::string e = commandVector[1];
        int eggNumber = std::stoi(e);
        gui_p.eggHatchAnimation(eggNumber);
    }
    if (cmd == EGG_DEATH) {
        std::string e = commandVector[1];
        gui_p.eggDeath(std::stoi(e));
    }
}

void serverCommands(std::string cmd, std::vector<std::string> commandVector, std::string rawCommand, Zappy::GUI &gui_p)
{
    if (cmd == TIME_UNIT) {
        std::string T = commandVector[1]; // sgt: get time value
        gui_p.getServerTimeUnit(T);
    }
    if (cmd == TIME_UNIT) {
        std::string T = commandVector[1]; // sst: modify time value
        gui_p.getServerTimeUnitChange(T);
    }
    if (cmd == GAME_OVER) {
        std::string N = commandVector[1];
    }
    if (cmd == UKN_CMD) {
        try {
            std::string N = commandVector[1];
            printf("Error: Unknown command: %s\n", N.c_str());
        } catch (std::exception& e) {
            printf("Error: Unknown command : %s\n", rawCommand.c_str());
        }
    }
}

void analyseCommand(std::string command, Zappy::GUI &gui_p)
{
    std::vector<std::string> commandVector = cutCommand(command);
    if (commandVector.empty()) {
        printf("Error cutCommand unknow command");
        return;
    }
    std::string cmd = commandVector[0];

    mapCommands(cmd, commandVector, gui_p);
    playerCommands(cmd, commandVector, command, gui_p);
    eggCommands(cmd, commandVector, gui_p);
    serverCommands(cmd, commandVector, command, gui_p);
}
