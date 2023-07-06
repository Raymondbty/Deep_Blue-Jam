/*
** EPITECH PROJECT, 2023
** Color.hpp
** File description:
** Color class
*/

#pragma once

namespace raytracer {
    class Color {
    public:
        Color(unsigned char red, unsigned char green, unsigned char blue);
        ~Color() = default;

        unsigned char getRed() const;
        unsigned char getGreen() const;
        unsigned char getBlue() const;
    private:
        unsigned char _red;
        unsigned char _green;
        unsigned char _blue;
    };
}
