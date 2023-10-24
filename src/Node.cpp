//
// Created by afklex on 10/22/23.
//

#include "header/Node.h"
Node::Node(std::string name, int x, int y){
    this->x = x;
    this->y = y;
    this->degree = 0;

    this->name = name;
}

// Implementation of the equality operator (==) for Node objects
bool Node::operator==(const Node& other) const {
    return (this->x == other.x) && (this->y == other.y);
}

void Node::setDegree(int i) {
    this->degree = i;
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

Node* checkNodeExistAtPosition(std::vector<Node> *nodeVector, int x , int y){
    int circleRadius = AppConfig::NODE_RADIUS/2+5;
    //std::cout <<"X and y " << x << " "<<y << std::endl;
    for(Node &node : *nodeVector){
        //std::cout << node.x << " " << node.y << std::endl;

        if(node.x - circleRadius  <= x && x <= node.x + circleRadius){
            if(node.y - circleRadius  <= y && y <= circleRadius  + node.y){
                //std::cout << "Found Node at position" << std::endl;
                return &node;
            }else{
               // std::cout << "Found no Node at position" << std::endl;
            }
        }else{
            //std::cout << "Found no Node at position" << std::endl;
        }
    }
    return nullptr;
}

void removeNodeFromNodeVector(std::vector<Node>*nodeVector, const Node *nodeToRemove){
    auto it = std::find(nodeVector->begin(), nodeVector->end(), *nodeToRemove);
    if (it != nodeVector->end()) {
        std::cout << "Remove node!" << std::endl;
        nodeVector->erase(it);
        //std::cout << "Vector Size: " << nodeVector->size() <<std::endl;
    } else {
        std::cout << "No element was found. So nothing was removed" << std::endl;
    }

}

void printNodeDegree(std::vector<Node> *vectorNodes){
    for(const auto& node : *vectorNodes){
        std::cout << "Degree of Node " << node.name << " : " << node.degree << std::endl;
    }
}

