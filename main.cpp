#include "NHeap.h"
#include "Graph.h"
#include <iostream>
#include <assert.h>
#include <sstream>
#include <chrono>

// void testNHeap();
void read_dimacs(std::istream& in, Graph& g);

int main(int argc, char** argv) {
    // testNHeap();
    assert(argc == 3);
    int origin = atoi(argv[1]);
    int dest = atoi(argv[2]);

    Graph g;
    
    read_dimacs(std::cin, g);
    
    // inicio
    std::chrono::system_clock::time_point t = std::chrono::system_clock::now();
    int distance = g.dijkstra(origin, dest);
    // medição
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-t).count() << std::endl;
    std::cout << distance << std::endl;

    return 0;
}

void read_dimacs(std::istream& in, Graph& g) {
    
    unsigned int n, m;
    std::string line="", dummy;
    while (line.substr(0,4) != "p sp")
        getline(in,line);
    
    // (1) get nodes and edges
    std::stringstream linestr;
    linestr.str(line);
    linestr >> dummy >> dummy >> n >> m;
    g.setSize(n);
    
    unsigned i = 0;
    
    while (i < m) {
        
        getline(in,line);
        
        if (line.substr(0,2) == "a ") {
            std::stringstream arc(line);
            unsigned u,v,w;
            char ac;
            arc >> ac >> u >> v >> w;
            // processar arco (u,v) com peso w
            g.set(u, v, w);
            i++;
        }
    }
}


// void testNHeap() {
//     auto comparator = [](Edge& a, Edge &b) -> bool {
//         return a.weight > b.weight;
//     };
    
//     NHeap<Edge> h(2);
//     h.setComparator(comparator);
    
//     std::srand(time(0));
//     int numNumbers = 10;
//     for (int i = 0; i < numNumbers; i++) {
//         int number = std::rand();
//         h.insert(number);
//     }
    
//     auto sortedArray = h.heapSorted();

//     std::cout << "HEAP" << std::endl;

//     for (int i = 0; i < sortedArray.size(); i++) {
//         std::cout << i << " = " << sortedArray[i] << std::endl;
//     }
    
// }