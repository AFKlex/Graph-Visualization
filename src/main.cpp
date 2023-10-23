//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
#include<vector>
void append_Node(std::vector<Node> *nodes,int x, int y, SDL_Event * e){
    std::cout << "Type the name in the Graph and press enter. Backspace to delete a character is allowed!"<< std::endl;
    std::string inputName = "";
    bool inputMode = true;
    SDL_StartTextInput(); // Enable text input

    while (inputMode) {
        while (SDL_PollEvent(e)) {
            if (e->type == SDL_QUIT) {
                inputMode = false;
            } else if (e->type == SDL_KEYDOWN) {
                if (e->key.keysym.sym == SDLK_RETURN) {
                    inputMode = false; // Stop input when Enter key is pressed
                    nodes->emplace_back(inputName,x,y);
                } else if (e->key.keysym.sym == SDLK_BACKSPACE && !inputName.empty()) {
                    inputName.pop_back(); // Backspace: remove the last character
                }else if (e->key.keysym.sym == SDLK_ESCAPE){
                    inputMode = false;
                    std::cout << "Abort Node creation" << std::endl;
                }
            } else if (e->type == SDL_TEXTINPUT) {
                // Append entered text to the inputName
                inputName += e->text.text;
            }
        }
    }
    SDL_StopTextInput();
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

