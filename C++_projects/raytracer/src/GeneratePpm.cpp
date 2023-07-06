/*
** EPITECH PROJECT, 2023
** GeneratePpm.cpp
** File description:
** GeneratePpm
*/

#include "GeneratePpm.hpp"

namespace raytracer {
    GeneratePpm::GeneratePpm(unsigned int width, unsigned int height, std::vector<Pixel> const &buffer, std::string const &filename)
        : _width(width), _height(height), _buffer(buffer), _filename(processFilename(filename)), _resDirectory("screenshots/")
    {
        if (buffer.size() != (3 * width * height)) {
            try {
                throw std::runtime_error("Wrong buffer size");
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        generate();
    }

    std::ostream &operator<<(std::ostream &os, GeneratePpm const &ppm)
    {
        os << ppm.getHeader() << std::endl;
        os.write(reinterpret_cast<char const *>(ppm._buffer.data()), ppm._buffer.size());

        return os;
    }

    void GeneratePpm::generate()
    {
        if (std::filesystem::exists(_resDirectory) == false && std::filesystem::is_directory(_resDirectory) == false)
            if (std::filesystem::create_directory(_resDirectory) == false) {
                try {
                    throw exceptions::FailedToCreateDirectory(_resDirectory);
                } catch (exceptions::InputError &e) {
                    std::cerr << e.what() << '\n';
                    exit(EXIT_ERROR);
                }
            }
        std::string path = _resDirectory + _filename + ".ppm";
        std::ofstream of(path);
        of << *this;
    }

    std::string GeneratePpm::getHeader() const
    {
        std::stringstream sstr;
        sstr << "P6" << std::endl;
        sstr << _width << std::endl;
        sstr << _height << std::endl;
        sstr << 255;

        return sstr.str();
    }

    std::string GeneratePpm::processFilename(std::string const &filename) const
    {
        std::string tmp = filename;
        std::string res;
        std::size_t found = tmp.find_last_of("/\\");

        res = tmp.substr(found + 1);
        found = res.find_last_of(".");
        res = res.substr(0, found);

        return res;
    }
}
