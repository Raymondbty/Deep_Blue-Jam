/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** render.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <thread>
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "rlgl.h"

#include "Network.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Commands.hpp"

namespace Zappy {

    struct UITextures {
        Texture2D food;
        Texture2D linemate;
        Texture2D deraumere;
        Texture2D sibur;
        Texture2D mendiane;
        Texture2D phiras;
        Texture2D thystame;
    };

    struct seasonTextures {
        Texture2D spring;
        Texture2D springSide;
        Texture2D summer;
        Texture2D summerSide;
        Texture2D winter;
        Texture2D winterSide;
    };

    struct Button
    {
        Rectangle rect;
        bool hovered;
        bool clicked;
        Color color;
        const char* text;
    };

    class GUI {
        public:
            GUI();
            ~GUI() = default;

            // -----------------
            // Protocol Commands
            // -----------------
            // Map related
            void setMapSize(int x, int y);
            /**
             * @brief Set the content of a tile on the map.
             * 
             * @param x The x-coordinate of the tile.
             * @param y The y-coordinate of the tile.
             * @param food The amount of food on the tile.
             * @param linemate The amount of linemate on the tile.
             * @param deraumere The amount of deraumere on the tile.
             * @param sibur The amount of sibur on the tile.
             * @param mendiane The amount of mendiane on the tile.
             * @param phiras The amount of phiras on the tile.
             * @param thystame The amount of thystame on the tile.
             */
            void setTileContent(int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

            /**
             * @brief Add a team to the game.
             * 
             * @param teamName The name of the team to add.
             */
            void addTeam(const std::string teamName);

            /**
             * @brief Move a player to a new position on the map.
             * 
             * @param id The ID of the player.
             * @param x The new x-coordinate of the player.
             * @param y The new y-coordinate of the player.
             */
            void movePlayer(int id, int x, int y, int rotation);

            /**
             * @brief Rotate a player to a new direction.
             * 
             * @param id The ID of the player.
             * @param direction The new direction of the player.
             */
            void rotatePlayer(int id, int direction);

            /**
             * @brief Pick up resources from a tile.
             * 
             * @param id The ID of the player.
             * @param resources The vector of resources to pick up.
             */
            void pickUpResources(int id, const std::vector<TileContent>& resources);

            /**
             * @brief Add a new player to the game.
             * 
             * @param id The ID of the player.
             * @param x The initial x-coordinate of the player.
             * @param y The initial y-coordinate of the player.
             * @param direction The initial direction of the player.
             * @param level The level of the player.
             * @param teamName The name of the team the player belongs to.
             */
            void addPlayer(int id, int x, int y, int direction, int level, std::string teamName);

            /**
             * @brief Set the position and direction of a player.
             * 
             * @param id The ID of the player.
             * @param x The new x-coordinate of the player.
             * @param y The new y-coordinate of the player.
             * @param direction The new direction of the player.
             */
            void setPlayerPos(int id, int x, int y, int direction);

            /**
             * @brief Set the level of a player.
             * 
             * @param id The ID of the player.
             * @param level The new level of the player.
             */
            void setPlayerLevel(int id, int level);

            /**
             * @brief Set the inventory of a player.
             * 
             * @param id The ID of the player.
             * @param x The x-coordinate of the player's inventory.
             * @param y The y-coordinate of the player's inventory.
             * @param food The amount of food in the player's inventory.
             * @param linemate The amount of linemate in the player's inventory.
             * @param deraumere The amount of deraumere in the player's inventory.
             * @param sibur The amount of sibur in the player's inventory.
             * @param mendiane The amount of mendiane in the player's inventory.
             * @param phiras The amount of phiras in the player's inventory.
             * @param thystame The amount of thystame in the player's inventory.
             */
            void setPlayerInventory(int id, int x, int y, int food, int linemate, int deraumere, int sibur, int mendiane, int phiras, int thystame);

            /**
            * @brief Expulse a player from their current position.
            *
            * @param id The ID of the player to be expelled.
            */
            void playerExpulse(int id);
            /**
             * @brief Start an incantation at a given position and level.
             * 
             * @param x The x-coordinate of the position.
             * @param y The y-coordinate of the position.
             * @param level The level of the incantation.
             * @param id The ID of the player initiating the incantation.
             * @param ... Additional player IDs participating in the incantation.
             */
            void playerIncantationStart(int x, int y, int level, int id, ...);

            /**
             * @brief End an incantation at a given position with a result.
             * 
             * @param x The x-coordinate of the position.
             * @param y The y-coordinate of the position.
             * @param result The result of the incantation.
             */
            void playerIncantationEnd(int x, int y, int result);

            /**
             * @brief Make a player fork (create a new player).
             * 
             * @param id The ID of the player forking.
             */
            void playerFork(int id);

            /**
             * @brief Make a player drop a resource.
             * 
             * @param id The ID of the player.
             * @param resource The resource to be dropped.
             */
            void playerRessourceDrop(int id, int resource);

            /**
             * @brief Make a player take a resource.
             * 
             * @param id The ID of the player.
             * @param resource The resource to be taken.
             */
            void playerRessourceTake(int id, int resource);

            /**
             * @brief End a player's ritual with a result.
             * 
             * @param id The ID of the player performing the ritual.
             * @param result The result of the ritual.
             */
            void playerRitualEnd(int id, int result);

            /**
             * @brief Start a player's ritual.
             * 
             * @param id The ID of the player starting the ritual.
             */
            void playerRitualStart(int id);

            /**
             * @brief Handle the death of a player.
             * 
             * @param id The ID of the player who died.
             */
            void playerDeath(int id);

            /**
             * @brief Make a player lay an egg at a given position.
             * 
             * @param egg_id The ID of the egg being laid.
             * @param id The ID of the player laying the egg.
             * @param x The x-coordinate of the position.
             * @param y The y-coordinate of the position.
             */
            void playerEggLay(int egg_id, int id, int x, int y);

            /**
             * @brief Hatch an egg.
             * 
             * @param egg_id The ID of the egg to be hatched.
             */
            void eggHatch(int egg_id);

            /**
             * @brief Handle the death of an egg.
             * 
             * @param egg_id The ID of the egg that died.
             */
            void eggDeath(int egg_id);
            // Server related
            /**
            * @brief Set the time unit of the server.
            *
            * @param timeUnit The time unit value to be set.
            */
            void serverTimeUnit(int timeUnit);
            /**
             * @brief Change the time unit of the server.
             * 
             * @param timeUnit The new time unit value.
             */
            void serverTimeUnitChange(int timeUnit);

            /**
             * @brief End the game on the server with a winning team.
             * 
             * @param teamName The name of the winning team.
             */
            void serverEndGame(std::string teamName);

            /**
             * @brief Display a server message.
             * 
             * @param message The message to be displayed.
             */
            void serverMessage(std::string message);

            /**
             * @brief Handle an unknown command received from the server.
             */
            void serverUnknownCommand(void);

            /**
             * @brief Handle a command with bad parameters received from the server.
             */
            void serverBadParameters(void);
            // Raylib

            /**
            * @brief Create a camera for the GUI.
            *
            * @return The created camera.
            */
            Camera createCamera(void);
            /**
             * @brief Control the camera movement and rotation.
             * 
             * @param camera The camera to be controlled.
             */
            void cameraControl(Camera& camera);

            /**
             * @brief Create a model with the specified 3D model file and texture file.
             * 
             * @param model The file path of the 3D model.
             * @param texture The file path of the texture.
             * @return The created model.
             */
            Model createModel(std::string model, std::string texture);

            /**
             * @brief Remove an item from the specified tile.
             * 
             * @param x The x-coordinate of the tile.
             * @param y The y-coordinate of the tile.
             * @param item The item to be removed.
             */
            void removeItem(int x, int y, TileContent item);

            /**
             * @brief Draw all the models in the GUI.
             */
            void drawModels(void);

            /**
             * @brief Draw the map in the GUI.
             */
            void drawMap(void);

            /**
             * @brief Draw the eggs in the GUI.
             */
            void drawEggs(void);

            /**
             * @brief Draw the players in the GUI.
             */
            void drawPlayers(void);

            /**
             * @brief Get a vector of pointers to the players in the GUI.
             * 
             * @return A vector of pointers to the players.
             */
            std::vector<Player*> getPlayers(void) {return _players;};
            // Animations

            /**
             * @brief Perform the animation of an egg hatching.
             * 
             * @param id The ID of the egg.
             */
            void eggHatchAnimation(int id);

            /**
             * @brief Animate the models in the GUI.
             */
            void animateModels(void);

            /**
             * @brief Animate the water in the GUI.
             */
            void animateWater(void);

            /**
             * @brief Animate the players in the GUI.
             */
            void animatePlayers(void);

            /**
             * @brief Set the rotation value for the models.
             * 
             * @param rotation The rotation value to set.
             */
            void setRotation(int rotation) {_models.rotation = rotation;};

            /**
             * @brief Get the rotation value for the models.
             * 
             * @return The rotation value.
             */
            int getRotation(void) {return _models.rotation;};

            // UI
            /**
            * @brief Draw the user interface.
            */
            void drawUI(void);
            /**
             * @brief Draw the teams in the GUI.
             */
            void drawTeams(void);

            /**
             * @brief Draw the broadcast message on the GUI using the specified camera.
             * 
             * @param camera The camera to use for drawing.
             */
            void drawBroadcast(Camera camera);

            /**
             * @brief Draw the menu in the GUI.
            */
            void drawMenu(void);
            /**
             * @brief Makes menu iptions
             * 
             * @param option 
             */
            void handleMenuSelection(int option);
            /**
             * @brief show infos about
             * 
             */
            void showAbout();
            /**
             * @brief Set the Time Option from menu
             * 
             * @param timeValue 
             * @param gui_p 
             */
            void setTimeOption(int& timeValue);
            /**
             * @brief Set the broadcast ID for the player.
             * 
             * @param id The ID of the player.
             */
            void setBroadcastId(int id) {_playerBroadcast = id;};

            /**
             * @brief Set the broadcast message to be displayed on the GUI.
             * 
             * @param text The broadcast message.
             */
            void setBroadcastMessage(std::string text) {_broadcastMessage= text;};

            /**
             * @brief Perform mouse collision detection and return the result.
             * 
             * @param collision The initial collision data.
             * @return The updated collision data.
             */
            RayCollision mouseCollision(RayCollision collision);

            /**
             * @brief Draw the selected tile in the GUI.
             */
            void drawSelectedTile(void);

            /**
             * @brief Draw the inventory of the player with the specified ID at the given position.
             * 
             * @param id The ID of the player.
             * @param x The X position of the player.
             * @param y The Y position of the player.
             */
            void drawPlayerInventory(int id, int x, int y);

            // Network
            /**
            * @brief Get the client information.
            *
            * @return The client information.
            */
            client_t getClient(void) {return _client;};
            /**
             * @brief Set the client information.
             * 
             * @param client The client information to set.
             */
            void setClient(client_t client) {_client = client;};

            /**
             * @brief Send a command to the specified client.
             * 
             * @param client The client to send the command to.
             * @param command The command to send.
             */
            void sendCommand(client_t client, std::string command) {send(client.sock, command.c_str(), command.size(), 0);};

            // isRunning
            /**
            * @brief Check if the GUI is currently running.
            *
            * @return True if the GUI is running, false otherwise.
            */
            bool getIsRunning(void) {return _isRunning;};

            // Network gets
            /**
            * @brief Get the size of the map from the server.
            *
            * Sends the "msz" command to the server.
            */
            void getMapSize(void) {sendCommand(_client, "msz\n");};
            /**
             * @brief Get the content of a specific tile from the server.
             * 
             * Sends the "bct" command with the specified coordinates to the server.
             * 
             * @param x The x-coordinate of the tile.
             * @param y The y-coordinate of the tile.
             */
            void getTileContent(int x, int y) {sendCommand(_client, "bct " + std::to_string(x) + " " + std::to_string(y) + "\n");};

            /**
             * @brief Get the content of all tiles from the server.
             * 
             * Sends the "mct" command to the server.
             */
            void getAllTileContent(void) {sendCommand(_client, "mct\n");};

            /**
             * @brief Get the list of teams from the server.
             * 
             * Sends the "tna" command to the server.
             */
            void getTeams(void);

            /**
             * @brief Get the position of a player from the server.
             * 
             * Sends the "ppo" command with the specified player ID to the server.
             * 
             * @param id The ID of the player.
             */
            void getPlayerPos(int id) {sendCommand(_client, "ppo " + std::to_string(id) + "\n");};

            /**
             * @brief Get the level of a player from the server.
             * 
             * Sends the "plv" command with the specified player ID to the server.
             * 
             * @param id The ID of the player.
             */
            void getPlayerLevel(int id) {sendCommand(_client, "plv " + std::to_string(id) + "\n");};

            /**
             * @brief Get the inventory of a player from the server.
             * 
             * Sends the "pin" command with the specified player ID to the server.
             * 
             * @param id The ID of the player.
             */
            void getPlayerInventory(int id) {sendCommand(_client, "pin " + std::to_string(id) + "\n");};

            /**
             * @brief Get the time unit of the server.
             * 
             * Sends the "sst" command with the specified time value to the server.
             * 
             * @param timeValue The time value.
             */
            void getServerTimeUnit(const std::string& timeValue);

            /**
             * @brief Get the changed time unit of the server.
             * 
             * Sends the "sgt" command with the specified time value to the server.
             * 
             * @param timeValue The time value.
             */
            void getServerTimeUnitChange(const std::string& timeValue);

            /*
            * @brief Get the network information.
            * 
            * @return The network information.
            */
            void setNetworkInfo(const std::string ip, const int port) {_networkInfo.ip = ip; _networkInfo.port = port;};

            // this is confusing
            /**
            * @brief Create the models structure.
            *
            * This function creates the necessary models for rendering the game.
            */
           void createModelsStruct(void);
            /**
             * @brief Create the textures structure.
             * 
             * This function creates the necessary textures for rendering the game.
             */
            void createTexturesStruct(void);

            /**
            * @brief Create the season textures.
            * 
            * This function creates the textures for the different seasons.
            */
            void createSeasonTextures(void);

            /**
            * @brief Destroy everything.
            * 
            * This function destroys all the models and textures.
            */
            void cleanTextures(void);

            /**
             * @brief Run the game.
             * 
             * This function starts the game loop and handles the main execution of the program.
             */
            void run();

            /**

            @brief Initialize the music.
            This function initializes the audio device, loads the music stream from the file
            "assets/music/music_ori.ogg", starts playing the music stream, and sets the music volume
            based on the value stored in the member variable _volume.
            */
            void init_music(void);

            /**
            @brief Update the music.
            This function updates the music stream, checks for user interaction with the pause button
            and volume slider, and performs the corresponding actions. If the pause button is clicked,
            the music stream is paused or resumed depending on its current state. If the volume slider
            is being dragged, the music volume is adjusted based on the slider's position.
            */
            void update_music(void);

            /**
            @brief Draw the music UI elements.
            This function draws the UI elements related to the music, including the pause button,
            the text indicating the play/stop status, the volume bar, and the volume slider.
            The color of the pause button is determined based on the current state of the music stream.
            */
            void draw_music(void);

            void update_fps(void);
            void draw_fps(void);

            void draw_brightness(void);
            void update_brightness(void);

            void update_quit(void);
            void draw_quit(void);

        private:
            int _mapX;
            int _mapY;
            client_t _client;
            int timeValue = 300;
            int selectedOption;//menu options
            std::vector<std::vector<Tile>> _map;
            std::vector<std::vector<BoundingBox>> _mapBoxes;
            Vector2 _selectedTile;
            std::vector<Player*> _players;
            std::vector<Egg> _eggs;
            std::vector<Team> _teams;
            seasonTextures _seasonTextures;
            Texture2D _top;
            Texture2D _side;
            Texture2D _water;
            std::vector<Texture2D> _waterTextures;

            Model _playerModel;
            Ray _ray;
            Models _models;
            UITextures _uiTextures;
            int _playerBroadcast;
            std::string _broadcastMessage;

            bool _isRunning;
            bool _displayMenu;
            int _animationSpeed;
            unsigned int _animsCount;
            int _animFrameCounter;
            ModelAnimation *_currentAnimation;
            ModelAnimation *_sillyDance;
            ModelAnimation *_walk;
            networkInfo_t _networkInfo;
            //music
            Music _music;
            Rectangle _pauseButton = { 1110, 810, 87, 30 };
            bool _musicPaused = false;
            Rectangle _volumeBar = { 1140, 600, 30, 200 };
            Rectangle _volumeSlider = { 1140, 600, 30, 20 };
            float _volume = 0.5f;
            // fps
            int _fps = 60;
            Rectangle _fpsButton = { 1040, 810, 64, 30 };
            bool _highFPS = false;

            Rectangle _fpsBar = { 1060, 600, 30, 200 };
            Rectangle _fpsSlider = { 1060, 600, 30, 20 };
            // brightness
            Rectangle _brightnessButton = { 920, 810, 115, 30 };
            bool _brightnessToggle = false;
            Rectangle _brightnessBar = { 965, 600, 30, 200 };
            Rectangle _brightnessSlider = { 965, 600, 30, 20 };
            float _brightness = 0.5f;
            Color _darkFilter = { 0, 0, 0, 0 };

            Rectangle _quitButton = { 1100, 20, 75, 30 };

            //ModelAnimation *_incantation;        bool musicPaused = false;

    };

    #define BASE_FPS 60
    #define BASE_WIDTH 1200
    #define BASE_HEIGHT 850

    #define CUBESIZE 3
    #define INCANTATIION_FAIL 0
    #define INCANTATIION_SUCCESS 1

    #define NORTH 1
    #define EAST 2
    #define SOUTH 3
    #define WEST 4

    void DrawCubeTexture(Texture2D textureA, Texture2D textureB, Vector3 position, float width, float height, float length, Color color, bool front, bool back, bool left, bool right);

}

void analyseCommand(std::string command, Zappy::GUI &gui_p);
