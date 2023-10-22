//
// Created by afklex on 10/22/23.
//

#ifndef GRAPH_VISUALIZATION_EDGE_H
#define GRAPH_VISUALIZATION_EDGE_H

#include "header/Node.h"
class Edge {
public:
    Node* A;
    Node* B;
    Edge(Node* first ,Node* second);
};


#endif //GRAPH_VISUALIZATION_EDGE_H
