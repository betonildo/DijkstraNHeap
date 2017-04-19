#include <fstream>
#include "unit_tests/test_heap.h"
#include "unit_tests/test_graph.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string arg;
    arg.assign(argv[1]);

    if (arg == "h_insert") {
        std::ofstream insert_test_2_ari("unit_tests/tests_outputs/heap_insert_2_ari.dat");
        NHeapTest::testInsert(insert_test_2_ari);
    }

    if (arg == "h_update") {
        std::ofstream update_test_2_ari("unit_tests/tests_outputs/heap_update_2_ari.dat");
        NHeapTest::testUpdate(update_test_2_ari);
    }

    if (arg == "h_deletemin") {
        std::ofstream deletemin_test_2_ari("unit_tests/tests_outputs/heap_deletemin_2_ari.dat");
        NHeapTest::testDeletemin(deletemin_test_2_ari);
    }

    if (arg == "dijkstra") {
        std::ofstream dijkstra_test_m("unit_tests/tests_outputs/dijkstra_test_m.dat");
        DijkstraTest::testDijkstraM(dijkstra_test_m);

        std::ofstream dijkstra_test_n("unit_tests/tests_outputs/dijkstra_test_n.dat");
        DijkstraTest::testDijkstraN(dijkstra_test_n);
    }

    return 0;
}