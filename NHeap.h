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
    
    unsigned int insert(T number) {
        int lastIndex = m_heap.size();
        unsigned int capacity = m_heap.capacity();
        if (lastIndex >= capacity) {
            printf("Resizing to %d\n", capacity * 2);
            m_heap.reserve(capacity * 2);
        }
        m_heap.push_back(number);
        unsigned int n_swaps = 0;
        m_heapfy(lastIndex, n_swaps);
        m_counter += 1;

        return n_swaps;
    }
    
    void setCapacity(unsigned long capacity) {
        m_heap.reserve(capacity);
    }

    void update(T element) {
        bool found = false;
        m_updateHeapdownAll(0, element, found);
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
                if (tmpChildValue > childValue)
                    childIndex = tmpChildIndex;
            }
        }

        // Mark root to be comparable distinguished
        m_heap[m_rootIndex] = T();

        // verify if the heapfy for all the tree from end to begining
        unsigned int n_swaps = 0;
        for (int i = m_heap.size() - 1; i >= m_rootIndex; i--) m_heapfy(i, n_swaps);

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
    
    void m_heapfy(int nodeIndex, unsigned int& num_swaps) {
        // if i'm root don't do anything
        if (nodeIndex == m_rootIndex) return;
        
        int parentIndex = parent(nodeIndex);
        // get vector references, much more elegant to use swap
        T& parent = m_heap[parentIndex];
        T& node = m_heap[nodeIndex];
        
        // if parent is higher than watching node, change their places in memory
        if (parent > node) {
            num_swaps += 1;
            m_swap(parent, node);
            m_heapfy(parentIndex, num_swaps);
        }
    }

    void m_updateHeapdownAll(int nodeIndex, T& element, bool& found = false) {

        if (found) return;

        T root = m_heap[nodeIndex];
        if (root == element) {
            found = true;
            m_heap[nodeIndex] = element;
            return;
        }
        else {
            for(int i = 0; i < m_aridity; i++) {
                if (hasChildNth(nodeIndex, i)) {
                    int childIndex = childNth(nodeIndex, i);
                    T childValue = m_heap[childIndex];
                    if (childValue == element) {
                        found = true;
                        m_heap[childIndex] = element;
                        return;
                    }
                    else m_updateHeapdownAll(childIndex, element, found);
                }
            }
        }

        return;
    }
    
    void m_swap(T& l, T& r) {
        T t = l;
        l = r;
        r = t;
    }
};

#endif /*NHEAP_H*/