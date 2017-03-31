#include <iostream>
#include <climits>
#include <vector>
#include <cstdlib>
#include <ctime>

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

    bool hasChildNth(int index, int childNumber) {
        int nodeIndex = m_aridity * index + childNumber + 1;
        return nodeIndex < m_rootIndex + m_counter;
    }
    
    int parent(int nodeIndex) {
        int parentIndex = (int)((float)(nodeIndex - 1)/(float)m_aridity);
        return parentIndex;
    }
    
    bool hasNext() {
        return m_counter > 0;
    }

    int getNext() {
        // the extracted 
        int next = m_heap[m_rootIndex];
        
        // choose the children that will occupy the roots place
        int tmpChildIndex, tmpChildValue;
        int childIndex = childNth(m_rootIndex, 0);
        int childValue = m_heap[childIndex];

        for (int i = 1; i < m_aridity; i++) {
            
            // only do some thing if have a valid child
            if (hasChildNth(m_rootIndex, i)) {
                tmpChildIndex = childNth(m_rootIndex, i);
                tmpChildValue = m_heap[tmpChildIndex];
                if (tmpChildValue > childValue) childIndex = tmpChildIndex;
            }
        }

        // Mark root to be extremely high
        m_heap[m_rootIndex] = INT_MAX;
        
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

    std::vector<int> heapSorted() {
        std::vector<int> sortedArray;
        
        while(hasNext()) {            
            int next = getNext();
            sortedArray.push_back(next);
        }

        return sortedArray;
    }

    void printHeap() {
        std::cout << "[";
        for (int i = m_rootIndex; i < m_heap.size() - 1; i++) {
            std::cout << m_heap[i] << ", ";
        }

        std::cout << m_heap[m_heap.size() - 1] << "]" << std::endl;
    }

    void printHeapChildInfo() {

        for (int i = 0; i < m_heap.size(); i++) {
            std::cout << "Node Value " << m_heap[i] << " Children: ";
            for (int ci = 0; ci < m_aridity; ci++) {

                if (hasChildNth(i, ci)) {
                    int childIndex = childNth(i, ci);
                    int childValue = m_heap[childIndex];
                    std::cout << childValue << "; ";
                }
                else {
                    std::cout << "No Child " << ci << "; ";
                }
            }
            std::cout << std::endl;
        }
    }
    
private:
    std::vector<int> m_heap;
    int m_aridity;
    int m_counter;
    int m_rootIndex;
    
    bool m_heapfy(int nodeIndex) {
        // if i'm root don't do anything
        if (nodeIndex == m_rootIndex) return false;        
        
        int parentIndex = parent(nodeIndex);
        // get vector references, much more elegant to use swap
        int& parent = m_heap[parentIndex];
        int& node = m_heap[nodeIndex];
        
        // if parent is higher than watching node, change their places in memory
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
    
    std::srand(time(0));
    int numNumbers = 10;
    for (int i = 0; i < numNumbers; i++) {
        int number = std::rand();
        h.insert(number);
    }
    
    h.printHeap();

    auto sortedArray = h.heapSorted();

    std::cout << "HEAP" << std::endl;

    for (int i = 0; i < sortedArray.size(); i++) {
        std::cout << i << " = " << sortedArray[i] << std::endl;
    }
    
    return 0;
}
