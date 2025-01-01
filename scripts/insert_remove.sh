#!/bin/bash

SRC_MAIN="../tests/insert_remove_test.c"
SRC_23="../src/trees/binary_tree/binary.c"
SRC_BIN="../src/trees/tree_23/tree_23.c"
SRC_AUX="../src/utils/aux.c"
OUT="in_del_test"

# Compilar os arquivos .c em .o
gcc -g -c $SRC_BIN -o binary.o
gcc -g -c $SRC_23 -I../src/trees/binary_tree -o tree_23.o
gcc -g -c $SRC_MAIN -o main.o
gcc -g -c $SRC_AUX -o aux.o 


# Verificação para garantir que os arquivos existem
if [ ! -f "$SRC_BIN" ]; then
    echo "Erro: Arquivo $SRC_BIN não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_23" ]; then
    echo "Erro: Arquivo $SRC_23 não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_MAIN" ]; then
    echo "Erro: Arquivo $SRC_MAIN não encontrado!"
    exit 1
fi

gcc -g  binary.o tree_23.o aux.o main.o -o ../bin/$OUT 

rm *.o

valgrind --leak-check=full ../bin/$OUT
