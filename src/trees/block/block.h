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

void concatenate_adjacent_nodes(Tree23 *root, Tree23 *original, Info info);

static int remove_internal_node1(Tree23 **source, Tree23 *root, Info *info, Tree23 *child1, Tree23 *child2, Tree23 **bigger_node);

static int remove_internal_node2(Tree23 **source, Tree23 *root, Info *info, Tree23 *child1, Tree23 *child2, Tree23 **bigger_node);

static int balance_23(Tree23 **root, Tree23 *child1, Tree23 **child2, Info info, Tree23 **bigger_node);

int rebalance_23(Tree23 **root, int start_block, Tree23 **bigger_node);

static int balance_23(Tree23 **root, Tree23 *child1, Tree23 **child2, Info info, Tree23 **bigger_node);

int remove_23(Tree23 **root, int start_block);

static int wave(Info saindo, Info *input, Tree23 *dad, Tree23 **source, Tree23 **root, Tree23 **bigger_node, 
                int (*remove_func)(Tree23 **, int, Tree23 *, Tree23 **, Tree23 **));

int remove_wave1(Tree23 **root, int start_block, Tree23 *dad, Tree23 **source, Tree23 **bigger_node);

int remove_wave2(Tree23 **root, int start_block, Tree23 *dad, Tree23 **source, Tree23 **bigger_node);

static Tree23 *search_23_small_dad_info2(Tree23 *root, int start_block);

Tree23 *search_23_small_dad(Tree23 *root, int start_block);

Tree23 *search_23_bigger_dad(Tree23 *root, int start_block);

Tree23 *search_23_dad(Tree23 *root, int start_block);

Tree23 *search_23_bigger_child(Tree23 *root, Tree23 **dad, Info *bigger_value);
Tree23 *search_23_lower_child(Tree23 *root, Tree23 **dad);
static Tree23 *join_node(Tree23 *child1, Info info, Tree23 *bigger_node, Tree23 **root);
static int is_removable(Tree23 *root);
static int height(Tree23 *node);
bool is_info2(Tree23 *node, int start_block, int end_block);
bool is_info1(Tree23 *node, int start_block);

#endif
