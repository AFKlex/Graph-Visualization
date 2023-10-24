//
// Created by afklex on 10/24/23.
//

#ifndef GRAPH_VISUALIZATION_GRAPHS_H
#define GRAPH_VISUALIZATION_GRAPHS_H
#include "header/Node.h"
#include "header/Edge.h"

void updateNodeDegree(std::vector<Edge> *edgeVector, std::vector<Node>* nodeVector);
void createAdjacencyMatrix(std::vector<Node> *nodeVector, std::vector<Edge> *edgeVector);

#endif //GRAPH_VISUALIZATION_GRAPHS_H
