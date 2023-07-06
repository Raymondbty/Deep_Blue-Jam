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

            enum Type
            {
                CIRCLE,
                RECTANGLE,
                TEXT,
                LINE,
                SPRITE
            };
            //! @brief the color of the object rgb value
            unsigned color;
            //! @brief the x and y positions of the object
            coordinates pos;
            //! @brief constructor
            AObject() = default;
            AObject(unsigned color, coordinates pos)
                : color(color), pos(pos) {}
            //! @brief the type of the object
            virtual Type getType() const = 0;
            //! @brief the default destructor
            virtual ~AObject() = default;
            struct AObjectUnknownException : public std::exception
            {
                AObjectUnknownException() : std::exception() {}
                const char *what() const noexcept override { return "Encountered unknown object"; }
            };
        };

        struct Circle : public AObject
        {
            Circle(unsigned color, coordinates pos, int radius)
                : AObject(color, pos), radius(radius) {}
            //! @brief the radius of the circle
            int radius;
            Type getType() const override { return CIRCLE; }
        };

        struct Rectangle : public AObject
        {
            Rectangle(unsigned color, coordinates pos, int width, int height)
                : AObject(color, pos),
                  width(width), height(height) {}
            //! @brief the width of the rectangle
            int width;
            //! @brief the height of the rectangle
            int height;
            Type getType() const override { return RECTANGLE; }
        };

        struct Text : public AObject
        {
            Text() = default;
            Text(unsigned color, coordinates pos, const std::string& text)
                : AObject(color, pos),
                  text(text) {}
            //! @brief the text to display
            std::string text;
            //! @brief the size of the text
            size_t FontSize;
            //! @brief The font file
            std::string path;
            //! @brief The font hitbox (?)
            //! @brief size of the text box
            coordinates hitbox;
            Type getType() const override { return TEXT; }
        };

        struct Line : public AObject
        {
            Line(unsigned color, coordinates pos, int x2, int y2)
                : AObject(color, pos),
                  x2(x2), y2(y2) {}
            //! @brief the x position of the end of the line
            int x2;
            //! @brief the y position of the end of the line
            int y2;
            Type getType() const override { return LINE; }
        };

        struct Sprite : public AObject
        {
            //! @brief the path to the sprite
            std::string path;
            //! @brief the width of the sprite
            int sizeX;
            //! @brief the height of the sprite
            int sizeY;
            //! @brief the character to use to represent as a backup
            int backupChar;
            Type getType() const override { return SPRITE; }
        };
    }
}