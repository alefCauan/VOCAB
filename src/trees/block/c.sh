#!/bin/bash

SRC_MAIN="c.c"
SRC_AUX="../../utils/aux.c"
SCR_BLOCK="block.c"
OUT="teste_c"


gcc -g -o $OUT $SCR_BLOCK $SRC_AUX $SRC_MAIN 

# rm *.o
gdb -x run.txt ./$OUT
