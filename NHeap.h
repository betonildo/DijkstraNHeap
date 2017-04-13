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
        if (lastIndex >= capacity) m_heap.reserve(capacity * 2);
        m_heap.push_back(number);
        unsigned long n_swaps = 0;
        m_heapfy(lastIndex, n_swaps);
        m_counter += 1;
        return n_swaps;
    }

    void setCapacity(unsigned long capacity) {
        m_heap.reserve(capacity);
    }

    int update(T element) {
        int nodeIndex = m_updateHeapdownAll(0, element);
        unsigned long n_swaps = 0;
        if (nodeIndex >= 0) {
            m_heap[nodeIndex] = element;
            // try to update upwards.
            m_heapfy(nodeIndex, n_swaps);
            // if no swap was made upper, then maybe some swap
            // can be needed down
            if (n_swaps == 0) m_heapfyDown(nodeIndex, n_swaps);
        }
        return n_swaps;
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
        unsigned long n_swaps;
        return getNext(n_swaps);
    }

    T getNext(unsigned long& n_swaps) {

        // the extracted
        T next = m_heap[m_rootIndex];

        // Mark root to be comparable distinguished
        m_heap[m_rootIndex] = T();

        // verify if the heapfy for all the tree from end to begining
        m_heapfyDown(m_rootIndex, n_swaps);
        m_counter -= 1;
        return next;
    }

    void clearTree() {
        m_rootIndex = 0;
        m_counter = 0;
        m_heap.clear();
        m_heap.erase(m_heap.begin(), m_heap.end());
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

    void m_heapfy(int nodeIndex, unsigned long& num_swaps) {
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

    void m_heapfyDown(int nodeIndex, unsigned long& num_swaps) {

        if (nodeIndex == m_counter + 1) return;

        // verify heap property for each of it's children
        for (int i = 0; i < m_aridity; i++) {

            if (hasChildNth(nodeIndex, i)) {

                int childIndex = childNth(nodeIndex, i);
                T& childValue = m_heap[childIndex];
                T& nodeValue = m_heap[nodeIndex];

                if (nodeValue > childValue) {
                    num_swaps += 1;
                    m_swap(nodeValue, childValue);
                    m_heapfyDown(childIndex, num_swaps);
                }
            }
        }
    }

    int m_updateHeapdownAll(int nodeIndex, T& element) {

        T root = m_heap[nodeIndex];
        if (root == element) return nodeIndex;
        else {
            for(int i = 0; i < m_aridity; i++) {
                if (hasChildNth(nodeIndex, i)) {
                    int childIndex = childNth(nodeIndex, i);
                    T childValue = m_heap[childIndex];
                    if (childValue == element) return childIndex;
                    else return m_updateHeapdownAll(childIndex, element);
                }
            }
        }

        return -1;
    }

    void m_swap(T& l, T& r) {
        T t = l;
        l = r;
        r = t;
    }
};

#endif /*NHEAP_H*/
