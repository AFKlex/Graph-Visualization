//
// Created by afklex on 10/22/23.
//
#include<SDL2/SDL.h>
#include "header/Node.h"
#include<SDL2/SDL_ttf.h>
#ifndef GRAPH_VISUALIZATION_WINDOW_H
#define GRAPH_VISUALIZATION_WINDOW_H
bool initGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer);
void destroyGame(SDL_Window *&ptrWindow, SDL_Surface *&ptrSurface, SDL_Renderer *&ptrRenderer);
void drawNode(SDL_Renderer *& ptrRender, Node node);
#endif //GRAPH_VISUALIZATION_WINDOW_H
