//
// Created by afklex on 10/22/23.
//
#include<SDL2/SDL.h>
#include "header/Node.h"
#include<SDL2/SDL_ttf.h>
#ifndef GRAPH_VISUALIZATION_WINDOW_H
#define GRAPH_VISUALIZATION_WINDOW_H
bool initGame();
void destroyGame();
void drawNode(Node node);
bool initFont();
#endif //GRAPH_VISUALIZATION_WINDOW_H
