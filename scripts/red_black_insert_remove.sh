#!/bin/bash

SRC_MAIN="../tests/red_black_insert_remove.c"
SRC_RED_BLACK="../src/trees/red_black_tree/red_black_tree.c"
SRC_UTILS="../src/utils/aux.c"
OUT="parser_test"

# Compilar os arquivos .c em .o
gcc -g -c $SRC_RED_BLACK -o redblack.o
gcc -g -c $SRC_UTILS -o utils.o
gcc -g -c $SRC_PARSER -o parser.o
gcc -g -c $SRC_MAIN -o main.o

# Verificação para garantir que os arquivos existem

if [ ! -f "$SRC_UTILS" ]; then
    echo "Erro: Arquivo $SRC_UTILS não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_MAIN" ]; then
    echo "Erro: Arquivo $SRC_MAIN não encontrado!"
    exit 1
fi

gcc -g utils.o redblack.o main.o -o ../bin/$OUT 

rm *.o

../bin/$OUT