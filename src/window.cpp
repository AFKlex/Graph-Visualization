//
// Created by afklex on 10/22/23.
//
#include<SDL2/SDL.h>
#include<iostream>
#include "header/AppConfig.h"
bool initWindow(SDL_Window *&ptrWindow){
    bool  success = true;

    // Initialize Window
    ptrWindow = SDL_CreateWindow("Graph Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,AppConfig::WINDOW_WIDTH,AppConfig::WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if(ptrWindow == nullptr){
        std::cout << "Window Could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

bool initRenderer(SDL_Renderer *&ptrRenderer, SDL_Window *&ptrWindow){
    bool success = true;
    ptrRenderer = SDL_CreateRenderer(ptrWindow, -1, SDL_RENDERER_ACCELERATED);
    if (ptrRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return  success;
}

bool initGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer){
    bool  success = true;

    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        success = initWindow(ptrWindow);
    }
    if(success){
        ptrSurface  = SDL_GetWindowSurface(ptrWindow);
    }else{
        std::cout << "Failed to Load ptrSurface because Window was not good! SDL Error: " << SDL_GetError() << std::endl;
    }

    if(!initRenderer(ptrRenderer,ptrWindow)){
        std::cout << "Failed to load ptrRenderer! SDL Error: " << SDL_GetError() << std::endl;
    }

    return success;
}

void destroyGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer){
    SDL_DestroyWindow(ptrWindow);
    SDL_DestroyRenderer(ptrRenderer);
    ptrWindow = nullptr;
    ptrRenderer = nullptr;
    ptrSurface = nullptr;
    SDL_Quit();
}