#include "NHeap.h"
#include "Edge.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <time.h>

namespace NHeapTest {
    void testNinstancesMtimesIntoO_ariTree(std::ostream& os, int n, int m, int o) {
        
        std::srand(time(0));
        
        NHeap<Edge> h(o);

        unsigned long long timesSum = 0;

        for (int turn = 0; turn < m; turn++) {
            auto start = std::chrono::system_clock::now();
            for (int i = 0; i < n; i++) {
                int v = std::rand();
                int w = std::rand();
                h.insert({v, w});
            }
            auto end = std::chrono::system_clock::now();
            timesSum += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        }

        os << n << " " << timesSum / (double)m << std::endl;
    }

    void testFromNtoNinstancesAtStepMtimes_O_aridity(std::ostream& os, int ni, int ne, int step, int m, int o) {

        os << "# Instances Insert_Time_ms " << std::endl;

        for(; ni <= ne; ni += step) {
            NHeapTest::testNinstancesMtimesIntoO_ariTree(os, ni, m, o);
        }
    }
}

