#include "../src/parser/parser.h"

int main()
{
    Zwei_drei_tree *root;
    root = NULL;
    scan_file_line(&root);

    printf("\n----------------------------------------------------------------------------------------\n");
    // Teste para (i): imprimir todas as palavras da unidade 1
    printf("Palavras da unidade 1:\n");
    show_port_and_eng_words(root, 1);
    printf("\n");
    printf("\n----------------------------------------------------------------------------------------\n");
    // Teste para (ii): imprimir as palavras em inglês para "dispositivo"
    printf("Traduções de 'dispositivo' em inglês:\n");
    show_eng_words(root, "dispositivo");
    printf("\n");
    printf("\n----------------------------------------------------------------------------------------\n");
    // Teste para (ii): imprimir as palavras em inglês para "memória"
    printf("Traduções de 'memória' em inglês:\n");
    show_eng_words(root, "memória");
    printf("\n");
    printf("\n----------------------------------------------------------------------------------------\n");

    deallocate_tree(root);

    return 0;
}