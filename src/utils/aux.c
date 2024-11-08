#include "aux.h"

void line() { printf("---------------------------------------------------------------\n"); }

// função simples para relatar um "erro" ou ação invalida
void print_error(const char *error_message) 
{
    ///////
    fprintf(stderr, "ERROR: in %s\n", error_message);
}
// Checa a alocação de memoria de um ponteiro 
void check_allocation(void *pointer, const char *mensage) 
{
    if(!pointer) 
    {
        fprintf(stderr, "ERRO: ao alocar memória para %s: %d - %s\n", mensage, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
}

bool valid_answer(int min, int max, int answer) 
{
    bool result = (answer >= min && answer <= max);

    if(!result)
    {
        line();
        (answer > max) ? 
            RAISE_ERROR("data input, input greater than maximum parameter") : 
            RAISE_ERROR("data input, input less than minimum parameter");
        line();
    }
    
    return result;
}

// (float) valida uma resposta dentro de um certo limite
bool validf_answer(float min, float max, float answer)
{
    bool result = (answer >= min && answer <= max);

    if(!result)
    {
        line();
        (answer > max) ? 
            RAISE_ERROR("data input, input greater than maximum parameter") : 
            RAISE_ERROR("data input, input less than minimum parameter");
        line();
    }
    
    return result;
}
