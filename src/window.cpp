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
    AppConfig::FONT = TTF_OpenFont("../assets/Gothic.ttf", 24);
    if(AppConfig::FONT == nullptr){
        std::cout << "Failed to load Font! TTF_Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    TTF_SetFontStyle(AppConfig::FONT, TTF_STYLE_NORMAL);

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

bool loadNodeTextTexture(Node node){
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

bool loadEdgeTexture(Edge edge){
    bool  success = true;
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(AppConfig::FONT, std::to_string(edge.weight).c_str()  , AppConfig::TEXT_COLOR);
    if(surfaceMessage == nullptr){
        std::cout << "Failed to load SurfaceMessage! SDL_Error: " << SDL_GetError() << std::endl;
        success = false ;
    }
    if(AppConfig::weightTexture != nullptr){
        SDL_DestroyTexture(AppConfig::weightTexture);
    }
    AppConfig::weightTexture = SDL_CreateTextureFromSurface(AppConfig::RENDERER, surfaceMessage);

    if(AppConfig::weightTexture == nullptr){
        std::cout << "Failed to load Message! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }else{
        SDL_FreeSurface(surfaceMessage);
    }
    return success;
}

void drawNode(Node node){
    SDL_SetRenderDrawColor(AppConfig::RENDERER,AppConfig::NODE_COLOR.red,AppConfig::NODE_COLOR.green, AppConfig::NODE_COLOR.blue, AppConfig::NODE_COLOR.alpha);
    SDL_RenderDrawCircle(node.x, node.y,AppConfig::NODE_RADIUS);
    loadNodeTextTexture(node);

    // Calculate the width and height of the text
    int textWidth, textHeight;
    TTF_SizeText(AppConfig::FONT, node.name.c_str(), &textWidth, &textHeight);

    SDL_Rect messageRect;
    messageRect.x = node.x - textWidth / 2; // Centered horizontally
    messageRect.y = node.y - textHeight / 2; // Centered vertically
    messageRect.w = textWidth;
    messageRect.h = textHeight;

    SDL_RenderCopy(AppConfig::RENDERER, AppConfig::textTexture, nullptr, &messageRect);


}

void drawEdge(Edge edge) {
    int ax = edge.A->x;
    int ay = edge.A->y;
    int bx = edge.B->x;
    int by = edge.B->y;

    // Calculate the direction of the edge
    int dx = bx - ax;
    int dy = by - ay;

    // Calculate the length of the edge
    float length = sqrt(dx * dx + dy * dy);

    // Normalize the direction
    float normalized_dx = dx / length;
    float normalized_dy = dy / length;

    // Calculate the offset from the node center to the edge
    int offset = AppConfig::NODE_RADIUS;

    // Calculate the starting point for the edge
    int start_x = ax + offset * normalized_dx;
    int start_y = ay + offset * normalized_dy;

    // Calculate the ending point for the edge
    int end_x = bx - offset * normalized_dx;
    int end_y = by - offset * normalized_dy;

    if(edge.A == edge.B){
        SDL_RenderDrawCircle(ax-AppConfig::NODE_RADIUS-2,ay -AppConfig::NODE_RADIUS-2,AppConfig::NODE_RADIUS-5);
    }else{
        SDL_RenderDrawLine(AppConfig::RENDERER, start_x, start_y, end_x, end_y);

        if(AppConfig::isWeightedGraph){
            loadEdgeTexture(edge);
            // Calculate the midpoint between start and end points
            int midX = (start_x + end_x) / 2;
            int midY = (start_y + end_y) / 2;

            // Calculate the width and height of the text
            int textWidth, textHeight;
            TTF_SizeText(AppConfig::FONT, std::to_string(edge.weight).c_str(), &textWidth, &textHeight);

            // Set an offset value (adjust as needed)
            int xOffset = 15; // Adjust as needed
            int yOffset = 15; // Adjust as needed

            // Adjust the messageRect to position it away from the line
            SDL_Rect messageRect;
            messageRect.x = midX - textWidth / 2 + xOffset; // Offset horizontally
            messageRect.y = midY - textHeight / 2 + yOffset; // Offset vertically
            messageRect.w = textWidth;
            messageRect.h = textHeight;

            // Render the weight text at the calculated position
            SDL_RenderCopy(AppConfig::RENDERER, AppConfig::weightTexture, nullptr, &messageRect);
        }

    }
}

void destroyGame(){
    SDL_DestroyWindow(AppConfig::WINDOW);
    SDL_DestroyRenderer(AppConfig::RENDERER);
    AppConfig::WINDOW = nullptr;
    AppConfig::RENDERER = nullptr;
    SDL_FreeSurface(AppConfig::SCREEN_SURFACE);
    SDL_Quit();
}