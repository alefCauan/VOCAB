#ifndef BINARY_H
#define BINARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Unit
{
    int unit;
    struct Unit *next;
} Unit;

// struct da arvore BINARIA
typedef struct Info_bin{
    ///////////////////
    char eng_word[25];
    Unit *units;
    //////////////////
}Info_bin;

typedef struct Binary_tree{
    ////////////////////////////
    Info_bin info;
    ////////////////////////////
    struct Binary_tree *left;
    struct Binary_tree *right;
    ////////////////////////////
}Binary_tree;


Binary_tree *allocate_binary(Info_bin info);

void deallocate_binary_tree(Binary_tree *root);

Binary_tree *search_bin(Binary_tree *root, Info_bin info);

bool insert_bin(Binary_tree **root, Binary_tree *new);

void register_bin(Binary_tree **root, Info_bin info);

void remove_eng_word_no_children(Binary_tree **root, Binary_tree *current, Binary_tree *parent);

void remove_eng_word_one_child(Binary_tree **root, Binary_tree *current, Binary_tree *parent);

void remove_eng_word_two_children(Binary_tree **root, Binary_tree *current);

bool remove_eng_word_bin(Binary_tree **root, Info_bin info_bin);

bool remove_eng_word_bin_unit(Binary_tree **root, Info_bin info_bin);

void print_binary_tree(Binary_tree *root, int level);

void show_all_eng_words(Binary_tree *root);

bool is_binary_tree_empty(Binary_tree *root);

Unit *allocate_list();

Unit *create_list(int unit);

void deallocate_list(Unit **lista);

void insert_list(Unit **lista, int unit);

void show_list(Unit *lista);

Unit *search_list(Unit *lista, int unit);

int remove_list(Unit **lista, int unit);

#endif