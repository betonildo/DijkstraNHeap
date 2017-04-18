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

        os << "#n x S[i]/SE[i] or T[i]/TE[i]" << std::endl;

        NHeap<Edge> h(2);

        std::srand(time(0));

        for (unsigned long i = 0; i <= 23; i++) {

            unsigned long E = pow(2, i - 1) * (i - 1);
            unsigned long n = pow(2, i) - 1;
            unsigned long n_swaps = 0;

            h.clearTree();
            h.setCapacity(n);

            auto start = std::chrono::system_clock::now();
            for (unsigned long keycount = n; keycount >=1; keycount--) {
                n_swaps += h.insert({keycount, (long unsigned int)std::rand()});
            }
            auto end = std::chrono::system_clock::now();
            unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            double E_div = (double) (E ? E : 1);
            double S_i_by_SE_i = n_swaps / E_div;
            double T_i_by_O_of_TE_i = elapsed / E_div;

            os << "SWAPS " << n << " " << S_i_by_SE_i << std::endl;
            os << "TIME " << n << " " << T_i_by_O_of_TE_i << std::endl;
        }
    }

    static inline void testUpdate(std::ostream& os) {

        NHeap<Edge> h(2);
        std::srand(time(0));

        os << "# n x S[i]/SE[i] or T[i]/TE[i]" << std::endl;

        for (unsigned long i = 1; i <= 20; i++) {

            unsigned long E = pow(2, i) * i;

            unsigned long _2_p_i_m_1 = pow(2, i) - 1;
            unsigned long values1 = pow(2, i) + 1;

            unsigned long _2_p_i = pow(2, i);
            unsigned long values2 = pow(2, i) + 2;

            unsigned long updatevalue = pow(2, i) + 1 - i;
            unsigned long keystartmark = _2_p_i_m_1;
            unsigned long n_swaps = 0;

            h.clearTree();
            h.setCapacity(_2_p_i_m_1 + _2_p_i);

            // insert the first lotation
            for (unsigned long keycount = 1; keycount <= _2_p_i_m_1; keycount++) {
                h.insert({keycount, values1});
            }

            // insert the second lotation
            for (unsigned long keycount = 1; keycount <= _2_p_i; keycount++) {
                h.insert({keycount + keystartmark, values2});
            }

            auto start = std::chrono::system_clock::now();
            for (unsigned long keycount = 1; keycount <= _2_p_i; keycount++) {
                n_swaps += h.update({keycount + keystartmark, updatevalue});
                updatevalue -= 1;
            }
            auto end = std::chrono::system_clock::now();
            unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            double E_div = (double) (E ? E : 1);
            double S_i_by_SE_i = n_swaps / E_div;
            double T_i_by_O_of_TE_i = elapsed / E_div;

            std::cout << E << " " << n_swaps << std::endl;

            os << "SWAPS " << _2_p_i << " " << S_i_by_SE_i << std::endl;
            os << "TIME " << _2_p_i << " " << T_i_by_O_of_TE_i << std::endl;

            // WARNING: It is updating values to the wrong ones
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
