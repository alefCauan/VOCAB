#include "parser.h"
#include "../trees/tree_23/tree_23.h"
#include "../utils/aux.h"

FILE *_open_file(const char *file_name, const char *type)
{
    FILE *file = fopen(file_name, type);
    ASSERT_ALLOC(file, "open file");

    return file;
}

void scan_file_line()
{
    FILE *parser = _open_file("/home/alef/programas/VOCAB/src/parser/vocabulary.txt", "r");
    char line[1024];
    
    while (fgets(line, sizeof(line), parser)) 
    {
        // Imprime a linha lida (ou processa conforme necessário)
        printf("%s", line);
        
        // Aqui você pode salvar, processar ou manipular a linha conforme necessário
        // Por exemplo, você pode analisar e armazenar as palavras da linha
    }
    
}

void printf_file_line()
{
    /////////////////////////////
    /////////////////////////////
    /////////////////////////////
}

