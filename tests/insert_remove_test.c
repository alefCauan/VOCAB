#include "../src/trees/tree_23/tree_23.h"

int main() 
{
    Zwei_drei_tree *root = NULL;
    Info info1, info2, info3, info4, info5;
    Info rise;  // Variável auxiliar para crescimento da árvore
 


    // Inicializa dados para teste
    strcpy(info1.br_word, "casa");
    strcpy(info2.br_word, "carro");
    strcpy(info3.br_word, "bola");
    strcpy(info4.br_word, "dado");
    strcpy(info5.br_word, "ave");

    // printf("%s - %s = %d\n", info1.br_word, info2.br_word, strcmp(info1.br_word, info2.br_word));
    // const char *search_word = "casa";


    // Insere nós na árvore
    printf("Inserindo palavras na árvore...\n");
    insert_tree_23(NULL, &root, info1, &rise);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info2, &rise);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info3, &rise);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info4, &rise);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info5, &rise);

    // Zwei_drei_tree *result = search_23_tree(root, search_word);
    // if (result != NULL) {
    //     printf("Palavra encontrada: %s\n", search_word);
    // } else {
    //     printf("Palavra '%s' não encontrada na árvore.\n", search_word);
    // }

    // Imprime estrutura da árvore após inserções
    printf("\nÁrvore após inserções:\n");
    print_tree(root, 0);

    // Remove alguns elementos e imprime o estado da árvore
    printf("\nRemovendo 'casa'...\n");
    remove_23(NULL, &root, info1);
    print_tree(root, 0);

    printf("\nRemovendo 'dado'...\n");
    remove_23(NULL, &root, info4);
    print_tree(root, 0);

    printf("\nRemovendo 'carro'...\n");
    remove_23(NULL, &root, info2);
    print_tree(root, 0);

    // Libera memória
    // Função para liberar a árvore inteira (não implementada aqui)

    return 0;
}