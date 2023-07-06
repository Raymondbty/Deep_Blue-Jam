/*
** EPITECH PROJECT, 2022
** Exceptions.hpp
** File description:
** Exceptions
*/

#pragma once

#include <exception>
#include <string>

namespace raytracer {
    namespace exceptions {
        class InputError : public std::exception {
        public:
            InputError(const std::string &message);
            ~InputError() = default;
            const char *what() const noexcept override;
        protected:
            std::string _message;
        };

        class NbArgs : public InputError {
        public:
            NbArgs();
            ~NbArgs() throw();
        };

        class FailedToCreateDirectory : public InputError {
        public:
            FailedToCreateDirectory(const std::string &dirName);
            ~FailedToCreateDirectory() throw();
        };
    }
}
