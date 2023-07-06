/*
** EPITECH PROJECT, 2023
** GeneratePpm.hpp
** File description:
** GeneratePpm
*/

#pragma once

#include "Buffer.hpp"
#include "Exceptions.hpp"
#include "Raytracer.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>
#include <filesystem>

namespace raytracer {
    class GeneratePpm {
    public:
        GeneratePpm(
            unsigned int width,
            unsigned int height,
            std::vector<Pixel> const &buffer,
            std::string const &filename
        );
        ~GeneratePpm() = default;

        friend std::ostream &operator<<(std::ostream &os, GeneratePpm const &img);

        void generate();
        std::string processFilename(std::string const &filename) const;
        // std::string processFilename(std::string const &filename)

    private:
        std::string getHeader() const;
        unsigned int _width;
        unsigned int _height;
        std::string _filename;
        std::string _resDirectory;
        std::vector<Pixel> _buffer;
    };
}
