//
// Created by afklex on 10/22/23.
//

#ifndef GRAPH_VISUALIZATION_APPCONFIG_H
#define GRAPH_VISUALIZATION_APPCONFIG_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

struct Color {
    int red;
    int green;
    int blue;
    int alpha;
};

namespace AppConfig{
    extern SDL_Window * WINDOW;
    extern SDL_Surface *SCREEN_SURFACE;
    extern SDL_Renderer *RENDERER;

    extern  const int WINDOW_WIDTH;
    extern const int WINDOW_HEIGHT;

    extern const SDL_Color TEXT_COLOR;
    extern const Color BACKGROUND_COLOR;
    extern const Color NODE_COLOR;
    extern TTF_Font* FONT;
    extern SDL_Texture *textTexture;

    extern const int NODE_RADIUS;


}


#endif //GRAPH_VISUALIZATION_APPCONFIG_H
