//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
#include<vector>
void modeDeactivation(bool *inputMode, bool *connectionMode, bool *removeMode){
    *inputMode = false;
    *connectionMode = false;
    *removeMode = false;
}

int main() {

    // Node
    std::vector<Node> nodeVector;
    std::vector<Edge> edgeVector;

    Node *firstNode = nullptr;
    Node *secondNode = nullptr;

    if(!initGame()){
        std::cout << "Failed to init the Game! SDL Error:  " << SDL_GetError()<< std::endl;
    }else if(!initFont()){
        std::cout << "Failed to load Font! TTF Error: " << TTF_GetError() << std::endl;
    }

    bool quit = false;
    bool nodeInsertMode = false;
    bool  connectionMode = false;
    bool oneNodeSelected = false;
    bool removeMode = false;

    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_n){
                    if(!nodeInsertMode){
                        modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode );
                        nodeInsertMode= true;
                        std::cout << "You are now in node insert mode" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_c) {
                    if (!connectionMode) {
                        modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode );
                        connectionMode = true;
                        std::cout << "You are now in node connection mode" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_r){
                    if(!removeMode){
                        modeDeactivation(&nodeInsertMode, &connectionMode, &removeMode);
                        removeMode = true;
                        std::cout << "You are now in remove mode!" << std::endl;
                    }


                }else if(e.key.keysym.sym ==SDLK_ESCAPE){
                    modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode );
                    std::cout << "You are in default mode" << std::endl;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT and nodeInsertMode){
                   // Create new node
                   append_Node(&nodeVector,e.button.x, e.button.y,&e);

                }else if(e.button.button == SDL_BUTTON_LEFT and connectionMode){
                    createEdgeBetweenNodes(e.button.x, e.button.y, firstNode, secondNode, &edgeVector, &nodeVector, &oneNodeSelected);
                }else if(e.button.button == SDL_BUTTON_LEFT and removeMode){
                    Node *nodeToRemove = checkNodeExistAtPosition(&nodeVector,e.button.x,e.button.y);
                    if(nodeToRemove != nullptr){
                        removeNodeFromNodeVector(&nodeVector,nodeToRemove);
                    }
                }

            }
        }

        for(const auto & i : nodeVector){
            drawNode(i);
        }
        for(const auto & i : edgeVector){
            drawEdge(i);
        }

        SDL_RenderPresent(AppConfig::RENDERER);
        SDL_Delay(10);
    }

    destroyGame();
    return 0;

}

