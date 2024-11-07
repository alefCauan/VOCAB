#ifndef TREE_23_H
#define TREE_23_H

#include "../../../includes/utils.h"
#include "../binary_tree/binary.h"

typedef struct Info {
    /////////////////////
    Binary_tree eng_words;
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

bool is_leaf(Zwei_drei_tree *root);

// Busca o menor valor à direita (sucessor)
void lower_info_right(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node);

// Busca o maior valor à esquerda (predecessor)
void lower_info_left(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node);

void add_tree_23(Zwei_drei_tree **root, Info info, Zwei_drei_tree *b_node);

Zwei_drei_tree *break_node(Zwei_drei_tree **root, Info info, Info *rise, Zwei_drei_tree *b_node);

Zwei_drei_tree *insert_tree_23(Zwei_drei_tree *Dad, Zwei_drei_tree **root, Info info, Info *rise);

int remove_23(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Info info);


#endif