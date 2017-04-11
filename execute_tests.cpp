#include <fstream>
#include "unit_tests/test_heap.h"


int main(int argc, char** argv) {

    std::ofstream insert_test_2_ari("unit_tests/tests_outputs/heap_insert_1000_upto_1000000_2_ari.dat");
    std::ofstream insert_test_3_ari("unit_tests/tests_outputs/heap_insert_1000_upto_1000000_3_ari.dat");
    std::ofstream insert_test_4_ari("unit_tests/tests_outputs/heap_insert_1000_upto_1000000_4_ari.dat");
    std::ofstream insert_test_5_ari("unit_tests/tests_outputs/heap_insert_1000_upto_1000000_5_ari.dat");

    NHeapTest::testFromNtoNinstancesAtStepMtimes_O_aridity(insert_test_2_ari, 100000, 1000000, 100000, 10, 2);
    NHeapTest::testFromNtoNinstancesAtStepMtimes_O_aridity(insert_test_3_ari, 100000, 1000000, 100000, 10, 3);
    NHeapTest::testFromNtoNinstancesAtStepMtimes_O_aridity(insert_test_4_ari, 100000, 1000000, 100000, 10, 4);
    NHeapTest::testFromNtoNinstancesAtStepMtimes_O_aridity(insert_test_5_ari, 100000, 1000000, 100000, 10, 5);


    return 0;
}