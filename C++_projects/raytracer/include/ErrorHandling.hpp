/*
** EPITECH PROJECT, 2023
** ErrorHandling.hpp
** File description:
** ErrorHandling
*/

#pragma once

#include <iostream>

class ErrorHandling {
public:
    ErrorHandling(int const ac, char const **av);
    ~ErrorHandling();

    void setReturnValue(int value);
    int getReturnValue();
    void showHelp(int retVal);

private:
    int _returnValue;
};
