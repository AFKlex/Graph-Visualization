//
// Created by afklex on 10/22/23.
//
#include<SDL2/SDL.h>
#include<iostream>
#include "header/AppConfig.h"
#include"header/window.h"
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

bool initFont(SDL_Surface *&ptrMessage, TTF_Font *&ptrFont){
    bool  success = true;
    if( TTF_Init() == -1 ){ //Initialize SDL_ttf
        std::cout << "Failed to load Font" << std::endl;
        success = false;
    }
    ptrFont = TTF_OpenFont("../assets/Gothic.ttf", 100);
    if(ptrFont == nullptr){
        std::cout << "Failed to load Font! TTF_Error: " << TTF_GetError() << std::endl;
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

int
SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void drawNode(SDL_Renderer *& ptrRender, Node node){
    SDL_SetRenderDrawColor(ptrRender,255,0,0,0);
    SDL_RenderDrawCircle(ptrRender, node.x, node.y,15);
}

void destroyGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer){
    SDL_DestroyWindow(ptrWindow);
    SDL_DestroyRenderer(ptrRenderer);
    ptrWindow = nullptr;
    ptrRenderer = nullptr;
    ptrSurface = nullptr;
    SDL_Quit();
}