/*
** EPITECH PROJECT, 2023
** Vector3.cpp
** File description:
** Vector3 templace class definition
*/

#include "Vector3.hpp"

#include <cmath>

namespace raytracer {
    template<typename T>
    Vector3<T>::Vector3(T x, T y, T z)
        : _x(x), _y(y), _z(z)
    {}

    template<typename T>
    Vector3<T> Vector3<T>::operator +(Vector3<T> &other)
    {
        return Vector3<T>(
            _x + other.getX(),
            _y + other.getY(),
            _z + other.getZ()
        );
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator -(Vector3<T> &other)
    {
        return Vector3<T>(
            _x - other.getX(),
            _y - other.getY(),
            _z - other.getZ()
        );
    }

    template<typename T>
    Vector3<T> Vector3<T>::operator *(T value)
    {
        return Vector3<T>(
            _x * value,
            _y * value,
            _z * value
        );
    }

    template<typename T>
    double Vector3<T>::getAngle(Vector3<T> &other)
    {
        return dotProduct(other) / (getNorm() * other.getNorm());
    }

    template<typename T>
    double Vector3<T>::dotProduct(Vector3<T> &other)
    {
        return _x * other.getX() + _y * other.getY() + _z * other.getZ();
    }

    template<typename T>
    double Vector3<T>::getNorm()
    {
        return sqrt(_x * _x + _y * _y + _z * _z);
    }

    template<typename T>
    void Vector3<T>::setX(T x)
    {
        _x = x;
    }

    template<typename T>
    void Vector3<T>::setY(T y)
    {
        _y = y;
    }

    template<typename T>
    void Vector3<T>::setZ(T z)
    {
        _z = z;
    }

    template<typename T>
    T Vector3<T>::getX()
    {
        return _x;
    }

    template<typename T>
    T Vector3<T>::getY()
    {
        return _y;
    }

    template<typename T>
    T Vector3<T>::getZ()
    {
        return _z;
    }

    template class Vector3<int>;
    template class Vector3<float>;
    template class Vector3<double>;
}
