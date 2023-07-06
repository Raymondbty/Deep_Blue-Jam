/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** render.cpp
*/

#include "../includes/Render.hpp"
#include "../includes/Network.hpp"
#include <thread>
#include <chrono>
#include <filesystem>

namespace Zappy {

    GUI::GUI()
    {
        // Anti-Aliasing (if available)
        SetConfigFlags(FLAG_MSAA_4X_HINT);
        // Resolution & Window Name
        InitWindow(BASE_WIDTH, BASE_HEIGHT, "Zappy GUI");
        // Set FPS
        SetTargetFPS(BASE_FPS);
        // Fill map with empty tiles
        for (int i = 0; i < _mapX; i++) {
            std::vector<Tile> tmp;
            for (int j = 0; j < _mapY; j++) {
                Tile t;
                t.x = i;
                t.y = j;
                tmp.push_back(t);
            }
            _map.push_back(tmp);
        }

        _models.stoneScale = (Vector3){0.7f, 0.7f, 0.7f};
        _models.eggScale = (Vector3){0.3f, 0.3f, 0.3f};
        _selectedTile = (Vector2){-1, -1};
        _ray = { 0 };

        // Fill the models and UI textures structs
        createModelsStruct();
        createTexturesStruct();
        createSeasonTextures();

        _animationSpeed = 15;
        _animsCount = 0;
        _animFrameCounter = 0;
        _sillyDance = LoadModelAnimations("assets/models/PlayerSillyDanceAnimation.iqm", &_animsCount);
        _walk = LoadModelAnimations("assets/models/PlayerWalkAnimation.iqm", &_animsCount);
        _currentAnimation = _sillyDance;

        _displayMenu = false;
        _isRunning = true;
        std::thread t1(&GUI::animateModels, this);
        t1.detach();
        std::thread wt(&GUI::animateWater, this);
        wt.detach();
        std::thread t2(&GUI::animatePlayers, this);
        t2.detach();

    }

    Model GUI::createModel(std::string model, std::string texture)
    {
        Model m = LoadModel(model.c_str());
        if (texture == "")
            return m;
        Texture2D t = LoadTexture(texture.c_str());
        Texture2D t2 = LoadTexture("assets/textures/reflect.png");
        m.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = t;
        m.materials[0].maps[MATERIAL_MAP_OCCLUSION].texture = t2;
        return m;
    }

    void GUI::animateModels(void)
    {
        while (_isRunning) {
            if (_models.rotation >= 360.0f)
                _models.rotation = 0.0f;
            else
                _models.rotation += 1.0f;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        printf("Stopped animation model thread.\n");
    }

    void GUI::animateWater(void)
    {
        int textureIndex = 0;
        while (_isRunning) {
            if (textureIndex >= 39)
                textureIndex = 0;
            else
                textureIndex++;
            _water = _waterTextures[textureIndex];
            std::this_thread::sleep_for(std::chrono::milliseconds(80));
        }
        printf("Stopped animation water thread.\n");
    }

    void GUI::animatePlayers(void)
    {
        while(_isRunning) {
            _animFrameCounter++;
            if (_animFrameCounter >= _currentAnimation[0].frameCount) _animFrameCounter = 0;
            std::this_thread::sleep_for(std::chrono::milliseconds(_animationSpeed));
        }
        printf("Stopped animation player thread.\n");
    }

    void GUI::playerIncantationStart(int x, int y, int level, int id ...)
    {
        printf("Player incantation start for player with ID: %d\n", id);

    }

    void GUI::playerIncantationEnd(int x, int y, int result)
    {
        printf("Player incantation end with result: %d\n", result);
    }

    void GUI::eggHatchAnimation(int egg_id)
    {
        printf("Egg animation to do for egg number: %d\n", egg_id);
    }

    void GUI::cleanTextures(void)
    {
        // Destroy the models
        UnloadModel(_models.foodModel);
        UnloadModel(_models.eggModel);
        UnloadModel(_models.linemateModel);
        UnloadModel(_models.deraumereModel);
        UnloadModel(_models.siburModel);
        UnloadModel(_models.mendianeModel);
        UnloadModel(_models.phirasModel);
        UnloadModel(_models.thystameModel);
        UnloadModel(_playerModel);

        // Destroy the textures
        UnloadTexture(_uiTextures.food);
        UnloadTexture(_uiTextures.linemate);
        UnloadTexture(_uiTextures.deraumere);
        UnloadTexture(_uiTextures.sibur);
        UnloadTexture(_uiTextures.mendiane);
        UnloadTexture(_uiTextures.phiras);
        UnloadTexture(_uiTextures.thystame);

        // Destroy the water textures
        for (int i = 0; i < _waterTextures.size(); i++) {
            UnloadTexture(_waterTextures[i]);
        }

        // Destroy the season textures
        UnloadTexture(_seasonTextures.spring);
        UnloadTexture(_seasonTextures.springSide);
        UnloadTexture(_seasonTextures.summer);
        UnloadTexture(_seasonTextures.summerSide);
        UnloadTexture(_seasonTextures.winter);
        UnloadTexture(_seasonTextures.winterSide);

        // Destroy the models animations
        UnloadModelAnimation(*_sillyDance);
        UnloadModelAnimation(*_walk);

        printf("All textures and models destroyed.\n");
    }

    RayCollision GUI::mouseCollision(RayCollision collision)
    {
        for (int i = 0; i < _map.size(); i++) {
            for (int j = 0; j < _map[i].size(); j++) {
                collision = GetRayCollisionBox(_ray, _mapBoxes[i][j]);
                if (collision.hit) {
                    _selectedTile = (Vector2){static_cast<float>(i), static_cast<float>(j)};
                    return collision;
                } else {
                    _selectedTile = (Vector2){-1000, -1000};
                }
            }
        }
        return collision;
    }

    void GUI::run(void)
    {
        init_music();

        Camera3D camera = createCamera();

        RayCollision collision = { 0 };
        collision.hit = false;

        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            // Update
            UpdateMusicStream(_music);

            if (IsCursorHidden()) UpdateCamera(&camera, CAMERA_FIRST_PERSON);
            cameraControl(camera);

            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                if (IsCursorHidden())
                    EnableCursor();
                else
                    DisableCursor();
            }
            _ray = GetMouseRay(GetMousePosition(), camera);
            // Check collision between ray and box
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (IsCursorHidden() == false && _displayMenu == false)
                    collision = mouseCollision(collision);
            }

            // Menu display
            if (IsKeyPressed(KEY_TAB))
                if (!_displayMenu) {
                    _displayMenu = true;
                    EnableCursor();
                } else {
                    _displayMenu = false;
                    DisableCursor();
                }

            UpdateModelAnimation(_playerModel, _currentAnimation[0], _animFrameCounter);

            // Draw
            BeginDrawing();

                ClearBackground(SKY);
                BeginMode3D(camera);
                    // Draw everything
                    drawMap();
                    drawModels();
                    drawPlayers();
                    drawEggs();

                EndMode3D();
                drawUI();
                drawMenu();
                drawBroadcast(camera);

                DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), _darkFilter);

            EndDrawing();
        }
        UnloadMusicStream(_music);
        CloseAudioDevice();
        CloseWindow();
        cleanTextures();
        // exit network thread
        close(getClient().sock);
        printf("\nExiting...\n");
        _isRunning = false;
        exit(0);
    }
}
