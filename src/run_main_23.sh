#!/bin/bash

SRC_23="trees/tree_23/tree_23.c"
SRC_BIN="trees/binary_tree/binary.c"
SRC_AUX="utils/aux.c"
SRC_PARSER="parser/parser.c"

OUT="run_main_23"

gcc -g -o ../bin/$OUT $SRC_23 $SRC_BIN $SRC_PARSER $SRC_AUX main_23.c

valgrind --leak-check=full ../bin/$OUT