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

#endif