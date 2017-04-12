#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef DIJKSTRA_TEST
#define DIJKSTRA_TEST

class DijkstraTest {

public:

    static inline void testDijkstra(std::ostream& os) {


        Graph g;
        std::srand(time(0));
        
        for (unsigned long i = 0; i < 20; i++) {
            
            g.clearCounters();
            
            unsigned long n = pow(2, 20);
            unsigned long m = pow(2, i);
            unsigned long time_sum = 0;
            generateGraph(g, n, m);

            for (int times = 0; times < 30; times++) {
                unsigned long origin = std::rand() % g.heigherVertice();
                unsigned long dest = std::rand() % g.heigherVertice();
                
                auto start = std::chrono::system_clock::now();
                g.dijkstra(origin, dest);
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

                time_sum += elapsed;
            }

            time_sum = time_sum / 30;

            os << g.getNumberOfInserts() << " " << n << " " << g.getNumberOfDeletes() << " " << n << " " << g.getNumberOfUpdates() << " " << m << std::endl;
        }
    }
    
    static inline void generateGraph(Graph& g, unsigned long n, unsigned long m) {
        std::srand(time(0));
        for (unsigned long i = 1; i <= n; i++) {
            
            unsigned long div = m/n;
            
            for (unsigned long j = 1; j <= div; j++) {

                g.set(i, j * div + i, std::rand() % 10000);
            }
        }
    }
};

#endif /*DIJKSTRA_TEST*/