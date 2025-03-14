#ifndef TREE_23_H
#define TREE_23_H

// #include "../../../includes/utils.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../binary_tree/binary.h"

typedef struct Info {
    /////////////////////
    Binary_tree *eng_words;
    char br_word[25];
    int unit;
    /////////////////////
}Info;

// struct da arvore 2-3
typedef struct Zwei_drei_tree{
    //////////////////////
    Info info1;
    Info info2;
    bool two_info;
    //////////////////////
    struct Zwei_drei_tree *left;
    struct Zwei_drei_tree *mid;
    struct Zwei_drei_tree *right;
    //////////////////////
}Zwei_drei_tree;

Zwei_drei_tree *alloc_tree(Info info, Zwei_drei_tree *left, Zwei_drei_tree *mid, Zwei_drei_tree *right);

void deallocate_tree(Zwei_drei_tree *no);

void deallocate_tree2(Zwei_drei_tree **no);

bool is_leaf(Zwei_drei_tree *root);

// // Busca o menor valor à direita (sucessor)
// void lower_info_right(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node);

// // Busca o maior valor à esquerda (predecessor)
// void lower_info_left(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node);

void add_tree_23(Zwei_drei_tree **root, Info info, Zwei_drei_tree *b_node);

Zwei_drei_tree *break_node(Zwei_drei_tree **root, Info info, Info *rise, Zwei_drei_tree *b_node);

Zwei_drei_tree *insert_tree_23(Zwei_drei_tree *Dad, Zwei_drei_tree **root, Info info, Info *rise);

/////////////////////////////////////////////////////////////////////////////////////////

int is_info1(Zwei_drei_tree no, char *info);

int is_info2(Zwei_drei_tree no, char *info);

static int height(Zwei_drei_tree *no);

static int is_removable(Zwei_drei_tree *raiz);

static Zwei_drei_tree *join_node(Zwei_drei_tree *filho1, Info info, Zwei_drei_tree *maior, Zwei_drei_tree **raiz);

Info bigger_info_node(Zwei_drei_tree *raiz);

Zwei_drei_tree *search_23(Zwei_drei_tree *raiz, char *info);

Zwei_drei_tree *search_23_lower_child(Zwei_drei_tree *raiz, Zwei_drei_tree **pai);

Zwei_drei_tree *search_23_bigger_child(Zwei_drei_tree *raiz, Zwei_drei_tree **pai, Info *maior_valor);

Zwei_drei_tree *search_23_dad(Zwei_drei_tree *raiz, char *info);

Zwei_drei_tree *search_23_bigger_dad(Zwei_drei_tree *raiz, char *info);

Zwei_drei_tree *search_23_small_dad(Zwei_drei_tree *raiz, char *info);

static Zwei_drei_tree *search_23_small_dad_info2(Zwei_drei_tree *raiz, char *info);

static int wave(Info saindo, Info *entrada, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **raiz, Zwei_drei_tree **maior, int (*funcao_remover)(Zwei_drei_tree **, char *, Zwei_drei_tree *, Zwei_drei_tree **, Zwei_drei_tree **));

static int remove_internal_node1(Zwei_drei_tree **origem, Zwei_drei_tree* raiz, Info *info, Zwei_drei_tree *filho1, Zwei_drei_tree *filho2, Zwei_drei_tree **maior);

static int remove_internal_node2(Zwei_drei_tree **origem, Zwei_drei_tree* raiz, Info *info, Zwei_drei_tree *filho1, Zwei_drei_tree *filho2, Zwei_drei_tree **maior);

int remove_wave1(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **maior);

int remove_wave2(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **maior);

int remove_23(Zwei_drei_tree **raiz, char *info);

static int balance_23(Zwei_drei_tree **raiz, Zwei_drei_tree *filho1, Zwei_drei_tree **filho2, Info info, Zwei_drei_tree **maior);

int rebalance_23(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree **maior);


Zwei_drei_tree *search_23_tree(Zwei_drei_tree *root, const char *br_word);

void print_tree(Zwei_drei_tree *root, int level); 

void print_bin_tree(Zwei_drei_tree *root, int level); 


// Remove espaços extras e caracteres invisíveis das extremidades
void trim_string(char *str);
/*
(i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
equivalentes em inglês; [x]
*/
void show_port_and_eng_words(Zwei_drei_tree *root, int unit);

/*
(ii)informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em
português dada, independente da unidade; [x]
*/
void show_eng_words(Zwei_drei_tree *root, const char *br_word);

bool is_binary_tree_empty(Binary_tree *root);
/*
(iii)informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
árvore 2-3; [x]
*/
void remove_eng_word(Zwei_drei_tree **root, Info_bin info_bin);

void remove_all_eng_words(Zwei_drei_tree **root, Binary_tree *eng_words);
/*
(iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
árvore 2-3. [x]
*/ 
void remove_port_word(Zwei_drei_tree **root, Info info);


#endif