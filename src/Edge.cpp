//
// Created by afklex on 10/22/23.
//

#include "header/Edge.h"
Edge::Edge(Node* first, Node* second){
    this->A = first;
    this->B = second;
}

void createEdgeBetweenNodes(int x, int y, Node *&firstNode, Node *&secondNode, std::vector<Edge>* edgeVector ,std::vector<Node>* nodeVector ,bool *oneNodeSelected){
    // Connect two nodes
    Node *selection = checkNodeExistAtPosition(nodeVector,x, y);

    if(*oneNodeSelected && selection != nullptr){
        secondNode = selection;
        edgeVector->emplace_back(firstNode, secondNode);
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
