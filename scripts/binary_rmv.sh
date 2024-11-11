#!/bin/bash

SRC_MAIN="../tests/binary_remove.c"
SRC_BIN="../src/trees/binary_tree/binary.c"
OUT="del_bin_test"

# Compilar os arquivos .c em .o
gcc -g -c $SRC_BIN -o binary.o
gcc -g -c $SRC_MAIN -o main.o

# Verificação para garantir que os arquivos existem
if [ ! -f "$SRC_BIN" ]; then
    echo "Erro: Arquivo $SRC_BIN não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_MAIN" ]; then
    echo "Erro: Arquivo $SRC_MAIN não encontrado!"
    exit 1
fi

gcc -g  binary.o main.o -o ../bin/$OUT 

rm *.o

../bin/$OUT