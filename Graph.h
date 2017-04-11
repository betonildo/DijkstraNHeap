#include <vector>
#include <map>

#include <iostream>
#include "NHeap.h"
#include "Edge.h"

#ifndef GRAPH_H
#define GRAPH_H

class Graph {

public:
    Graph() {
        m_graph.clear();
    }

    void setHeapAridity(int aridity) {
        m_aridity = aridity;
    }
    
    void setSize(int numberOfElements) {
        m_numberOfElements = numberOfElements + 1;
    }
    
    void set(int origin, int dest, int weight) {
        m_graph[origin].push_back({dest, weight});
    }
    
    EdgeDistance dijkstra(int origin,  int dest) {
        
        // instantiate distances calculated
        EdgeDistance distances[m_numberOfElements];

        // if some over or under flow occurs, the distance is infinity
        if (dest >= m_numberOfElements || origin >= m_numberOfElements || dest < 0 || origin < 0) return distances[0];
        // The distance to it self is 0
        distances[origin].distanceTo = 0;
        
        // instantiate the heap and insert the vertice origin as starting point
        NHeap<Edge> edgesHeap(m_aridity);
        edgesHeap.insert({origin, 0});
        
        while (!edgesHeap.empty()) {
            
            // get next and delete the minimun (deletemin* variant name)
            Edge e = edgesHeap.getNext();
            int u = e.to;
            
            // if this vertice was not visited yet, look for each neibor 
            // and verify the distance to the origin
            if (distances[u].visited == false) {                
                distances[u].visited = true;
                
                for(auto neibor : m_graph[u]) {
                    
                    int v = neibor.to;
                    int w = neibor.weight;
                    int cost = distances[u].distanceTo + w;
                    // if the current distance is infinity (not calculated yet)
                    // and the cost is less than infinity we try the path by this
                    // vertice.
                    if (distances[v].infinity && cost < distances[v].distanceTo) {
                        distances[v].infinity = false;
                        distances[v].distanceTo = cost;
                        edgesHeap.insert({v, cost});
                    }
                    // else if we already have an instance of the vertice on the heap,
                    // we must update the distance to origin reling on distances pre
                    // calculated.
                    else if (cost < distances[v].distanceTo) {
                        distances[v].distanceTo = cost;
                        edgesHeap.update({v, cost});
                    }
                }
            }
        }
        
        return distances[dest];
    }

    void print(unsigned ni) {
        
        printf("%d ", ni);
        for(auto neibor : m_graph[ni]) {
            printf("-(%d)-> ", neibor.weight);
            print(neibor.to);
        }

        if (m_graph[ni].size() == 0)
            printf("\n");
    }

private:
    int m_aridity;
    int m_numberOfElements;
    std::map<int, std::vector<Edge> > m_graph;
    
};

#endif /*GRAPH_H*/
