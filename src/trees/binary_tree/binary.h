#ifndef BINARY_H
#define BINARY_H

#include "../../../includes/utils.h"

// struct da arvore BINARIA
typedef struct Info_bin{
    char word[25];
}Info_bin;

typedef struct Binary_tree{
    Info_bin root;
    struct Binary_tree *left;
    struct Binary_tree *right;
}Binary_tree;



#endif