/*
** EPITECH PROJECT, 2023
** libsdl.cpp
** File description:
** lmaozopaj
*/

#include "libsdl.hpp"

void sprite_init(SDL_Renderer* renderer, Sprite* sprite, const char* filepath) {
    SDL_Surface* surface = SDL_LoadBMP(filepath);
    sprite->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->width, &sprite->height);

    sprite->x = 0;
    sprite->y = 0;
}

void window_manage(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
    }
}
