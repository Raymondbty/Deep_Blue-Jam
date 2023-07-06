/*
** EPITECH PROJECT, 2023
** Pixel.hpp
** File description:
** Pixel Class
*/

#pragma once

namespace raytracer {
    class Pixel {
    public:
        Pixel(unsigned char red, unsigned char green, unsigned char blue);
        ~Pixel() = default;

        unsigned char getRed();
        unsigned char getGreen();
        unsigned char getBlue();
    private:
        unsigned char _red;
        unsigned char _green;
        unsigned char _blue;
    };
}
