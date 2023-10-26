//
// Created by afklex on 10/22/23.
//

#include "header/Edge.h"
Edge::Edge(Node* first, Node* second, int weight){
    this->A = first;
    this->B = second;
    this->weight = weight;
}

void createEdgeBetweenNodes(int x, int y, Node *&firstNode, Node *&secondNode, std::vector<Edge>* edgeVector ,std::vector<Node>* nodeVector ,bool *oneNodeSelected,SDL_Event * e){
    // Connect two nodes
    Node *selection = checkNodeExistAtPosition(nodeVector,x, y);

    if(*oneNodeSelected && selection != nullptr){
        std::cout << "is not weighted Graph" << std::endl;
        secondNode = selection;

        if(AppConfig::isWeightedGraph){
            std::cout << "Type the Weight for the Edge and press enter:"<< std::endl;
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
                            secondNode = selection;
                            edgeVector->emplace_back(firstNode, secondNode, std::stoi(inputName));
                            *oneNodeSelected = false;
                            firstNode = nullptr;
                            secondNode = nullptr;
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

        }else{
            edgeVector->emplace_back(firstNode, secondNode, 0);
        }

        *oneNodeSelected = false;
        firstNode = nullptr;
        secondNode = nullptr;

    }else if(selection != nullptr){
        //std::cout << "First node was picked!" << std::endl;
        *oneNodeSelected  = true;
        firstNode = selection;
    }else{
        std::cout << "No node was picked!" << std::endl;
    }

}

void removeEdgesFromVector(std::vector<Edge>* edgeVector, Node* nodeToRemove) {
    std::vector<int> indicesToRemove;
    if(edgeVector != nullptr && nodeToRemove != nullptr){
        for (int i = edgeVector->size() - 1; i >= 0; i--) {
            if (edgeVector->at(i).A == nodeToRemove || edgeVector->at(i).B == nodeToRemove) {
                indicesToRemove.push_back(i);
            }
        }

        for (int i : indicesToRemove) {
            edgeVector->erase(edgeVector->begin() + i);
            std::cout << "Vector Size: " << edgeVector->size() <<std::endl;
        }
    }else{
        std::cout << "Could not Remove Edge from vector. Either noteToRemove or edgeVector was a nullptr" << std::endl;
    }

}

bool checkIfEdgeBetweenToNodes(std::vector<Edge> *edgeVector, Node* a, Node* b){
    for (auto &i: *edgeVector)
        if ((i.A == a && i.B == b) || (i.A == b && i.B == a))
            return true;

    return false;
}
