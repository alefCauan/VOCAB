#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../binary_tree/binary.h"

// Estrutura da árvore Rubro-Negra
typedef enum {
    BLACK = 0,
    RED = 1
} Color;


typedef struct Info_rb {
    Binary_tree *eng_words;
    char br_word[256]; // Palavra em português
    int unit;          // Unidade associada
} Info_rb;

typedef struct Red_black_tree {
    Info_rb info;                  // Informações da palavra
    Color color;                   // Cor do nó (Vermelho ou Preto)
    struct Red_black_tree *left;   // Ponteiro para o filho esquerdo
    struct Red_black_tree *right;  // Ponteiro para o filho direito
} Red_black_tree;

// ============================
// Funções de desalocação
// ============================

/**
 * Desaloca toda a árvore Rubro-Negra.
 * @param root: Ponteiro para a raiz da árvore.
 */
void deallocate_red_black_tree(Red_black_tree *root);

// ============================
// Funções auxiliares
// ============================

/**
 * Retorna a cor de um nó. Nulo é considerado Preto.
 * @param H: Ponteiro para o nó.
 * @return Color (RED ou BLACK).
 */
Color color(Red_black_tree *H);

/**
 * Verifica se um nó é vermelho.
 * @param node: Ponteiro para o nó.
 * @return true se for vermelho, false caso contrário.
 */
bool is_red(Red_black_tree *node);

/**
 * Rotação à esquerda para manter o balanceamento.
 * @param root: Ponteiro para o nó desbalanceado.
 */
void rotate_left(Red_black_tree **root);

/**
 * Rotação à direita para manter o balanceamento.
 * @param root: Ponteiro para o nó desbalanceado.
 */
void rotate_right(Red_black_tree **root);

/**
 * Troca as cores de um nó e seus filhos.
 * @param H: Ponteiro para o nó cuja cor será trocada.
 */
void swap_color(Red_black_tree **H);

// ============================
// Funções de inserção
// ============================

/**
 * Insere um novo nó na árvore Rubro-Negra.
 * @param node: Ponteiro para a raiz da árvore.
 * @param info: Informações a serem inseridas.
 * @return Ponteiro para a raiz balanceada.
 */
Red_black_tree *insert_rb(Red_black_tree *node, Info_rb info);

/**
 * Insere e ajusta a raiz para garantir que ela seja preta.
 * @param root: Ponteiro para a raiz da árvore.
 * @param info: Informações a serem inseridas.
 * @return Ponteiro para a nova raiz ajustada.
 */
Red_black_tree* register_rb(Red_black_tree *root, Info_rb info);

// ============================
// Funções auxiliares para remoção
// ============================

Red_black_tree *search_rb(Red_black_tree *root, const char *br_word);

/**
 * Encontra o menor valor na subárvore.
 * @param root: Ponteiro para a raiz da subárvore.
 * @return Ponteiro para o nó com o menor valor.
 */
Red_black_tree* find_min(Red_black_tree *root);

/**
 * Move a cor vermelha para a subárvore esquerda.
 * @param H: Ponteiro para o nó atual.
 */
void move_left(Red_black_tree **H);

/**
 * Move a cor vermelha para a subárvore direita.
 * @param H: Ponteiro para o nó atual.
 */
void move_right(Red_black_tree **H);

/**
 * Remove o menor valor de uma subárvore.
 * @param H: Ponteiro para a raiz da subárvore.
 */
void remove_min(Red_black_tree **H);

// ============================
// Funções de balanceamento e remoção
// ============================

/**
 * Balanceia a árvore após uma inserção ou remoção.
 * @param node: Ponteiro para o nó atual.
 * @return Ponteiro para o nó balanceado.
 */
Red_black_tree *balance(Red_black_tree *node);

/**
 * Remove um nó específico da árvore Rubro-Negra.
 * @param H: Ponteiro para a raiz da árvore.
 * @param word: Palavra a ser removida.
 * @return true se a remoção for bem-sucedida, false caso contrário.
 */
bool remove_node(Red_black_tree **H, const char *word);

/**
 * Remove uma palavra da árvore Rubro-Negra e ajusta a raiz se necessário.
 * @param root: Ponteiro para a raiz da árvore.
 * @param word: Palavra a ser removida.
 * @return true se a remoção for bem-sucedida, false caso contrário.
 */
bool remove_in_tree(Red_black_tree **root, const char *word);

#endif // RED_BLACK_TREE_H
