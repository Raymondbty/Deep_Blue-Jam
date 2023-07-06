/*
** EPITECH PROJECT, 2023
** Raytracer.hpp
** File description:
** raytracer class header
*/

#pragma once

#include "ErrorHandling.hpp"
#include "GeneratePpm.hpp"
#include "Scene.hpp"

#include <cmath>
#include <iostream>

#define EXIT_ERROR 84

namespace raytracer {
    class Raytracer {
    public:
        Raytracer(Scene &scene, Buffer &buffer);
        ~Raytracer() = default;

        void trace();
    private:
        Scene _scene;
        Buffer _buffer;
    };
}
