//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
#include<vector>
#include"header/Graphs.h"

void modeDeactivation(bool *inputMode, bool *connectionMode, bool *removeMode, bool *functionMode){
    *inputMode = false;
    *connectionMode = false;
    *removeMode = false;
    *functionMode= false;
}

int main() {

    int input;
    std::cout << "1. Weighted Graph \n" <<"2. Non-Weighted"<<  std::endl;
    std::cin >> input;

    if(input == 1 ){
        std::cout << "Weighted Graph is true." << std::endl;
        AppConfig::isWeightedGraph = true;
    }



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
    bool  functionMode = false;
    bool removeMode = false;

    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_n){
                    if(!nodeInsertMode){
                        modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode,&functionMode );
                        nodeInsertMode= true;
                        std::cout << "You are now in node insert mode" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_c) {
                    if (!connectionMode) {
                        modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode,&functionMode );
                        connectionMode = true;
                        std::cout << "You are now in node connection mode" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_r){
                    if(!removeMode){
                        modeDeactivation(&nodeInsertMode, &connectionMode, &removeMode,&functionMode);
                        removeMode = true;
                        std::cout << "You are now in remove mode!" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_f) {
                    if (!removeMode) {
                        modeDeactivation(&nodeInsertMode, &connectionMode, &removeMode, &functionMode);
                        functionMode = true;
                        std::cout << "You are now in function mode!" << std::endl;
                    }
                }else if(e.key.keysym.sym == SDLK_a && functionMode){
                    createAdjacencyMatrix(&nodeVector, &edgeVector);
                }else if(e.key.keysym.sym == SDLK_d && functionMode){
                    updateNodeDegree(&edgeVector,&nodeVector);
                    printNodeDegree(&nodeVector);

                }else if(e.key.keysym.sym ==SDLK_ESCAPE){
                    modeDeactivation(&nodeInsertMode, &connectionMode,&removeMode ,&functionMode);
                    std::cout << "You are in default mode" << std::endl;
                }
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT and nodeInsertMode){
                   // Create new node
                   append_Node(&nodeVector,e.button.x, e.button.y,&e);

                }else if(e.button.button == SDL_BUTTON_LEFT and connectionMode){
                    createEdgeBetweenNodes(e.button.x, e.button.y, firstNode, secondNode, &edgeVector, &nodeVector, &oneNodeSelected, &e);
                }else if(e.button.button == SDL_BUTTON_LEFT and removeMode){
                    Node *nodeToRemove = checkNodeExistAtPosition(&nodeVector,e.button.x,e.button.y);
                    if(nodeToRemove != nullptr){
                        removeEdgesFromVector(&edgeVector, nodeToRemove);
                        removeNodeFromNodeVector(&nodeVector,nodeToRemove);

                        SDL_SetRenderDrawColor(AppConfig::RENDERER, AppConfig::BACKGROUND_COLOR.red, AppConfig::BACKGROUND_COLOR.green, AppConfig::BACKGROUND_COLOR.blue, AppConfig::BACKGROUND_COLOR.alpha ); // Set the clear color to black
                        SDL_RenderClear(AppConfig::RENDERER);
                        SDL_SetRenderDrawColor(AppConfig::RENDERER, AppConfig::NODE_COLOR.red, AppConfig::NODE_COLOR.green, AppConfig::NODE_COLOR.blue, AppConfig::NODE_COLOR.alpha);
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

