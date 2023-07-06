#pragma once

#include <iostream>
#include <memory>
#include <string>

namespace Game
{
    namespace Display
    {
        struct AObject
        {
            struct coordinates
            {
                int x;
                int y;
            };
            struct sfml {
                struct Circle {
                    int radius;
                };
                struct Rectangle { 
                    int width;
                    int height;
                };
                struct Text {
                    std::string text;
                    size_t FontSize;
                    std::string path;
                };
                struct Line {
                    int x2;
                    int y2;
                };
                struct Sprite {
                    std::string path;
                    int sizeX_sprite;
                    int sizeY_sprite;
                };
                enum Type
                {
                    CIRCLE,
                    RECTANGLE,
                    TEXT,
                    LINE,
                    SPRITE
                };
                Type type;
                Circle c;
                Rectangle r;
                Text t;
                Line l;
                Sprite s;
            };
            struct ncurse {
                std::string caractere;
            };
            std::string name;
            coordinates pos;
            sfml obj_sfml;
            ncurse obj_ncurse;
            std::string color;
        };
    }
}
