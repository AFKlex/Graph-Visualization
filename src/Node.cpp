//
// Created by afklex on 10/22/23.
//

#include "header/Node.h"
Node::Node(std::string name, int x, int y){
    this->x = x;
    this->y = y;
    this->name = name;
}

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

