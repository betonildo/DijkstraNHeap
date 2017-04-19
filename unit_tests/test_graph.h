#include "Graph.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifndef DIJKSTRA_TEST
#define DIJKSTRA_TEST

class DijkstraTest {

public:

    static inline void testDijkstraM(std::ostream& os) {


        Graph g;
        std::srand(time(0));

        os << "# m, T /(n + m) log(n), inserts, deletes, updates" << std::endl;
        
        for (unsigned long i = 1; i < 20; i++) {
            
            g.clearCounters();
            
            unsigned long m = pow(2, i);
            unsigned long n = m;
            double time_sum = 0;
            generateGraph(g, n, m);

            

            for (int times = 0; times < 30; times++) {
                unsigned long origin = -1;
                unsigned long dest = -1;
                
                while(origin == dest) {
                    origin = std::rand() % g.heigherVertice();
                    dest = std::rand() % g.heigherVertice();
                }
                
                auto start = std::chrono::system_clock::now();
                g.dijkstra(origin, dest);
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                time_sum += elapsed;
            }            

            time_sum = time_sum / 30.0;
            double t_by_log = (double)time_sum / ((n + m) * log(n));
            os << m << " " << t_by_log << " # " << g.getNumberOfInserts() << " " << g.getNumberOfDeletes() << " " << g.getNumberOfUpdates() << std::endl;
        }
    }
    
    static inline void testDijkstraN(std::ostream& os) {


        Graph g;
        std::srand(time(0));

        os << "# m, T /(n + m) log(n), inserts, deletes, updates" << std::endl;
        
        for (unsigned long i = 1; i < 20; i++) {
            
            g.clearCounters();
            
            unsigned long m = pow(2, i);
            unsigned long n = m;
            double time_sum = 0;
            generateGraph(g, n, m);

            

            for (int times = 0; times < 30; times++) {
                unsigned long origin = -1;
                unsigned long dest = -1;
                
                while(origin == dest) {
                    origin = std::rand() % g.heigherVertice();
                    dest = std::rand() % g.heigherVertice();
                }
                
                auto start = std::chrono::system_clock::now();
                g.dijkstra(origin, dest);
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                time_sum += elapsed;
            }            

            time_sum = time_sum / 30.0;
            double t_by_log = (double)time_sum / ((n + m) * log(n));
            os << m << " " << t_by_log << " # " << g.getNumberOfInserts() << " " << g.getNumberOfDeletes() << " " << g.getNumberOfUpdates() << std::endl;
        }
    }

    static inline void generateGraph(Graph& g, unsigned long n, unsigned long m) {
        std::srand(time(0));
        for (unsigned long i = 1; i <= n; i++) {
            
            double div = m/(double)n;
            
            for (unsigned long j = 1; j <= div; j++) {

                g.set(i, j * div + i, std::rand() % 10000);
            }
        }
    }
};

#endif /*DIJKSTRA_TEST*/