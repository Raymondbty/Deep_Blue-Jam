/*
** EPITECH PROJECT, 2023
** libsdl.hpp
** File description:
** lmaooo
*/
#ifndef LIBSDL_HPP
#define LIBSDL_HPP

#include <SDL2/SDL.h>

struct Sprite {
    SDL_Texture* texture;
    int x, y;
    int width, height;
};

void sprite_init(SDL_Renderer* renderer, Sprite* sprite, const char* filepath);
void window_manage(SDL_Window* window, SDL_Renderer* renderer);

#endif

