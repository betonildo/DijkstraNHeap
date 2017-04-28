#include "Graph.h"
#include "read_dimacs.h"
#include <iostream>
#include <assert.h>
#include <chrono>
#include <fstream>


int main(int argc, char** argv) {

    assert(argc >= 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph g;

    if (argc == 3) {
        read_dimacs(std::cin, g);
    }
    else {
        std::ifstream f(argv[3]);
        read_dimacs(f, g);
    }
    
    // inicio
    EdgeDistance ed = g.dijkstra(origin, dest);
    std::cout << ed << std::endl;        

    return 0;
}