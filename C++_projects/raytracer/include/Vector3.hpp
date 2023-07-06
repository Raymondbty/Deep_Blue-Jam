/*
** EPITECH PROJECT, 2023
** Vector3.hpp
** File description:
** Vector3 template class
*/

#pragma once

namespace raytracer {
    template<typename T>
    class Vector3 {
    public:
        Vector3<T>(T x, T y, T z);
        ~Vector3<T>() = default;

        Vector3<T> operator +(Vector3<T> &other);
        Vector3<T> operator -(Vector3<T> &other);
        Vector3<T> operator *(T value);

        double dotProduct(Vector3<T> &other);
        double getAngle(Vector3<T> &other);
        double getNorm();

        void setX(T x);
        void setY(T y);
        void setZ(T y);

        T getX();
        T getY();
        T getZ();
    private:
        T _x;
        T _y;
        T _z;
    };

}
