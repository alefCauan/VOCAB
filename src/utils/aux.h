#ifndef AUX_H
#define AUX_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#define RAISE_ERROR(message) (print_error(message))
#define ASSERT_ALLOC(pointer, message) (check_allocation(pointer, message))


void line();

// função simples para relatar um "erro" ou ação invalida
void print_error(const char *error_message);

// Checa a alocação de memoria de um ponteiro 
void check_allocation(void *pointer, const char *mensage);

bool valid_answer(int min, int max, int answer);

// (float) valida uma resposta dentro de um certo limite
bool validf_answer(float min, float max, float answer);

void trim_string(char *str);

#endif // AUX_H