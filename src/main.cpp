//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
#include<vector>
int main() {

    // Node
    std::vector<Node> nodeVector;



    if(!initGame()){
        std::cout << "Failed to init the Game! SDL Error:  " << SDL_GetError()<< std::endl;
    }else if(!initFont()){
        std::cout << "Failed to load Font! TTF Error: " << TTF_GetError() << std::endl;
    }

    bool quit = false;
    bool nodeInsertMode = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_n){
                    if(!nodeInsertMode){
                        nodeInsertMode= true;
                        std::cout << "You are now in node insert mode" << std::endl;
                    }
                }else if(e.key.keysym.sym ==SDLK_ESCAPE){
                    nodeInsertMode = false;
                    std::cout << "You are in default mode" << std::endl;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN and nodeInsertMode){
                if(e.button.button == SDL_BUTTON_LEFT){
                   // a = Node("a ", e.button.x, e.button.y)
                   append_Node(&nodeVector,e.button.x, e.button.y,&e);
                }

            }
        }

        for(const auto & i : nodeVector){
            drawNode(i);
        }


        SDL_RenderPresent(AppConfig::RENDERER);
        SDL_Delay(10);
    }

    destroyGame();
    return 0;

}

