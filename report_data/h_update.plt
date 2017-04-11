plot    "unit_tests/tests_outputs/heap_update_1000_upto_1000000_2_ari.dat" using 1:2 title "2-ari" w linesp, \
        "unit_tests/tests_outputs/heap_update_1000_upto_1000000_3_ari.dat" using 1:2 title "3-ari" w linesp, \
        "unit_tests/tests_outputs/heap_update_1000_upto_1000000_4_ari.dat" using 1:2 title "4-ari" w linesp, \
        "unit_tests/tests_outputs/heap_update_1000_upto_1000000_5_ari.dat" using 1:2 title "5-ari" w linesp, \
        log(10, x) using 1:2 title "theorical-complexity" w linesp