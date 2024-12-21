#!/bin/bash

SRC_MAIN="../tests/parser_rb.c"
SRC_PARSER="../src/parser/parser_rb.c"
SRC_BIN="../src/trees/binary_tree/binary.c"
SRC_RED_BLACK="../src/trees/red_black_tree/red_black_tree.c"
SRC_UTILS="../src/utils/aux.c"
OUT="parser_test_rb"

# Compilar os arquivos .c em .o
gcc -g -c $SRC_BIN -o bin.o
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

if [ ! -f "$SRC_BIN" ]; then
    echo "Erro: Arquivo $SRC_BIN não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_RED_BLACK" ]; then
    echo "Erro: Arquivo $SRC_RED_BLACK não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_PARSER" ]; then
    echo "Erro: Arquivo $SRC_PARSER não encontrado!"
    exit 1
fi

gcc -g bin.o utils.o redblack.o parser.o main.o -o ../bin/$OUT 

rm *.o

../bin/$OUT