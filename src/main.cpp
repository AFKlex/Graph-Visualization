//
// Created by afklex on 10/22/23.
//
#include<iostream>
#include "header/window.h"
#include "header/Node.h"
#include "header/AppConfig.h"
#include "header/Edge.h"
int main() {

    // Node
    Node a = Node("A", 100,100);
    Node b = Node("B", 200,200);

    Node c = Node("C", 500,350);
    Node d = Node("D", 400,400);
    Node f = Node("f", 150,50);
    Edge edgeAB = Edge(&a,&b);
    Edge edgeCD = Edge(&c, &d);
    Edge edgeBD = Edge(&d,&b);
    Edge edgeBF = Edge(&f, &b);


    if(!initGame()){
        std::cout << "Failed to init the Game! SDL Error:  " << SDL_GetError()<< std::endl;
    }else if(!initFont()){
        std::cout << "Failed to load Font! TTF Error: " << TTF_GetError() << std::endl;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        drawNode(a);
        drawNode(b);
        drawNode(c);
        drawNode(d);
        drawNode(f);
        drawEdge(edgeCD);
        drawEdge(edgeAB);
        drawEdge(edgeBD);
        drawEdge(edgeBF);
        SDL_RenderPresent(AppConfig::RENDERER);
        SDL_Delay(10);
    }

    destroyGame();
    return 0;

}