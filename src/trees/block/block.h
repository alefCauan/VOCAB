#ifndef BLOCK23_H
#define BLOCK23_H
#define LAST_BLOCK 100

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct Info {
    /////////////////////
    char status;                  // 'O' (occupied) or 'F' (free)
    int start_block;              // Starting block number
    int end_block;                // Ending block number
    /////////////////////
}Info;


// Structure for a 2-3 Tree Node
typedef struct Tree23 {
    Info info1;
    Info info2;
    bool two_info;
    struct Tree23 *left_child;    // Pointer to the left child
    struct Tree23 *middle_child;  // Pointer to the middle child (if exists)
    struct Tree23 *right_child; 
} Tree23;

// Function declarations
Tree23 *createNode(char status, int start_block, int end_block);

Tree23 *alloc_tree(Info info, Tree23 *left, Tree23 *mid, Tree23 *right);

void add_tree_23(Tree23 **root, Info info, Tree23 *b_node);

Tree23 *break_node(Tree23 **root, Info info, Info *rise, Tree23 *b_node);

Tree23 *insert_tree_23(Tree23 *Dad, Tree23 **root, Info info, Info *rise);

void print_tree_in_order(Tree23 *root);

bool is_leaf(Tree23 *root);

void concatenate_adjacent_nodes(Tree23 *root);

#endif
