set xlabel "time (ms)"
set ylabel "swaps"
plot    "unit_tests/tests_outputs/heap_insert_2_ari.dat" using 1:2 title "swap x time" w linesp, \
        (2 ** x) * x using 1:2 title "swap x time theorical" w linesp, \