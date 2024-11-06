#ifndef TREE_23_H
#define TREE_23_H

#include "../../../includes/utils.h"
#include "../binary_tree/binary.h"

typedef struct Info {
    /////////////////////
    Binary_tree br_words;
    char eng_word[25];
    /////////////////////
}Info;

// struct da arvore 2-3
typedef struct Zwei_drei_tree{
    //////////////////////
    Info info1;
    Info info2;
    bool two_info;
    //////////////////////
    Zwei_drei_tree *left;
    Zwei_drei_tree *mid;
    Zwei_drei_tree *right;
    //////////////////////
}Zwei_drei_tree;


#endif