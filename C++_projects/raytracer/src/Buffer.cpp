/*
** EPITECH PROJECT, 2023
** Buffer.cpp
** File description:
** Buffer class definition
*/

#include "Buffer.hpp"
#include "Vector2.hpp"

using std::vector;

namespace raytracer {
    Buffer::Buffer(unsigned int width, unsigned int height)
        : _width(width),
        _height(height),
        _pixels(3 * width * height, Pixel(0, 0, 0))
    {}

    vector<Pixel> Buffer::getBuffer() const
    {
        return _pixels;
    }

    Pixel Buffer::getPixelAt(Vector2<int> position)
    {
        return _pixels[position.getX() % _width + position.getY() * _height];
    }

    unsigned int Buffer::getWidth()
    {
        return _width;
    }

    unsigned int Buffer::getHeight()
    {
        return _height;
    }

    void Buffer::setPixelAt(Pixel pixel, Vector2<int> position)
    {
        _pixels[position.getX() % _width + position.getY() * _height] = pixel;
    }
}
