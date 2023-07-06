/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** camera.cpp
*/

#include "../includes/Render.hpp"

namespace Zappy {
    Camera GUI::createCamera(void)
    {
        Camera camera;
        camera.position = (Vector3){ 0.0f, 16.0f, 16.0f }; // Camera position
        camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
        camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
        camera.fovy = 45.0f;                                // Camera field-of-view Y
        camera.projection = CAMERA_PERSPECTIVE;             // Camera mode type

        return camera;
    }

    void GUI::cameraControl(Camera& camera)
    {
        // Camera controls
        // if page up/down in pressed change the camera height
        if (IsKeyDown(KEY_PAGE_UP))
            camera.position.y += 0.2f;
        else if (IsKeyDown(KEY_PAGE_DOWN))
            camera.position.y -= 0.2f;
    }
}
