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
    int weight;
    Edge(Node* first ,Node* second, int weight);
};
void createEdgeBetweenNodes(int x, int y, Node *&firstNode, Node *&secondNode, std::vector<Edge>* edgeVector ,std::vector<Node>* nodeVector ,bool *oneNodeSelected,SDL_Event * e);
void removeEdgesFromVector(std::vector<Edge>* edgeVector, Node* nodeToRemove);
bool checkIfEdgeBetweenToNodes(std::vector<Edge> *edgeVector, Node* a, Node* b);

#endif //GRAPH_VISUALIZATION_EDGE_H
