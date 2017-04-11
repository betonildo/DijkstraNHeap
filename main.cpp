#include "Graph.h"
#include "read_dimacs.h"
#include <iostream>
#include <assert.h>
#include <chrono>
#include <fstream>


int main(int argc, char** argv) {

    assert(argc == 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph g;

    read_dimacs(std::cin, g);
    
    // inicio
    auto start = std::chrono::system_clock::now();
    EdgeDistance ed = g.dijkstra(origin, dest);
    unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-start).count();
    std::cout << ed << std::endl;        

    return 0;
}