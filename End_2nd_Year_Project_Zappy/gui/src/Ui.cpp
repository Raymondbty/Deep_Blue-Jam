/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** ui.cpp
*/

#include "../includes/Render.hpp"
#include <cmath>

namespace Zappy {

    void GUI::drawUI(void)
    {
        DrawFPS(1120, 10);
        DrawText("Press ESC to quit", 1010, 30, 20, GRAY);
        drawTeams();
        if (_selectedTile.x != -1 && _selectedTile.y != -1)
            drawSelectedTile();
    }

    void GUI::handleMenuSelection(int selectedOption)
    {
        switch (selectedOption)
        {
            case 1:
                // Resume game -> TAB
                break;
            case 2:
                showAbout();
                break;
            case 3:
                // Exit -> do escape
                break;
            case 4:
                _top = _seasonTextures.spring;
                _side = _seasonTextures.springSide;
                break;
            case 5:
                _top = _seasonTextures.winter;
                _side = _seasonTextures.winterSide;
                break;
            case 6:
                _top = _seasonTextures.summer;
                _side = _seasonTextures.summerSide;
                break;
            case 8:
                {
                    // Perform action for "Set Time" button
                    timeValue += 10;
                    if (timeValue > 600)
                        timeValue = 100;
                    std::string timeStr = std::to_string(timeValue);
                   // getServerTimeUnitChange(timeStr);// segfault here !!!
                }
                break;
            case 9:
                break;
            default:
                break;
        }
    }

    void GUI::showAbout()
    {
        int selectedOption = 0;
        bool aboutActive = true;

        while (!WindowShouldClose() && !(IsKeyPressed(KEY_BACKSPACE) && aboutActive))
        {
            BeginDrawing();

            if (aboutActive)
                ClearBackground(RAYWHITE);

            if (IsKeyPressed(KEY_BACKSPACE))
                aboutActive = false;

            if (aboutActive)
            {
                DrawText("Zappy Command List", 20, 20, 30, BLACK);
                DrawText("Press Backspace to go back to the menu", 20, 50, 20, BLACK);
                DrawText("Zappy Commands:", 20, 100, 25, BLACK);
                DrawText("1. " MAP_SIZE " - Get the map size", 40, 130, 20, BLACK);
                DrawText("2. " TILE_CONTENT " - Get the content of a tile", 40, 160, 20, BLACK);
                DrawText("3. " TEAM_NAME " - Get the team names", 40, 190, 20, BLACK);
                DrawText("4. " NEW_PLAYER " - New player connected", 40, 220, 20, BLACK);
                DrawText("5. " PLAYER_POSITION " - Get player position", 40, 250, 20, BLACK);
                DrawText("6. " PLAYER_LEVEL " - Get player level", 40, 280, 20, BLACK);
                DrawText("7. " PLAYER_INVENTORY " - Get player inventory", 40, 310, 20, BLACK);
                DrawText("8. " PLAYER_EJECT " - Player ejected", 40, 340, 20, BLACK);
                DrawText("9. " PLAYER_BROADCAST " - Player broadcast", 40, 370, 20, BLACK);
                DrawText("10. " PLAYER_DEATH " - Player death", 40, 400, 20, BLACK);
                DrawText("11. " PLAYER_TAKE_OBJECT " - Player takes object", 40, 430, 20, BLACK);
                DrawText("12. " PLAYER_DROP_OBJECT " - Player drops object", 40, 460, 20, BLACK);
                DrawText("13. " PLAYER_INCANTATION_START " - Player incantation start", 40, 490, 20, BLACK);
                DrawText("14. " PLAYER_INCANTATION_END " - Player incantation end", 40, 520, 20, BLACK);
                DrawText("15. " EGG_LAY " - Egg laid", 40, 550, 20, BLACK);
                DrawText("16. " PLAYER_FORK " - Player forks", 40, 580, 20, BLACK);
                DrawText("17. " EGG_CONNECT " - Egg connected", 40, 610, 20, BLACK);
                DrawText("18. " EGG_DEATH " - Egg death", 40, 640, 20, BLACK);
                DrawText("19. " TIME_UNIT " - Get the time unit", 40, 670, 20, BLACK);
                DrawText("20. " TIME_UNIT_MODIFICATION " - Modify the time unit", 40, 700, 20, BLACK);
                DrawText("21. " GAME_OVER " - Game over", 40, 730, 20, BLACK);
                DrawText("22. " SERVER_MSG " - Server message", 40, 760, 20, BLACK);
                DrawText("23. " UKN_CMD " - Unknown command", 40, 790, 20, BLACK);
                DrawText("Additional Controls:", 550, 100, 25, BLACK);
                DrawText("Z Q S D: Movement", 570, 130, 20, BLACK);
                DrawText("A/E: Camera Rotation", 570, 160, 20, BLACK);
                DrawText("Arrow Keys: Camera X/Y", 570, 190, 20, BLACK);
                DrawText("I J L: Change Season", 570, 220, 20, BLACK);
            }

            EndDrawing();
        }
    }

    bool isButtonPressed(Button button)
    {
        return button.clicked;
    }

    void updateButtonState(Button& button)
    {
        bool wasClicked = button.clicked;
        bool wasHovered = button.hovered;

        button.hovered = CheckCollisionPointRec(GetMousePosition(), button.rect);
        button.clicked = button.hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

        if (wasClicked && !button.clicked)
            button.clicked = button.hovered;
        else if (!wasClicked && button.clicked && !button.hovered)
            button.clicked = false;

        if (!button.hovered && !button.clicked)
            button.color = DARKGRAY;
    }

    void drawButton(Button button, int fontSize)
    {
        Color buttonColor = button.color;

        if (button.clicked)
            buttonColor = button.hovered ? GRAY : button.color;
        else if (button.hovered)
            buttonColor = LIGHTGRAY;

        DrawRectangleRec(button.rect, buttonColor);
        DrawText(button.text, button.rect.x + 10, button.rect.y + 5, fontSize, button.clicked ? BLACK : WHITE);
    }

    Button createButton(float x, float y, const char* text, int fontSize, Color buttonColor)
    {
        Button button;
        button.rect = { x, y, 0, 0 };
        button.hovered = false;
        button.clicked = false;
        button.color = buttonColor; // Set the color passed as a parameter
        button.text = text;

        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, fontSize, 1);
        button.rect.width = textSize.x + 20;
        button.rect.height = textSize.y + 10;

        return button;
    }

    void GUI::drawMenu()
    {
        if (!_displayMenu)
            return;

        const int menuWidth = 400;
        const int menuItemHeight = 30;
        const int verticalSpacing = 30;

        // Calculate the center coordinates
        const int centerX = GetScreenWidth() / 2;
        const int centerY = GetScreenHeight() / 2;

        // Calculate the top position for the menu
        const int menuTop = centerY - (menuItemHeight * 9 + verticalSpacing * 8) / 2;

        int zappyX = centerX - MeasureText("Zappy", 30) / 2;
        int adjustedX = zappyX - 30;

        Button resumeGameButton = createButton(adjustedX, menuTop + 200, "2. Resume Game : press TAB", 20, WHITE);
        Button aboutButton = createButton(adjustedX, menuTop + 250, "3. About", 20, WHITE);
        Button exitButton = createButton(adjustedX, menuTop + 300, "4. Exit : press ESCAPE", 20, WHITE);
        Button setTimeButton = createButton(adjustedX, menuTop + 70, "1. Set Time", 20, WHITE);
        Button springButton = createButton(adjustedX + 15, menuTop + 470, "5. Spring", 20, GREEN);
        Button winterButton = createButton(adjustedX + 15, menuTop + 520, "6. Winter", 20, BLUE);
        Button summerButton = createButton(adjustedX + 15, menuTop + 570, "7. Summer", 20, YELLOW);

        // Draw background panel
        DrawRectangle(10, 10, 1180, 830, Color{ 200, 200, 200, 220 });
        // Draw title
        DrawText("Zappy", zappyX, menuTop - 40, 30, BLACK);

        // Draw parameters section
        DrawText("Parameters:", adjustedX, menuTop + 20, 25, BLACK);

        updateButtonState(setTimeButton);
        drawButton(setTimeButton, 20);

        // Draw menu options section
        DrawText("Menu Options:", adjustedX, menuTop + 150, 25, BLACK);

        updateButtonState(resumeGameButton);
        updateButtonState(aboutButton);
        updateButtonState(exitButton);

        drawButton(resumeGameButton, 20);
        drawButton(aboutButton, 20);
        drawButton(exitButton, 20);

        // Draw text
        DrawText("Seasons:", adjustedX + 15, menuTop + 420, 25, BLACK);
        DrawText("IP:", 40, 40, 20, BLACK);
        DrawText("Port:", 40, 60, 20, BLACK);
        DrawText(_networkInfo.ip.c_str(), 100, 40, 20, BLACK);
        DrawText(std::to_string(_networkInfo.port).c_str(), 100, 60, 20, BLACK);
        DrawText(std::to_string(timeValue).c_str(), adjustedX + 200, menuTop + 70, 20, BLACK);

        // Draw buttons for seasons
        updateButtonState(springButton);
        updateButtonState(winterButton);
        updateButtonState(summerButton);

        drawButton(springButton, 20);
        drawButton(winterButton, 20);
        drawButton(summerButton, 20);
        //music
        update_music();
        draw_music();
        update_fps();
        draw_fps();
        update_brightness();
        draw_brightness();
        update_quit();
        draw_quit();
        // Handle button press events
        if (isButtonPressed(resumeGameButton))
            handleMenuSelection(1);
        else if (isButtonPressed(aboutButton))
            handleMenuSelection(2);
        else if (isButtonPressed(exitButton))
            handleMenuSelection(3);
        else if (isButtonPressed(springButton))
            handleMenuSelection(4);
        else if (isButtonPressed(winterButton))
            handleMenuSelection(5);
        else if (isButtonPressed(summerButton))
            handleMenuSelection(6);
        else if (isButtonPressed(setTimeButton))
            handleMenuSelection(8);
    }

    void GUI::drawTeams(void)
    {
        int i = 0;
        int j = 0;
        int x = 10;
        int y = 10;
        int spacing = 235;
        std::string teamName;
        std::string playerNameBis;

        for (auto team : _teams) {
            j = 0;
            unsigned char r = team.color.r - 20;
            unsigned char g = team.color.g - 20;
            unsigned char b = team.color.b - 20;
            Color darkerTeamColor = (Color){r, g, b, 255};
            teamName = "Team " + team.name;
            // Draw rectangles
            DrawRectangle(x + i * spacing - 5, y - 5, 230 , 30 + team.players.size() * 30 + 5, darkerTeamColor);
            DrawRectangle(x + i * spacing, y, 220, 20 + team.players.size() * 30 + 5, team.color);
            // Draw text
            DrawText(teamName.c_str(), x + i * spacing + 5, y + 5, 20, BLACK);
            for (auto player : team.players) {
                playerNameBis = std::to_string(player.id) + " : " + player.playerName + " [LVL " + std::to_string(player.level) + "]";
                DrawText(playerNameBis.c_str(), x  + i * spacing + 10, y + 30 + j * 30, 20, BLACK);
                j++;
            }
            i++;
        }
    }

    std::string enumToString(int item)
    {
        switch (item) {
            case 0:
                return "Food";
            case 1:
                return "Linemate";
            case 2:
                return "Deraumere";
            case 3:
                return "Sibur";
            case 4:
                return "Mendiane";
            case 5:
                return "Phiras";
            case 6:
                return "Thystame";
            default:
                return "";
        }
    }

    void GUI::drawPlayerInventory(int id, int x, int y)
    {
        int i = 0;
        std::string inventory = "";
        std::string playerId = "Player " + std::to_string(id);
        std::string playerLevel = "Level : ";
        std::string team_str;
        Color teamColorBis;

        for (auto &team: _teams)
            for (auto &player: team.players) {
                if (id == player.id) {
                    team_str = team.name;
                    teamColorBis = Color{static_cast<unsigned char>(team.color.r - 20), static_cast<unsigned char>(team.color.g - 20), static_cast<unsigned char>(team.color.b - 20), 255};

                    for (auto item: player.inventory) {
                        if (i != 0)
                            inventory += ", ";
                        inventory += enumToString(static_cast<int>(item));
                        i++;
                    }
                    playerLevel += std::to_string(player.level);
                    DrawRectangle(x, y, (playerId.length() * 16.0f) + (inventory.length() * 9.0f) + 5, 105, teamColorBis);
                    DrawRectangle(x + 5, y + 5, (playerId.length() * 16.0f) + (inventory.length() * 9.0f) - 5, 95, team.color);
                    DrawText(playerId.c_str(), x + 15, y + 15, 25, BLACK);
                    DrawText(playerLevel.c_str(), x + 15, y + 48, 20, BLACK);
                    DrawText(inventory.c_str(), x + 15, y + 75, 20, BLACK);
                }
        }
    }

    void GUI::drawSelectedTile(void)
    {
        // Draw a rectangle at the bottom left corner of the screen and display the content of the selected tile
        std::string tilePosition = "Tile (" + std::to_string(static_cast<int>(_selectedTile.x)) + ", " + std::to_string(static_cast<int>(_selectedTile.y)) + ")";
        std::string tileContent = "Content : ";
        std::string players = "";
        std::string eggs = "";
        int i = 0;
        int food = 0;
        int linemate = 0;
        int deraumere = 0;
        int sibur = 0;
        int mendiane = 0;
        int phiras = 0;
        int thystame = 0;

        if (_selectedTile.x >= 0 && _selectedTile.y >= 0) {
            for (auto content : _map[_selectedTile.x][_selectedTile.y].content) {
                switch (content) {
                    case FOOD:
                        food++;
                        break;
                    case LINEMATE:
                        linemate++;
                        break;
                    case DERAUMERE:
                        deraumere++;
                        break;
                    case SIBUR:
                        sibur++;
                        break;
                    case MENDIANE:
                        mendiane++;
                        break;
                    case PHIRAS:
                        phiras++;
                        break;
                    case THYSTAME:
                        thystame++;
                        break;
                }
                i++;
            }
            for (auto &egg: _eggs)
                if (egg.x == _selectedTile.x && egg.y == _selectedTile.y) {
                    eggs += "Egg N°";
                    eggs += std::to_string(egg.id) + " ";
                }
            DrawRectangle(10, 720, 1185, 125, (Color){0, 130, 130, 165});
            DrawRectangle(15, 725, 1175, 115, (Color){0, 180, 180, 165});
            DrawText(tilePosition.c_str(), 20, 730, 30, BLACK);

            DrawTexture(_uiTextures.food,      20,  760, WHITE);
            DrawText(std::to_string(food).c_str(),  90,  790, 40, BLACK);
            DrawTexture(_uiTextures.linemate,  180, 760, WHITE);
            DrawText(std::to_string(linemate).c_str(),  250, 790, 40, BLACK);
            DrawTexture(_uiTextures.deraumere, 340, 760, WHITE);
            DrawText(std::to_string(deraumere).c_str(),  410, 790, 40, BLACK);
            DrawTexture(_uiTextures.sibur,     500, 760, WHITE);
            DrawText(std::to_string(sibur).c_str(),  570, 790, 40, BLACK);
            DrawTexture(_uiTextures.mendiane,  660, 760, WHITE);
            DrawText(std::to_string(mendiane).c_str(),  730, 790, 40, BLACK);
            DrawTexture(_uiTextures.phiras,    820, 760, WHITE);
            DrawText(std::to_string(phiras).c_str(),  890, 790, 40, BLACK);
            DrawTexture(_uiTextures.thystame,  980, 760, WHITE);
            DrawText(std::to_string(thystame).c_str(),  1050, 790, 40, BLACK);
            DrawText(eggs.c_str(), 20, 820, 20, BLACK);
            for (auto &player: _players) {
                if (player->x == _selectedTile.x && player->y == _selectedTile.y) {
                    drawPlayerInventory(player->id, 10, 600);
                }
            }
        }
    }

    void GUI::drawBroadcast(Camera camera)
    {
        int rotation = 0;
        Vector2 broadcastPosition;
        if (_playerBroadcast < 0)
            return;
        for (int i = 0; i < _teams.size(); i++) {
            for (int j = 0; j < _teams[i].players.size(); j++) {
                if (_teams[i].players[j].id == _playerBroadcast) {
                    broadcastPosition = GetWorldToScreen(
                    (Vector3){ static_cast<float>(
                        _teams[i].players[j].x * CUBESIZE - _mapX + CUBESIZE / 2.0f),
                        3.5f,
                        _teams[i].players[j].y * CUBESIZE - _mapY * CUBESIZE / 2.0f
                    }, camera);
                    // offset the position of the message so that it is centered above the player
                    broadcastPosition.x -= MeasureText(_broadcastMessage.c_str(), 30) / 2;
                    broadcastPosition.y -= 30 / 2;
                    DrawText(_broadcastMessage.c_str(), broadcastPosition.x, broadcastPosition.y, 30, BLACK);
                }
            }
        }
    }

    void GUI::createTexturesStruct(void)
    {
        createSeasonTextures();
        _uiTextures.food = LoadTexture("assets/textures/icons/food_icon.png");
        _uiTextures.linemate = LoadTexture("assets/textures/icons/linemate_icon.png");
        _uiTextures.deraumere = LoadTexture("assets/textures/icons/deraumere_icon.png");
        _uiTextures.sibur = LoadTexture("assets/textures/icons/sibur_icon.png");
        _uiTextures.mendiane = LoadTexture("assets/textures/icons/mendiane_icon.png");
        _uiTextures.phiras = LoadTexture("assets/textures/icons/phiras_icon.png");
        _uiTextures.thystame = LoadTexture("assets/textures/icons/thystame_icon.png");

        for (int i = 0; i <= 39; i++) {
            std::string path = "assets/textures/water/" + std::to_string(i) + ".png";
            _waterTextures.push_back(LoadTexture(path.c_str()));
        }
    }
    // music
    void GUI::init_music(void)
    {
        InitAudioDevice();
        _music = LoadMusicStream("assets/music/music_ori.ogg");
        PlayMusicStream(_music);
        SetMusicVolume(_music, _volume);
    }

    void GUI::update_music(void)
    {
        if (CheckCollisionPointRec(GetMousePosition(), _pauseButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (_musicPaused) {
                ResumeMusicStream(_music);
            } else {
                PauseMusicStream(_music);
            }
            _musicPaused = !_musicPaused;
        }

        if (CheckCollisionPointRec(GetMousePosition(), _volumeSlider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            _volumeSlider.y = GetMouseY() - _volumeSlider.height / 2;
            _volumeSlider.y = Clamp(_volumeSlider.y, _volumeBar.y, _volumeBar.y + _volumeBar.height - _volumeSlider.height);
            _volume = 1.0f - (_volumeSlider.y - _volumeBar.y) / (_volumeBar.height - _volumeSlider.height);
            SetMusicVolume(_music, _volume);
        }
    }

    void GUI::draw_music(void)
    {
        if (!_musicPaused)
            DrawRectangleRec(_pauseButton, RED);
        else
            DrawRectangleRec(_pauseButton, GREEN);
        DrawText(_musicPaused ? "Play music" : "Stop music", _pauseButton.x + 5, _pauseButton.y + 5, 15, WHITE);

        DrawRectangleRec(_volumeBar, LIGHTGRAY);
        DrawRectangleRec(_volumeSlider, DARKGRAY);
    }

    void GUI::update_fps(void)
    {
        if (CheckCollisionPointRec(GetMousePosition(), _fpsButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            _highFPS = !_highFPS;
            _fps = _highFPS ? 160 : 30;
            SetTargetFPS(_fps);
        }

        if (CheckCollisionPointRec(GetMousePosition(), _fpsSlider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            _fpsSlider.y = GetMouseY() - _fpsSlider.height / 2;
            _fpsSlider.y = Clamp(_fpsSlider.y, _fpsBar.y, _fpsBar.y + _fpsBar.height - _fpsSlider.height);
            _fps = (1.0f - (_fpsSlider.y - _fpsBar.y) / (_fpsBar.height - _fpsSlider.height)) * 160;
            _fps = Clamp(_fps, 30, 160);
            SetTargetFPS(_fps);
        }
    }

    void GUI::draw_fps(void)
    {
        if (!_highFPS)
            DrawRectangleRec(_fpsButton, RED);
        else
            DrawRectangleRec(_fpsButton, GREEN);
        DrawText(_highFPS ? "FPS: 160" : "FPS: 30", _fpsButton.x + 5, _fpsButton.y + 5, 15, WHITE);

        DrawRectangleRec(_fpsBar, LIGHTGRAY);
        DrawRectangleRec(_fpsSlider, DARKGRAY);
    }
    // brightness
    void GUI::update_brightness(void)
    {
        if (CheckCollisionPointRec(GetMousePosition(), _brightnessButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (_brightnessToggle) {
                _brightness = 1.0f;
            } else {
                _brightness = 0.1f;
            }
            _brightnessToggle = !_brightnessToggle;
            _darkFilter.a = (1.0f - _brightness) * 255;
        }

        if (CheckCollisionPointRec(GetMousePosition(), _brightnessSlider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            _brightnessSlider.y = GetMouseY() - _brightnessSlider.height / 2;
            _brightnessSlider.y = Clamp(_brightnessSlider.y, _brightnessBar.y, _brightnessBar.y + _brightnessBar.height - _brightnessSlider.height);
            _brightness = 1.0f - (_brightnessSlider.y - _brightnessBar.y) / (_brightnessBar.height - _brightnessSlider.height);
            _darkFilter.a = (1.0f - _brightness) * 255;
        }
    }

    void GUI::draw_brightness(void)
    {
        if (!_brightnessToggle)
            DrawRectangleRec(_brightnessButton, RED);
        else
            DrawRectangleRec(_brightnessButton, GREEN);
        DrawText(_brightnessToggle ? "Max brightness" : "Min brightness", _brightnessButton.x + 5, _brightnessButton.y + 5, 15, WHITE);

        DrawRectangleRec(_brightnessBar, LIGHTGRAY);
        DrawRectangleRec(_brightnessSlider, DARKGRAY);
    }

    void GUI::update_quit(void)
    {
        if (CheckCollisionPointRec(GetMousePosition(), _quitButton) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if (_displayMenu) // Check if the menu is currently being displayed
            {
                exit(0);
            }
        }
    }


    void GUI::draw_quit(void)
    {
        DrawRectangleRec(_quitButton, DARKGRAY);
        DrawText("Quit game", _quitButton.x + 5, _quitButton.y + 5, 15, WHITE);
    }

}
