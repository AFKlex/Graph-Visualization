//
// Created by afklex on 10/22/23.
//
#include<SDL2/SDL.h>
#include<iostream>
#include "header/AppConfig.h"
#include"header/window.h"
bool initWindow(){
    bool  success = true;

    // Initialize Window
    AppConfig::WINDOW = SDL_CreateWindow("Graph Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,AppConfig::WINDOW_WIDTH,AppConfig::WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    if(AppConfig::WINDOW == nullptr){
        std::cout << "Window Could not be loaded! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return success;
}

bool initFont(){
    bool  success = true;
    if( TTF_Init() == -1 ){ //Initialize SDL_ttf
        std::cout << "Failed to load Font" << std::endl;
        success = false;
    }
    AppConfig::FONT = TTF_OpenFont("../assets/Gothic.ttf", 200);
    if(AppConfig::FONT == nullptr){
        std::cout << "Failed to load Font! TTF_Error: " << TTF_GetError() << std::endl;
        success = false;
    }

    return success;
}

bool initRenderer(){
    bool success = true;
    AppConfig::RENDERER = SDL_CreateRenderer(AppConfig::WINDOW, -1, SDL_RENDERER_ACCELERATED);
    if ( AppConfig::RENDERER == nullptr) {
        std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    return  success;
}

bool initGame(){
    bool  success = true;

    if(SDL_Init(SDL_INIT_VIDEO) <0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        success = initWindow();
    }
    if(success){
        AppConfig::SCREEN_SURFACE  = SDL_GetWindowSurface(AppConfig::WINDOW);
    }else{
        std::cout << "Failed to Load ptrSurface because Window was not good! SDL Error: " << SDL_GetError() << std::endl;
    }

    if(!initRenderer()){
        std::cout << "Failed to load ptrRenderer! SDL Error: " << SDL_GetError() << std::endl;
    }

    return success;
}

int
SDL_RenderDrawCircle(int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(AppConfig::RENDERER, x - offsety, y - offsetx);

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

bool loadTextTexture(Node node){
    bool  success = true;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(AppConfig::FONT, node.name.c_str(), AppConfig::TEXT_COLOR);
    if(surfaceMessage == nullptr){
        std::cout << "Failed to load SurfaceMessage! SDL_Error: " << SDL_GetError() << std::endl;
        success = false ;
    }
    if(AppConfig::textTexture != nullptr){
        SDL_DestroyTexture(AppConfig::textTexture);
    }
    AppConfig::textTexture = SDL_CreateTextureFromSurface(AppConfig::RENDERER, surfaceMessage);

    if(AppConfig::textTexture == nullptr){
        std::cout << "Failed to load Message! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        SDL_FreeSurface(surfaceMessage);
    }
    return success;
}

void drawNode(Node node){
    SDL_SetRenderDrawColor(AppConfig::RENDERER,255,0,0,0);
    SDL_RenderDrawCircle(node.x, node.y,AppConfig::NODE_RADIUS);
    loadTextTexture(node);

    SDL_Rect messageRect; //create a rect
    messageRect.x = node.x-10;  //controls the rect's x coordinate
    messageRect.y = node.y-10; // controls the rect's y coordinte
    messageRect.w = 20; // controls the width of the rect
    messageRect.h = 20;

    SDL_RenderCopy(AppConfig::RENDERER, AppConfig::textTexture, nullptr, &messageRect);


}

void drawEdge(Edge edge){
    int ax = edge.A->x;
    int ay = edge.A->y;

    int bx = edge.B->x;
    int by = edge.B->y;

    int ax_increment = 0;
    int ay_increment = 0;
    int bx_increment = 0;
    int by_increment = 0;

    if(ax <= bx){
        // Node A is left of node B
        if(ay <= by){
            // Node A over B
            //std::cout << "Node A left over B" << std::endl;
            ax_increment = AppConfig::NODE_RADIUS-4;
            ay_increment = AppConfig::NODE_RADIUS-4;
            bx_increment = -(AppConfig::NODE_RADIUS-4);
            by_increment = -(AppConfig::NODE_RADIUS-4);
        }else{
            // Node A is under B
            //std::cout << "Node A left under B" << std::endl;
            ax_increment = AppConfig::NODE_RADIUS;
        }
    }else{
        // Node A is right of node B
        if(ay <= by){
            // Node A over B
            //std::cout << "Node A right over B" << std::endl;
            bx_increment = (AppConfig::NODE_RADIUS-4);
            by_increment = -(AppConfig::NODE_RADIUS-4);
            ax_increment = -(AppConfig::NODE_RADIUS-4);
            ay_increment = +(AppConfig::NODE_RADIUS-4);
        }else{
            // Node A is under B
            //std::cout << "Node A right under B" << std::endl;
            bx_increment = (AppConfig::NODE_RADIUS-4);
            by_increment = (AppConfig::NODE_RADIUS-4);
            ax_increment = -(AppConfig::NODE_RADIUS-4);
            ay_increment = -(AppConfig::NODE_RADIUS-4);

        }

    }

    SDL_RenderDrawLine(AppConfig::RENDERER, ax+ax_increment,ay+ ay_increment, bx + bx_increment, by+by_increment);
}

void destroyGame(){
    SDL_DestroyWindow(AppConfig::WINDOW);
    SDL_DestroyRenderer(AppConfig::RENDERER);
    AppConfig::WINDOW = nullptr;
    AppConfig::RENDERER = nullptr;
    SDL_FreeSurface(AppConfig::SCREEN_SURFACE);
    SDL_Quit();
}