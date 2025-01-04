SRC_RB="trees/red_black_tree/red_black_tree.c"
SRC_BIN="trees/binary_tree/binary.c"
SRC_AUX="utils/aux.c"
SRC_PARSER="parser/parser_rb.c"

OUT="run_main_rb"

gcc -g -o ../bin/$OUT $SRC_RB $SRC_BIN $SRC_PARSER $SRC_AUX main_rb.c

../bin/$OUT