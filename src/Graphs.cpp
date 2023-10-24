//
// Created by afklex on 10/24/23.
//

#include "header/Graphs.h"


void updateNodeDegree(std::vector<Edge> *edgeVector, std::vector<Node>* nodeVector){
    int degree;

    for(auto & node: *nodeVector){
        degree = 0;

        for(auto & i : *edgeVector){
            if(*(i.A) == node){
                degree++;
            }
            if(*(i.B) == node){
                degree++;
            }
        }
        //std::cout << "Node Degree: " << degree << std::endl;
        node.setDegree(degree);
    }
    //std::cout << "Node Degree: " << degree << std::endl;
}

void printAdjacencyMatrix(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<Node>& nodeVector) {
    std::cout << "\t";
    for (const Node& node : nodeVector) {
        std::cout << node.name << "\t";
    }
    std::cout << std::endl;

    // Print the adjacency matrix
    for (size_t i = 0; i < adjacencyMatrix.size(); i++) {
        // Print row header (node name)
        std::cout << nodeVector[i].name << "\t";
        for (size_t j = 0; j < adjacencyMatrix[i].size(); j++) {
            std::cout << adjacencyMatrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

void createAdjacencyMatrix(std::vector<Node> *nodeVector, std::vector<Edge> *edgeVector){
    unsigned long int size;
    size = nodeVector->size();
    std::vector<std::vector<int>> adjacencyMatrix(size, std::vector<int>(size, 0));;
    for(int i = 0; i<size; i++){
        for(int j =0; j < size; j++){
            if(checkIfEdgeBetweenToNodes(edgeVector,&nodeVector->at(i), &nodeVector->at(j))){
                adjacencyMatrix[i][j] +=1;
                // If Edge is a self loop we need to add 2 so one again.
                if(&nodeVector->at(i) == &nodeVector->at(j)){
                    adjacencyMatrix[i][j]+= 1;
                }
            }
        }
    }
    printAdjacencyMatrix(adjacencyMatrix, *nodeVector);

}
