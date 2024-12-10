#ifndef PARSER_RB_H
#define PARSER_RB_H

// #include "../../../includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../utils/aux.h"
#include "../trees/red_black_tree/red_black_tree.h"

#define UNIT_TOKEN '%'
#define ENG_TOKEN  ":"
#define BR_TOKEN   ","
#define END_TOKEN  ";"
#define PARSER_PATH "/home/alef/programas/VOCAB/src/parser/vocabulary.txt"

FILE *_open_file_rb(const char *file_name, const char *type);

void scan_file_line_rb(Red_black_tree **root);

void insert_vocabulary_rb(Red_black_tree **root, char *translation, char *english_word, int unit);

#endif