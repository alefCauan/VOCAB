#!/bin/bash

SRC_MAIN="../tests/parser_test.c"
SRC_23="../src/trees/tree_23/tree_23.c"
SRC_BIN="../src/trees/binary_tree/binary.c"
SRC_PARSER="../src/parser/parser.c"
SRC_UTILS="../src/utils/aux.c"
OUT="parser_test"

# Compilar os arquivos .c em .o
gcc -g -c $SRC_BIN -o binary.o
gcc -g -c $SRC_23 -I../src/trees/binary_tree -o tree_23.o
gcc -g -c $SRC_UTILS -o utils.o
gcc -g -c $SRC_PARSER -o parser.o
gcc -g -c $SRC_MAIN -o main.o

# Verificação para garantir que os arquivos existem
if [ ! -f "$SRC_BIN" ]; then
    echo "Erro: Arquivo $SRC_BIN não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_23" ]; then
    echo "Erro: Arquivo $SRC_23 não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_UTILS" ]; then
    echo "Erro: Arquivo $SRC_UTILS não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_PARSER" ]; then
    echo "Erro: Arquivo $SRC_PARSER não encontrado!"
    exit 1
fi

if [ ! -f "$SRC_MAIN" ]; then
    echo "Erro: Arquivo $SRC_MAIN não encontrado!"
    exit 1
fi

gcc -g  binary.o tree_23.o utils.o parser.o main.o -o ../bin/$OUT 

rm *.o

../bin/$OUT