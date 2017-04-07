#include <vector>
#include <map>
#include <climits>
#include <iostream>
#include "NHeap.h"

#ifndef GRAPH_H
#define GRAPH_H

#define INF INT_MAX

#pragma pack(push, 0)

struct Edge {
    int to;
    int weight;
    
    Edge& operator=(const Edge& b) {
        to = b.to;
        weight = b.weight;
        return *this;
    }
    
    static Edge Distinguished() {
        return {INF, INF};
    }
    
    inline static bool SameKey(Edge& a, Edge& b) {
        return a.to == b.to;
    }
    
    inline friend int operator>(Edge& a, Edge& b) {
        return a.weight > b.weight;
    }
    
    inline friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
        os << "{" << e.to << ", " << e.weight << "}";
        return os;
    }
};

#pragma pack(pop)

class Graph {

public:
    Graph() {
        m_graph.clear();
    }
    
    void setSize(int numberOfElements) {
        m_numberOfElements = numberOfElements;
    }
    
    void set(int origin, int dest, int weight) {
        m_graph[origin].push_back({dest, weight});
    }
    
    int dijkstra(int origin,  int dest) {
        
        int dist[m_numberOfElements];
        bool visited[m_numberOfElements];
        
        //init distances and 
        for(int i = 0; i < m_numberOfElements; i++) {
            dist[i] = INF;
            visited[i] = false;
        }
        
        NHeap<Edge> h(2);
        
        dist[origin] = 0;
        
        h.insert({origin, 0});
        
        while (!h.empty()) {
            
            Edge e = h.getNext();
            int u = e.to;
            
            if (!visited[u]) {
                
                visited[u] = true;
                
                for(auto neibor : m_graph[u]) {
                    
                    int v = neibor.to;
                    int w = neibor.weight;

                    if (dist[v] == INF) {
                        dist[v] = dist[u] + w;
                        h.insert({v, dist[v]});
                    }
                    else if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        std::cout << "UPDATE" << std::endl;
                        h.update({v, dist[v]});
                    }
                }
            }
        }
        
        return dist[dest];
    }

private:
    int m_numberOfElements;
    std::map<int, std::vector<Edge> > m_graph;
    
};

#endif /*GRAPH_H*/
