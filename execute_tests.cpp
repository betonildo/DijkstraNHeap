#include <fstream>
#include "unit_tests/test_heap.h"
#include <string.h>

int main(int argc, char** argv) {

    // insert
    if (strcmp(argv[1], "h_insert") == 0) {
        std::ofstream insert_test_2_ari("unit_tests/tests_outputs/heap_insert_2_ari.dat");
        NHeapTest::testInsert(insert_test_2_ari);
    }

    if (strcmp(argv[1], "h_update") == 0) {
        std::ofstream update_test_2_ari("unit_tests/tests_outputs/heap_update_2_ari.dat");
        NHeapTest::testUpdate(update_test_2_ari);
    }

    return 0;
}