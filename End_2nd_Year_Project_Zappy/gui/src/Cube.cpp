/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-zappy-guillaume.clement-bonniel-veyron
** File description:
** cube.cpp
*/

#include "../includes/Render.hpp"

namespace Zappy {

    void DrawCubeTexture(Texture2D textureA, Texture2D textureB, Vector3 position, float width, float height, float length, Color color, bool front, bool back, bool left, bool right)
    {
        float x = position.x;
        float y = position.y;
        float z = position.z;

        // Set desired texture
        rlSetTexture(textureA.id);

            rlBegin(RL_QUADS);
                rlColor4ub(color.r, color.g, color.b, color.a);
                // Top Face
                rlNormal3f(0.0f, 1.0f, 0.0f);       // Normal Pointing Up
                rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
                rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Bottom Left Of The Texture and Quad
                rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Bottom Right Of The Texture and Quad
                rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
                if (!front && !back && !left && !right){
                    rlEnd();
                    rlSetTexture(0);
                    return;
                }
            rlEnd();

        rlSetTexture(0);

        rlSetTexture(textureB.id);

            rlBegin(RL_QUADS);
                rlColor4ub(color.r, color.g, color.b, color.a);
                if (front) {
                    // Front Face
                    rlNormal3f(0.0f, 0.0f, 1.0f);       // Normal Pointing Towards Viewer
                    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
                    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
                    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
                    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
                }
                if (back) {
                    // Back Face
                    rlNormal3f(0.0f, 0.0f, - 1.0f);     // Normal Pointing Away From Viewer
                    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
                    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
                    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
                    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
                }
                if (right) {
                    // Right face
                    rlNormal3f(1.0f, 0.0f, 0.0f);       // Normal Pointing Right
                    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z - length/2);  // Bottom Right Of The Texture and Quad
                    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z - length/2);  // Top Right Of The Texture and Quad
                    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x + width/2, y + height/2, z + length/2);  // Top Left Of The Texture and Quad
                    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x + width/2, y - height/2, z + length/2);  // Bottom Left Of The Texture and Quad
                }
                if (left) {
                    // Left Face
                    rlNormal3f( - 1.0f, 0.0f, 0.0f);    // Normal Pointing Left
                    rlTexCoord2f(0.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z - length/2);  // Bottom Left Of The Texture and Quad
                    rlTexCoord2f(1.0f, 0.0f); rlVertex3f(x - width/2, y - height/2, z + length/2);  // Bottom Right Of The Texture and Quad
                    rlTexCoord2f(1.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z + length/2);  // Top Right Of The Texture and Quad
                    rlTexCoord2f(0.0f, 1.0f); rlVertex3f(x - width/2, y + height/2, z - length/2);  // Top Left Of The Texture and Quad
                }
            rlEnd();
        rlSetTexture(0);
    }
}