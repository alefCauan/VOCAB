#ifndef TREE_23_H
#define TREE_23_H

// #include "../../../includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../binary_tree/binary.h"

typedef struct Info {
    /////////////////////
    Binary_tree eng_words;
    char br_word[25];
    int unit;
    /////////////////////
}Info;

// struct da arvore 2-3
typedef struct Two_three_tree{
    //////////////////////
    Info info1;
    Info info2;
    bool two_info;
    //////////////////////
    struct Two_three_tree *left;
    struct Two_three_tree *mid;
    struct Two_three_tree *right;
    //////////////////////
}Two_three_tree;

Two_three_tree *alloc_tree(Info info, Two_three_tree *left, Two_three_tree *mid, Two_three_tree *right);

bool is_leaf(Two_three_tree *root);

// Busca o menor valor à direita (sucessor)
void lower_info_right(Two_three_tree *node, Two_three_tree **result_node, Two_three_tree **parent_node);

// Busca o maior valor à esquerda (predecessor)
void lower_info_left(Two_three_tree *node, Two_three_tree **result_node, Two_three_tree **parent_node);

void add_tree_23(Two_three_tree **root, Info info, Two_three_tree *b_node);

Two_three_tree *break_node(Two_three_tree **root, Info info, Info *rise, Two_three_tree *b_node);

Two_three_tree *insert_tree_23(Two_three_tree *Dad, Two_three_tree **root, Info info, Info *rise);

int remove_23(Two_three_tree **Dad, Two_three_tree **root, Info info);

void print_tree(Two_three_tree *root, int level); 


// Além disso, permita ao usuário:
// (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
// equivalentes em inglês;

// (ii)informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em
// português dada, independente da unidade;

// (iii)informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias
// das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
// árvore 2-3;

// (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto
// deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
// unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
// árvore 2-3.

#endif