#ifndef BINARY_H
#define BINARY_H

#include "../../../includes/utils.h"

// struct da arvore BINARIA
typedef struct Info_bin
{
    int unit;
    char word[25];
}Info_bin;

typedef struct Binary_tree
{
    Info_bin root;
    Binary_tree *left;
    Binary_tree *right;
}Binary_tree;



#endif