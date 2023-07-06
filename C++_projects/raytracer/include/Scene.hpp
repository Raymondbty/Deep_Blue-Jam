/*
** EPITECH PROJECT, 2023
** Scene.hpp
** File description:
** Scene
*/

#pragma once

#include "Objects.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <libconfig.h++>

#define EXIT_ERROR 84

namespace raytracer {
    class Scene {
    public:
        Scene(std::string &filename);
        ~Scene() = default;

        std::vector<objects::Sphere> &getSpheres();
        std::vector<objects::Plane> &getPlanes();
        std::vector<objects::DirectionalLight> &getDirectionalLights();
        objects::AmbientLight &getAmbientLight();
        objects::Camera &getCamera();
    private:
        std::vector<objects::Sphere> _spheres;
        std::vector<objects::Plane> _planes;
        std::vector<objects::DirectionalLight> _directionalLights;
        objects::AmbientLight _ambientLight;
        objects::Camera _camera;
    };
}
