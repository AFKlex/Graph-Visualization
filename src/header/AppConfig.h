//
// Created by afklex on 10/22/23.
//

#ifndef GRAPH_VISUALIZATION_APPCONFIG_H
#define GRAPH_VISUALIZATION_APPCONFIG_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

struct Color {
    Uint8 red;
    Uint8 green;
    Uint8 blue;
    Uint8 alpha;
};

namespace AppConfig{
    extern SDL_Window * WINDOW;
    extern SDL_Surface *SCREEN_SURFACE;
    extern SDL_Renderer *RENDERER;
    extern bool isWeightedGraph;

    extern  const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;

    extern const SDL_Color TEXT_COLOR;
    extern const Color BACKGROUND_COLOR;
    extern const Color NODE_COLOR;
    extern TTF_Font* FONT;
    extern SDL_Texture *textTexture;
    extern SDL_Texture *weightTexture;

    extern const int NODE_RADIUS;


}


#endif //GRAPH_VISUALIZATION_APPCONFIG_H
