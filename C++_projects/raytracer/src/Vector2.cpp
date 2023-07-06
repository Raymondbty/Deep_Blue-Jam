/*
** EPITECH PROJECT, 2023
** Vector2.cpp
** File description:
** Vector2 template class definition
*/

#include "Vector2.hpp"

#include <cmath>

namespace raytracer {
    template<typename T>
    Vector2<T>::Vector2(T x, T y)
        : _x(x), _y(y)
    {}

    template<typename T>
    Vector2<T> Vector2<T>::operator +(Vector2<T> &other)
    {
        return Vector2<T>(
            _x + other.getX(),
            _y + other.getY()
        );
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator -(Vector2<T> &other)
    {
        return Vector2<T>(
            _x - other.getX(),
            _y - other.getY()
        );
    }

    template<typename T>
    Vector2<T> Vector2<T>::operator *(T value)
    {
        return Vector2<T>(
            _x * value,
            _y * value
        );
    }

    template<typename T>
    double Vector2<T>::dotProduct(Vector2<T> &other)
    {
        return _x * other.getX() + _y * other.getY();
    }

    template<typename T>
    double Vector2<T>::getAngle(Vector2<T> &other)
    {
        return dotProduct(other) / (getNorm() * other.getNorm());
    }

    template<typename T>
    double Vector2<T>::getNorm()
    {
        return sqrt(_x * _x + _y * _y);
    }

    template<typename T>
    void Vector2<T>::setX(T x)
    {
        _x = x;
    }

    template<typename T>
    void Vector2<T>::setY(T y)
    {
        _y = y;
    }

    template<typename T>
    T Vector2<T>::getX()
    {
        return _x;
    }

    template<typename T>
    T Vector2<T>::getY()
    {
        return _y;
    }

    template class Vector2<int>;
    template class Vector2<float>;
    template class Vector2<double>;
}
