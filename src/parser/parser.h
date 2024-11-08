#ifndef PARSER_H
#define PARSER_H

// #include "../../../includes/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../utils/aux.h"

#define UNIT_TOKEN '%'
#define ENG_TOKEN  ":"
#define BR_TOKEN   ","
#define END_TOKEN  ";"
#define PARSER_PATH "/home/alef/programas/VOCAB/src/parser/vocabulary.txt"

FILE *_open_file(const char *file_name, const char *type);

void scan_file_line();

void printf_file_line();


#endif