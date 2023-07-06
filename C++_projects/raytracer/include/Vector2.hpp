/*
** EPITECH PROJECT, 2023
** Vector2.hpp
** File description:
** Vector generic class
*/

#pragma once

namespace raytracer {
    template<typename T>
    class Vector2 {
    public:
        Vector2<T>(T x, T y);
        ~Vector2<T>() = default;

        Vector2<T> operator +(Vector2<T> &other);
        Vector2<T> operator -(Vector2<T> &other);
        Vector2<T> operator *(T value);

        double dotProduct(Vector2<T> &other);
        double getAngle(Vector2<T> &other);
        double getNorm();

        void setX(T x);
        void setY(T y);

        T getX();
        T getY();
    private:
        T _x;
        T _y;
    };
}
