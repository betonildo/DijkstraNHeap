#include "NHeap.h"
#include "Edge.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <time.h>
#include <math.h>

#define TIMES_RUN_TESTS 10

class NHeapTest {

public:

    static inline void testInsert(std::ostream& os) {
        NHeap<Edge> h(2);

        unsigned long n_max = pow(2, 20);
        unsigned long n = 1;
        unsigned short times_run = 10;
        unsigned long timesSum = 0;
        unsigned long timesSwap = 0;
        
        os << "# Swaps x Time" << std::endl;

        // record the times for T1 to T20
        for (n = n_max; n >= 1; n -= 1) {

            h.setCapacity(n);
            timesSum = 0;
            timesSwap = 0;

            for (times_run = 0; times_run < TIMES_RUN_TESTS; times_run++) {
                auto start = std::chrono::system_clock::now();
                for (unsigned long i = 0; i < n; i++) {
                    int v = std::rand();
                    int w = std::rand();
                    timesSwap += h.insert({v, w});
                }
                auto end = std::chrono::system_clock::now();
                timesSum += std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                h.clearTree();
            }

            os << timesSwap / TIMES_RUN_TESTS / (double) n << " " << timesSum / (double) TIMES_RUN_TESTS << std::endl;
        }
    }
};