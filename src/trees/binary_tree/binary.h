#ifndef BINARY_H
#define BINARY_H

#include "../../../includes/utils.h"

// struct da arvore BINARIA
typedef struct Info_bin{
    char eng_word[25];
}Info_bin;

typedef struct Binary_tree{
    Info_bin info;
    struct Binary_tree *left;
    struct Binary_tree *right;
}Binary_tree;

Binary_tree *allocate_binary();

Binary_tree *search_bin(Binary_tree *root, Info_bin info);

bool insert_bin(Binary_tree **root, Binary_tree *new);

void register_bin(Binary_tree **root, Info_bin info);


#endif