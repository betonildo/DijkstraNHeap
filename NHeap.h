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
        clearTree();
    }
    
    void setComparator(std::function<bool(T&, T&)> comparator) {
        m_comparator = comparator;
    }
    
    void insert(T number) {
        int lastIndex = m_heap.size();
        m_heap.push_back(number);
        m_heapfy(lastIndex);
        m_counter += 1;
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
                if (m_comparator(tmpChildValue, childValue)) childIndex = tmpChildIndex;
            }
        }

        // Mark root to be comparable distinguished
        m_heap[m_rootIndex] = T::Distinguished();
        
        // change places to choose the min child to occupy the root position
        m_swap(m_heap[m_rootIndex], m_heap[childIndex]);
        

        // verify if the heapfy for all the tree from end to begining
        for (int i = m_heap.size() - 1; i >= m_rootIndex; i--) {
            m_heapfy(i);
        }
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
    std::function<bool(T&, T&)> m_comparator;
    
    bool m_heapfy(int nodeIndex) {
        // if i'm root don't do anything
        if (nodeIndex == m_rootIndex) return false;        
        
        int parentIndex = parent(nodeIndex);
        // get vector references, much more elegant to use swap
        T& parent = m_heap[parentIndex];
        T& node = m_heap[nodeIndex];
        
        // if parent is higher than watching node, change their places in memory
        if (m_comparator(parent, node)) {
            m_swap(parent, node);
            return m_heapfy(parentIndex) || true;
        }
        
        return false;
    }
    
    void m_swap(T& l, T& r) {
        T t = l;
        l = r;
        r = t;
    }
};

#endif /*NHEAP_H*/