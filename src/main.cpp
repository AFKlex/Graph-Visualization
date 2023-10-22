//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
int main() {

    SDL_Window * window = nullptr;
    SDL_Surface *screenSurface = nullptr;
    SDL_Renderer *renderer = nullptr;

    if(!initGame(window,screenSurface,renderer)){
        std::cout << "Failed to init the Game! SDL Error:  " << SDL_GetError()<< std::endl;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_Delay(10);
    }

    destroyGame(window,screenSurface,renderer);
    return 0;

}