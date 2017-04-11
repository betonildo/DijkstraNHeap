set xlabel "inserts"
set ylabel "swaps"
plot "unit_tests/tests_outputs/heap_insert_2_ari_eswaps_nitens.dat" title "swap x itens theorical" w linesp, \
    "unit_tests/tests_outputs/heap_insert_2_ari_swaps_nitens.dat" title "swap x itens" w linesp