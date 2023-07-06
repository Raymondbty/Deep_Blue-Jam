/*
** EPITECH PROJECT, 2023
** Color.cpp
** File description:
** Color class definition
*/

#include "Color.hpp"

namespace raytracer {
    Color::Color(
        unsigned char red,
        unsigned char green,
        unsigned char blue
    )
        : _red(red), _green(green), _blue(blue)
    {}

    unsigned char Color::getRed() const
    {
        return _red;
    }

    unsigned char Color::getGreen() const
    {
        return _green;
    }

    unsigned char Color::getBlue() const
    {
        return _blue;
    }
}
