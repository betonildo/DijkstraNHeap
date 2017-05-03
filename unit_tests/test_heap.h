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

        for (U32 i = 0; i <= 23; i++) {

            U32 E = pow(2, i - 1) * (i - 1);
            U32 n = pow(2, i) - 1;
            U32 n_swaps = 0;

            h.clearTree();
            h.setCapacity(n);

            auto start = std::chrono::system_clock::now();
            for (U32 keycount = n; keycount >=1; keycount--) {
                n_swaps += h.insert({keycount, (U32)std::rand()});
            }
            auto end = std::chrono::system_clock::now();
            unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            double E_div = (double) (E ? E : 1);
            double S_i_by_SE_i = n_swaps / E_div;
            double T_i_by_O_of_TE_i = elapsed / E_div;

            os << "SWAPS " << n_swaps << " " << E << std::endl;
            os << "TIME " << elapsed << " " << E << std::endl;
        }
    }

    static inline void testUpdate(std::ostream& os) {

        NHeap<Edge> h(2);
        std::srand(time(0));
        int max_i = 15;
        os << "# n x S[i]/SE[i] or T[i]/TE[i]" << std::endl;

        for (U32 i = 1; i <= max_i; i++) {

            U32 E = pow(2, i) * i;

            U32 _2_p_i_m_1 = pow(2, i) - 1;
            U32 values1 = pow(2, i) + 1;

            U32 _2_p_i = pow(2, i);
            U32 values2 = pow(2, i) + 2;

            U32 updatevalue = pow(2, i) + 1 - i;
            U32 keystartmark = _2_p_i_m_1;
            U32 n_swaps = 0;

            h.clearTree();
            h.setCapacity(_2_p_i_m_1 + _2_p_i);

            // insert the first lotation
            for (U32 keycount = 1; keycount <= _2_p_i_m_1; keycount++) {
                h.insert({keycount, values1});
            }

            // insert the second lotation
            for (U32 keycount = 1; keycount <= _2_p_i; keycount++) {
                h.insert({keycount + keystartmark, values2});
            }

            auto start = std::chrono::system_clock::now();
            for (U32 keycount = _2_p_i; keycount >= 1 ; keycount--) {
                n_swaps += h.update({keycount + keystartmark, updatevalue});
                updatevalue -= 1;
            }
            auto end = std::chrono::system_clock::now();
            unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            double E_div = (double) (E ? E : 1);
            double S_i_by_SE_i = n_swaps / E_div;
            double T_i_by_O_of_TE_i = elapsed / E_div;

            os << "SWAPS " << n_swaps << " " << E << std::endl;
            os << "TIME " << elapsed << " " << E << std::endl;

            // WARNING: It is updating values to the wrong ones
        }
    }

    static inline void testDeletemin(std::ostream& os) {

        std::srand(time(0));

        NHeap<Edge> h(2);

        int max_i = 13;

        os << "# n x S[i]/SE[i] or T[i]/TE[i]" << std::endl;

        for (U32 i = 1; i <= max_i; i++) {

            h.clearTree();
            U32 E = pow(2, i - 1) * (i - 1);

            U32 n = pow(2, i) - 1;

            U32 n_deletes = pow(2, i - 1);

            U32 n_swaps = 0;            

            for (U32 keycount = 1;keycount <= n; keycount++) {

                U32 key = std::rand();
                U32 value = std::rand();

                h.insert({key, value});
            }           

            auto start = std::chrono::system_clock::now();
            for (U32 keycount = 1; keycount <= n_deletes; keycount++) {
                h.getNext(n_swaps);
            }
            auto end = std::chrono::system_clock::now();
            unsigned elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            
            double E_div = (double) (E ? E : 1);
            double S_i_by_SE_i = n_swaps / E_div;
            double T_i_by_O_of_TE_i = elapsed / E_div;

            os << "SWAPS " << n_swaps << " " << E << std::endl;
            os << "TIME " << elapsed << " " << E << std::endl;
        }
    }
};
