#include "../src/parser/parser.h"

int main()
{
    Zwei_drei_tree *root;
    root = NULL;
    scan_file_line(&root);

    // printf("\n----------------------------------------------------------------------------------------\n");
    // // Teste para (i): imprimir todas as palavras da unidade 1
    // printf("Palavras da unidade 1:\n");
    // show_port_and_eng_words(root, 1);
    // print_tree(root, 0);
    // printf("\n");
    // printf("\n----------------------------------------------------------------------------------------\n");
   
    // Teste para (ii): imprimir as palavras em inglês para "tela"
    printf("Traduções de 'ventilador' em inglês:\n");
    char palavra[20] = {"ventilador"};
    // strcpy(palavra, "ventilador");
    show_eng_words(root, palavra);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------------\n");
    // Teste para (ii): imprimir as palavras em inglês para "memória"
    printf("Traduções de 'memória' em inglês:\n");
    show_eng_words(root, "memória");
    printf("\n");
    printf("\n----------------------------------------------------------------------------------------\n");

    // insert_vocabulary(&root, "casa", "house", 1);
    // insert_vocabulary(&root, "casa", "home", 1);
    // insert_vocabulary(&root, "casa", "residence", 1);

    show_all_eng_words(root->info1.eng_words);  // Deve exibir: house, home, residence

    deallocate_tree(root);

    return 0;
}