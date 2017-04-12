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
        
        os << "#Tempos x Swaps x E" << std::endl;

        NHeap<Edge> h(2);

        for (unsigned long i = 1; i <= 23; i++) {

            h.clearTree();

            unsigned long E = pow(2, i) * i;
            
            unsigned long n = pow(2, i) - 1;
            
            unsigned long n_swaps = 0;

            unsigned long elapsed_sum = 0;

            for (int times_run = 0; times_run < TIMES_RUN_TESTS; times_run++) {
                h.clearTree();
                auto start = std::chrono::system_clock::now();
                for (unsigned long keycount = n; keycount >= 1; keycount--) {
                    n_swaps += h.insert({keycount, keycount});
                }
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                elapsed_sum += elapsed;
            }

            os << elapsed_sum / (double) TIMES_RUN_TESTS << " " << n_swaps / (double) TIMES_RUN_TESTS << " " << E << " " << n << std::endl;
        }
    }

    static inline void testUpdate(std::ostream& os) {

        NHeap<Edge> h(2);

        os << "#Tempos x Swaps" << std::endl;

        for (unsigned long i = 1; i <= 20; i++) {

            h.clearTree();

            unsigned long E = pow(2, i) * i;

            unsigned long n_keys1 = pow(2, i) - 1;
            unsigned long values1 = pow(2, i) + 1;
            
            unsigned long n_keys2 = pow(2, i);
            unsigned long values2 = pow(2, i) + 2;
            
            unsigned long updatevalue = pow(2, i);

            unsigned long keystartmark = 0;

            unsigned long n_swaps = 0;

            // update the second location
            unsigned long elapsed_sum = 0;

            for (int times_run = 0; times_run < TIMES_RUN_TESTS; times_run++) {
                
                h.clearTree();

                // insert the first lotation
                for (unsigned long keycount = 1; keycount <= n_keys1; keycount++) {
                    h.insert({keycount, values1});
                    keystartmark = keycount;
                }

                // insert the second lotation
                for (unsigned long keycount = 1; keycount <= n_keys2; keycount++) {
                    h.insert({keycount + keystartmark, values2});
                }           
            
                auto start = std::chrono::system_clock::now();
                for (unsigned long keycount = 1; keycount <= n_keys2; keycount++) {
                    updatevalue -= 1;
                    n_swaps += h.update({keycount + keystartmark, updatevalue});
                }
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                elapsed_sum += elapsed;
            }

            os << elapsed_sum / (double) TIMES_RUN_TESTS << " " << n_swaps / (double) TIMES_RUN_TESTS << " " << E << " " << n_keys2 << std::endl;
        }
    }

    static inline void testDeletemin(std::ostream& os) {
        
        std::srand(time(0));

        NHeap<Edge> h(2);

        os << "#Tempos x Swaps" << std::endl;

        for (unsigned long i = 1; i <= 17; i++) {

            h.clearTree();

            unsigned long E = pow(2, i) * log(i - 1);

            unsigned long n = pow(2, i) - 1;

            unsigned long n_swaps = 0;

            // deletemin
            unsigned long elapsed_sum = 0;

            for (int times_run = 0; times_run < TIMES_RUN_TESTS; times_run++) {
                
                h.clearTree();
                
                for (unsigned long keycount = 1;keycount <= n; keycount++) {

                    unsigned long key = std::rand();
                    unsigned long value = std::rand();

                    h.insert({key, value});
                }
                
                auto start = std::chrono::system_clock::now();
                for (unsigned long keycount = 1; keycount <= n; keycount++) {                
                    h.getNext(n_swaps);
                }
                auto end = std::chrono::system_clock::now();
                unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                elapsed_sum += elapsed;
            }

            os << elapsed_sum / (double) TIMES_RUN_TESTS << " " << n_swaps / (double) TIMES_RUN_TESTS << " " << E << " " << n << std::endl;

        }
    }
};