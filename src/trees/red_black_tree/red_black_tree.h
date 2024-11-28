#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #define RED 1
// #define BLACK 0

typedef enum {
    BLACK = 0,
    RED = 1
} Color;

// Estrutura para armazenar a informação do nó
typedef struct Info_rb {
    char eng_word[25];
    int unit;
} Info_rb;

// Estrutura do nó da árvore Rubro-Negra
typedef struct Red_Black_Tree {
    Info_rb info;
    Color color;
    struct Red_Black_Tree *left;
    struct Red_Black_Tree *right;
} Red_Black_Tree;

// Funções auxiliares
Color color(Red_Black_Tree *H);
void rotateLeft(Red_Black_Tree **root);
void rotateRight(Red_Black_Tree **root);
void swapColor(Red_Black_Tree *H);

// Funções de inserção
Red_Black_Tree* insert(Red_Black_Tree **H, Info_rb info);
Red_Black_Tree* register_rb(Red_Black_Tree *root, Info_rb info);

// Funções auxiliares para remoção
Red_Black_Tree* findMin(Red_Black_Tree *root);
void move2LeftRED(Red_Black_Tree **H);
void move2RightRED(Red_Black_Tree **H);
void removeMin(Red_Black_Tree **H);

// Funções de balanceamento e remoção
void balance(Red_Black_Tree **H);
bool removeNode(Red_Black_Tree **H, const char *word);
bool removeInTree(Red_Black_Tree **root, const char *word);

#endif
