/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** player.cpp
*/

#include "../includes/Render.hpp"
#include <thread>
#include <queue>
#include <random>
#include <fstream>

namespace Zappy
{
    std::string getRandomName()
    {
        // Open the names.json file
        std::ifstream file("names.json");
        if  (!file.is_open()) {
            std::cerr << "Failed to open names.json" << std::endl;
            return "";
        }
        // Read the file contents into a string
        std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // Parse the JSON data
        std::vector<std::string> names;
        size_t pos = 0;
        while ((pos = fileContents.find("\"", pos)) != std::string::npos) {
            size_t endPos = fileContents.find("\"", pos + 1);
            if (endPos == std::string::npos)
                break;
            std::string name = fileContents.substr(pos + 1, endPos - pos - 1);
            names.push_back(name);
            pos = endPos + 1;
        }

        // Generate a random index for the name and surname
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> nameDist(0, names.size() - 1);
        int nameIndex = nameDist(gen);

        std::string name = names[nameIndex];
        return name;
    }

    void GUI::addPlayer(int id, int x, int y, int direction, int level, std::string teamName)
    {
        printf("Adding a player with params : id = %d, x = %d, y = %d, direction = %d, level = %d, teamName = %s\n", id, x, y, direction, level, teamName.c_str());
        for (auto &team : _teams) {
            if (team.name == teamName) {
                Player player;
                player.id = id;
                player.x = x;
                player.y = y;
                player.direction = direction;
                player.level = level;
                player.teamName = teamName;
                player.playerName = getRandomName();
                team.players.push_back(player);
                // Push the adress of the player to the GUI's _players vector
                _players.push_back(&team.players.back());
            }
        }
    }

    void GUI::movePlayer(int id, int x, int y, int rotation)
    {
        printf("Moving player with id %d to x = %d, y = %d\n", id, x, y);
        setPlayerPos(id, x, y, rotation);
    }

    void GUI::rotatePlayer(int id, int direction)
    {
        for (auto &player: _players) {
            if (player->id == id) {
                player->direction = direction;
            }
        }
    }

    void posThread(GUI *gui, int id, int x, int y, int direction)
    {
        printf("Setting player's %d position\n", id);
        if (gui->getIsRunning() == false)
            return;
        for (auto &player: gui->getPlayers()) {
            if (player->id == id) {
                // if the player position isnt a round number, we round it
                if (player->x - static_cast<int>(player->x) != 0) {
                    player->x = x;
                    return;
                }
                if (player->y - static_cast<int>(player->y) != 0) {
                    player->y = y;
                    return;
                }
                int xsign = (x - player->x) < 0 ? -1 : 1;
                int ysign = (y - player->y) < 0 ? -1 : 1;
                while (player->x != x && gui->getIsRunning()) {
                    player->x += ((x - player->x) / 10);
                    if (player->x + 0.005 >= x && xsign > 0)
                        player->x = x;
                    if (player->x - 0.005 <= x && xsign < 0)
                        player->x = x;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                while (player->y != y && gui->getIsRunning()) {
                    player->y += ((y - player->y) / 10);
                    if (player->y + 0.005 >= y && ysign > 0)
                        player->y = y;
                    if (player->y - 0.005 <= y && ysign < 0)
                        player->y = y;
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
                if (direction < 0)
                    direction = player->direction;
                player->direction = direction;
            }
        }
    }

    void GUI::setPlayerPos(int id, int x, int y, int direction)
    {
        // If the player moves more than 5 tiles, we teleport him
        for (auto &player : _players) {
            if (abs(x - player->x) > 5 || abs(y - player->y) > 5) {
                player->x = x;
                player->y = y;
                player->direction = direction;
                return;
            }
        }
        std::thread t(posThread, this, id, x, y, direction);
        t.detach();
    }

    void GUI::setPlayerLevel(int id, int level)
    {
        for (auto &player: _players) {
            if (player->id == id) {
                player->level = level;
            }
        }
    }

    void GUI::setPlayerInventory(int id, int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame)
    {
        for (auto &team : _teams) {
            for (auto &player : team.players) {
                if (player.id == id) {
                    player.inventory.clear();
                    for (int i = 0; i < food; i++)
                        player.inventory.push_back(TileContent::FOOD);
                    for (int i = 0; i < linemate; i++)
                        player.inventory.push_back(TileContent::LINEMATE);
                    for (int i = 0; i < deraumere; i++)
                        player.inventory.push_back(TileContent::DERAUMERE);
                    for (int i = 0; i < sibur; i++)
                        player.inventory.push_back(TileContent::SIBUR);
                    for (int i = 0; i < mendiane; i++)
                        player.inventory.push_back(TileContent::MENDIANE);
                    for (int i = 0; i < phiras; i++)
                        player.inventory.push_back(TileContent::PHIRAS);
                    for (int i = 0; i < thystame; i++)
                        player.inventory.push_back(TileContent::THYSTAME);
                }
            }
        }
    }

    void GUI::playerRessourceDrop(int id, int ressource)
    {
        for (auto &player: _players) {
            if (player->id == id) {
                // parse the player inventory and drop the ressource at index ressource
                for (auto it = player->inventory.begin(); it != player->inventory.end(); it++) {
                    if (ressource < 0) {
                        // drop the first ressource
                        ressource = static_cast<int>(*it);
                    }
                    if (*it == ressource) {
                        player->inventory.erase(it);
                        TileContent tileContent = static_cast<TileContent>(ressource);
                        _map[player->x - 1][player->y - 1].content.push_back(tileContent);
                        break;
                    }
                }
            }
        }
    }

    void GUI::playerRessourceTake(int id, int ressource)
    {
        for (auto &player: _players) {
            if (player->id == id) {
                // parse the tile content and take the ressource at index ressource
                for (auto it = _map[player->x - 1][player->y - 1].content.begin(); it != _map[player->x - 1][player->y - 1].content.end(); it++) {
                    if (ressource < 0) {
                        // take the first ressource
                        ressource = static_cast<int>(*it);
                    }
                    if (*it == ressource) {
                        _map[player->x - 1][player->y - 1].content.erase(it);
                        player->inventory.push_back(static_cast<TileContent>(ressource));
                        break;
                    }
                }
            }
        }
    }

    void GUI::playerEggLay(int egg_id, int id, int x, int y)
    {
        for (auto &team : _teams) {
            for (auto &player : team.players) {
                if (player.id == id) {
                    Egg newEgg = {egg_id, x, y, id, &team};
                    _eggs.push_back(newEgg);
                }
            }
        }
    }

    void GUI::eggDeath(int egg_id)
    {
        for (auto it = _eggs.begin(); it != _eggs.end(); it++) {
            if (it->id == egg_id) {
                _eggs.erase(it);
                break;
            }
        }
    }

    void GUI::playerRitualStart(int id)
    {
        printf("Player %d ritual started\n", id);
        for (auto &team : _teams) {
            for (auto &player : team.players) {
                if (player.id == id) {
                    player.inIncantation = true;
                }
            }
        }
    }

    void GUI::playerRitualEnd(int id, int result)
    {
        printf("Player %d ritual ended with result %d\n", id, result);
        for (auto &team : _teams) {
            for (auto &player : team.players) {
                if (player.id == id) {
                    player.inIncantation = false;
                }
            }
        }
    }

    void GUI::playerDeath(int id)
    {
        for (auto& team : _teams) {
            for (auto& player : team.players) {
                if (player.id == id) {
                    // Remove player
                    team.players.erase(std::remove_if(team.players.begin(), team.players.end(), [id](Player &p) { return p.id == id; }), team.players.end());
                }
            }
        }
    }

    void GUI::drawPlayers(void)
    {
        // Parse the teams, draw the players contained in each team
        for (int i = 0; i < _teams.size(); i++) {
            for (int j = 0; j < _teams[i].players.size(); j++) {
                // The rotation depends on the player direction
                int rotation = 0;
                if (_teams[i].players[j].direction == NORTH)
                    rotation = 180;
                if (_teams[i].players[j].direction == EAST)
                    rotation = 90;
                if (_teams[i].players[j].direction == WEST)
                    rotation = 270;
                // The scale depends on the the player level
                float initial_scale = 0.25f;
                float scale_factor = 0.1f;
                float scale_pos = initial_scale + _teams[i].players[j].level * scale_factor;
                Vector3 scale = (Vector3){scale_pos, scale_pos, scale_pos};
                DrawModelEx(_playerModel, (Vector3){_teams[i].players[j].x * CUBESIZE - _mapX + CUBESIZE / 2.0f,
                1.5f,
                _teams[i].players[j].y * CUBESIZE - _mapY * CUBESIZE / 2.0f}, // Offsets
                (Vector3){0, 1, 0}, rotation, scale, _teams[i].color);
            }
        }
    }

    void GUI::drawEggs(void)
    {
        // Parse the teams, draw the eggs contained in each team
        if (_eggs.size() == 0)
            return;
        for (auto &egg: _eggs) {
            DrawModelEx(_models.eggModel, (Vector3){egg.x * CUBESIZE - _mapX + CUBESIZE / 2.0f,
            1.5f,
            egg.y * CUBESIZE - _mapY * CUBESIZE / 2.0f}, // Offsets
            (Vector3){0, 1, 0}, _models.rotation, _models.eggScale, egg.team->color);
        }
    }
}
