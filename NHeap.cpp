#include <iostream>
#include <stdlib.h>
#include <vector>

class NHeap {
    
public:
    NHeap(int aridity) {
        m_aridity = aridity;
        clearTree();
    }
    
    void insert(int number) {
        int lastIndex = m_heap.size();
        m_heap.push_back(number);
        m_heapfy(lastIndex);
        m_counter += 1;
    }
    
    int childNth(int index, int childNumber) {
        int nodeIndex = m_aridity * index + childNumber + 1;
        return nodeIndex;
    }
    
    int parent(int nodeIndex) {
        int parentIndex = (int)((nodeIndex - 1)/(float)m_aridity);
        return parentIndex;
    }
    
    bool hasNext() {
        return m_counter > m_rootIndex;
    }

    int getNext() {
        int next = m_heap[m_rootIndex];

        // choose the children that will occupy the roots place
        int tmpChildIndex, tmpChildValue;
        int childIndex = childNth(m_rootIndex, 0);
        int childValue = m_heap[childIndex];

        for (int i = 1; i < m_aridity; i++) {
            tmpChildIndex = childNth(m_rootIndex, i);
            tmpChildValue = m_heap[tmpChildIndex];
            if (tmpChildValue < childValue) childValue = tmpChildValue;
        }

        // verify if the heapfy for all the tree from end to begining
        for (int i = m_heap.size() - 1; i > m_rootIndex; i--) {
            m_heapfy(i);
        }

        // root is now increased in one to avoid memcpy and 
        m_rootIndex += 1;
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

    std::vector<int> heapSorted() {
        std::vector<int> sortedArray;
        
        while(hasNext()) {
            int next = getNext();
            sortedArray.push_back(next);    
        }

        return sortedArray;
    }
    
private:
    std::vector<int> m_heap;
    int m_aridity;
    int m_counter;
    int m_rootIndex;
    
    bool m_heapfy(int nodeIndex) {

        if (nodeIndex == m_rootIndex) return false;        
        
        int parentIndex = parent(nodeIndex);
        int parent = m_heap[parentIndex];        
        int node = m_heap[nodeIndex];
        
        if (parent > node) {
            m_swap(parent, node);
            return m_heapfy(parentIndex) || true;
        }
        
        return false;
    }
    
    void m_swap(int& l, int& r) {
        int t = l;
        l = r;
        r = t;
    }
};


int main() {

    NHeap h(2);
    h.insert(10);
    h.insert(50);
    h.insert(30);
    h.insert(9);
    h.insert(40);
    h.insert(11);

    auto sortedArray = h.heapSorted();

    std::cout << "HEAP" << std::endl;

    for (int i = 0; i < sortedArray.size(); i++) {
        std::cout << i << " = " << sortedArray[i] << std::endl;
    }
    
    return 0;
}
