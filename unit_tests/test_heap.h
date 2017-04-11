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

        unsigned long n_max = pow(2, 20) - 1;
        unsigned short times_run = 10;
        unsigned long timesSwap = 0;
        unsigned long E = 0;
        
        os << "# Swaps x Insert_Numbers" << std::endl;

        // record the times for T1 to T20
        for (unsigned long i = 0, n = 0; n <= n_max; n = pow(2, i), i++) {

            E = pow(2, i) * i;

            h.setCapacity(n);
            timesSwap = 0;

            for (times_run = 0; times_run < TIMES_RUN_TESTS; times_run++) {
                
                for (unsigned long i = 0; i <= n; i++) {
                    int v = std::rand();
                    int w = std::rand();
                    timesSwap += h.insert({v, w});
                }
                h.clearTree();
            }
            os << timesSwap / (double)TIMES_RUN_TESTS << " ";
            os << n << " ";
            os << E;
            os << std::endl;
        }
    }
};