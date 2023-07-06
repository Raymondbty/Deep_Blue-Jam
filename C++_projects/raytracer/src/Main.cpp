/*
** EPITECH PROJECT, 2023
** Main.cpp
** File description:
** Main
*/

#include "Raytracer.hpp"
#include "GeneratePpm.hpp"
#include "Exceptions.hpp"
#include "Scene.hpp"
#include "Buffer.hpp"

#include <cstdlib>
#include <iostream>

using std::string;
using std::cout;
using std::cerr;

static const string HELP_MSG = "USAGE: ./raytracer <SCENE_FILE>\n\
\n\tSCENE_FILE: scene configuration\n";

int main(int argc, char const **argv)
{
    if (argc == 2 && string(argv[1]) == "--help") {
        cout << HELP_MSG;
        return EXIT_SUCCESS;
    }
    if (argc < 2 || argc > 2) {
        try {
            throw raytracer::exceptions::NbArgs();
        } catch (raytracer::exceptions::InputError &e) {
            std::cerr << e.what() << '\n';
            return EXIT_ERROR;
        }
    }
    std::string filename = argv[1];
    raytracer::Scene Scene(filename);
    
/* TEMPORARY (creating a zebra pattern image in 1080p) */
unsigned int width = 1920;
unsigned int height = 1080;
raytracer::Buffer buffer(width, height);

for (unsigned int y = 0; y < height; ++y) {
    for (unsigned int x = 0; x < width; ++x) {
        if (((y / 10) % 2)) {
            buffer.setPixelAt(raytracer::Pixel(0, 0, 0), raytracer::Vector2<int>(x, y));
        } else {
            buffer.setPixelAt(raytracer::Pixel(255, 255, 255), raytracer::Vector2<int>(x, y));
        }
    }
}
raytracer::GeneratePpm genPpm(width, height, buffer.getBuffer(), "scene.ppm");
/* END OF TEMPORARY */


    return EXIT_SUCCESS;
}
