/*
** EPITECH PROJECT, 2023
** Pixel.cpp
** File description:
** Pixel class definition
*/

#include "Pixel.hpp"

namespace raytracer {
    Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue)
        : _red(red), _green(green), _blue(blue)
    {
    }

    unsigned char Pixel::getRed()
    {
        return _red;
    }

    unsigned char Pixel::getGreen()
    {
        return _green;
    }

    unsigned char Pixel::getBlue()
    {
        return _blue;
    }
}
