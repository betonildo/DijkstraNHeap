#include <iostream>
#include <climits>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <functional>

#ifndef NHEAP_H
#define NHEAP_H

template<typename T>
class NHeap {
    
public:
    NHeap(int aridity) {
        m_aridity = aridity;
        m_heap.reserve(64);
        clearTree();        
    }
    
    void insert(T number) {
        int lastIndex = m_heap.size();
        unsigned int capacity = m_heap.capacity();
        if (lastIndex >= capacity) {
            unsigned int toreserve = capacity * 2;
            //printf("RESERVING. %d... %d..\n", capacity, toreserve);
            m_heap.resize(toreserve);
        }
        m_heap.push_back(number);
        m_heapfy(lastIndex);
        m_counter += 1;
    }
    
    void update(T element) {
        // todo: recusively bottom up to update
        bool wasUpdated = false;
        for (int i = 0; i < m_heap.size(); i++)
            if (T::SameKey(m_heap[i], element)) {
                m_heap[i] = element;
                wasUpdated = true;
                break;
            }

        if (!wasUpdated) insert(element);
    }
    
    int childNth(int index, int childNumber) {
        int nodeIndex = m_aridity * index + childNumber + 1;
        return nodeIndex;
    }

    bool hasChildNth(int index, int childNumber) {
        int nodeIndex = m_aridity * index + childNumber + 1;
        return nodeIndex < m_rootIndex + m_counter;
    }
    
    int parent(int nodeIndex) {
        int parentIndex = (int)((float)(nodeIndex - 1)/(float)m_aridity);
        return parentIndex;
    }
    
    bool empty() {
        return m_counter == 0;
    }
    
    bool hasNext() {
        return m_counter > 0;
    }

    T getNext() {
        // the extracted 
        T next = m_heap[m_rootIndex];
        
        // choose the children that will occupy the roots place
        int tmpChildIndex;
        T tmpChildValue;
        int childIndex = childNth(m_rootIndex, 0);
        T childValue = m_heap[childIndex];

        for (int i = 1; i < m_aridity; i++) {            
            // only do some thing if have a valid child
            if (hasChildNth(m_rootIndex, i)) {
                tmpChildIndex = childNth(m_rootIndex, i);
                tmpChildValue = m_heap[tmpChildIndex];
                if (T::CompareWeights(tmpChildValue, childValue))
                    childIndex = tmpChildIndex;
            }
        }

        // Mark root to be comparable distinguished
        m_heap[m_rootIndex] = T::Distinguished();

        // verify if the heapfy for all the tree from end to begining
        for (int i = m_heap.size() - 1; i >= m_rootIndex; i--) m_heapfy(i);

        m_counter -= 1;
        return next;
    }

    void clearTree() {
        m_rootIndex = 0;
        m_counter = 0;
        m_heap.clear();
    }    

    int size() {
        return m_heap.size();
    }

    void print() {
        std::cout << "[";
        for (unsigned i = 0; i < m_heap.size() - 1; i++) {
            auto e = m_heap[i];
            std::cout << e << ", ";
        }

        auto e = m_heap[m_heap.size() - 1];
        std::cout << e << "]" << std::endl;
    }

    std::vector<T> heapSorted() {
        std::vector<T> sortedArray;
        
        while(hasNext()) {            
            T next = getNext();
            sortedArray.push_back(next);
        }

        return sortedArray;
    }
    
private:
    std::vector<T> m_heap;
    int m_aridity;
    int m_counter;
    int m_rootIndex;
    
    void m_heapfy(int nodeIndex) {
        // if i'm root don't do anything
        if (nodeIndex == m_rootIndex) return;
        
        int parentIndex = parent(nodeIndex);
        // get vector references, much more elegant to use swap
        T& parent = m_heap[parentIndex];
        T& node = m_heap[nodeIndex];
        
        // if parent is higher than watching node, change their places in memory
        if (T::CompareWeights(parent, node)) {
            m_swap(parent, node);
            m_heapfy(parentIndex);
        }
    }
    
    void m_swap(T& l, T& r) {
        T t = l;
        l = r;
        r = t;
    }
};

#endif /*NHEAP_H*/