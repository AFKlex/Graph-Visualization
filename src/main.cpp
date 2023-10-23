//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
#include<vector>

void modeDeactivation(bool *inputMode, bool *connectionMode){
    *inputMode = false;
    *connectionMode = false;
}

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
    bool  connectionMode = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_n){
                    if(!nodeInsertMode){
                        modeDeactivation(&nodeInsertMode, &connectionMode);
                        nodeInsertMode= true;
                        std::cout << "You are now in node insert mode" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_c){
                    if(!connectionMode){
                        connectionMode= true;
                        modeDeactivation(&nodeInsertMode, &connectionMode);
                        std::cout << "You are now in node connection mode" << std::endl;
                    }
                }else if(e.key.keysym.sym ==SDLK_ESCAPE){
                    modeDeactivation(&nodeInsertMode, &connectionMode);
                    std::cout << "You are in default mode" << std::endl;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT and nodeInsertMode){
                   // Create new node
                   append_Node(&nodeVector,e.button.x, e.button.y,&e);

                }else if(e.button.button == SDL_BUTTON_LEFT and connectionMode){
                    // Connect two nodes
                    checkNodeExistAtPosition(&nodeVector,e.button.x, e.button.y);

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

