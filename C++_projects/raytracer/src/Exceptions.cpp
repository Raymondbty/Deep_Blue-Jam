/*
** EPITECH PROJECT, 2022
** Exceptions.cpp
** File description:
** Exceptions
*/

#include "Exceptions.hpp"

#include <iostream>

namespace raytracer {
    namespace exceptions {
        InputError::InputError(const std::string &message)
            : _message("[!] " + message)
        {
        }

        const char *InputError::what() const throw()
        {
            return _message.c_str();
        }

        NbArgs::NbArgs()
            : InputError("Invalid number of arguments. (Try --help)")
        {
        }

        NbArgs::~NbArgs() throw()
        {
        }

        FailedToCreateDirectory::FailedToCreateDirectory(const std::string &dirName)
            : InputError("Failed to create directory: " + dirName)
        {
        }

        FailedToCreateDirectory::~FailedToCreateDirectory() throw()
        {
        }
    }
}
