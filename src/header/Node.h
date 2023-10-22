//
// Created by afklex on 10/22/23.
//

#ifndef GRAPH_VISUALIZATION_NODE_H
#define GRAPH_VISUALIZATION_NODE_H
#include<iostream>


class Node {
public:
    std::string name;
    int x,y;
    Node(std::string name, int x, int y);
};


#endif //GRAPH_VISUALIZATION_NODE_H
