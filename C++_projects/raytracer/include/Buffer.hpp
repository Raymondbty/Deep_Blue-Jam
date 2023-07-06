/*
** EPITECH PROJECT, 2023
** Buffer.hpp
** File description:
** Buffer class
*/

#pragma once

#include "Pixel.hpp"
#include "Vector2.hpp"

#include <vector>

namespace raytracer {
    class Buffer {
    public:
        Buffer(unsigned int width, unsigned int height);
        ~Buffer() = default;

        void setPixelAt(Pixel pixel, Vector2<int> position);

        unsigned int getWidth();
        unsigned int getHeight();

        Pixel getPixelAt(Vector2<int> position);
        std::vector<Pixel> getBuffer() const;
    private:
        const unsigned int _width;
        const unsigned int _height;
        std::vector<Pixel> _pixels;
    };
}
