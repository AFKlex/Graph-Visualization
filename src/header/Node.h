//
// Created by afklex on 10/22/23.
//

#ifndef GRAPH_VISUALIZATION_NODE_H
#define GRAPH_VISUALIZATION_NODE_H
#include<iostream>
#include<vector>
#include<SDL2/SDL.h>
#include"header/AppConfig.h"

class Node {
public:
    std::string name;
    int x,y;
    Node(std::string name, int x, int y);
    bool operator==(const Node& other) const;
};

void append_Node(std::vector<Node> *nodes,int x, int y, SDL_Event * e);
Node* checkNodeExistAtPosition(std::vector<Node> *nodeVector, int x , int y);
void removeNodeFromNodeVector(std::vector<Node>* nodeVector, const Node *nodeToRemove);


#endif //GRAPH_VISUALIZATION_NODE_H
