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
void createEdgeBetweenNodes(int x, int y, Node *&firstNode, Node *&secondNode, std::vector<Edge>* edgeVector ,std::vector<Node>* nodeVector ,bool *oneNodeSelected);
void removeEdgesFromVector(std::vector<Edge>* edgeVector, Node* nodeToRemove);
bool checkIfEdgeBetweenToNodes(std::vector<Edge> *edgeVector, Node* a, Node* b);

#endif //GRAPH_VISUALIZATION_EDGE_H
