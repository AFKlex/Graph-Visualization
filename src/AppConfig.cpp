//
// Created by afklex on 10/22/23.
//

#include "header/AppConfig.h"
namespace AppConfig{
    SDL_Window * WINDOW = nullptr;
    SDL_Surface *SCREEN_SURFACE = nullptr;
    SDL_Renderer *RENDERER = nullptr;

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;
    const SDL_Color TEXT_COLOR = {255,0,0};
    TTF_Font* FONT = nullptr;

    SDL_Texture *textTexture = nullptr;

    const int NODE_RADIUS= 15;
}