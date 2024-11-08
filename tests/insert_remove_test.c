#include "../src/trees/tree_23/tree_23.h"

int main() 
{
    Zwei_drei_tree *root = NULL;
    Info info1, info2, info3, info4, info5;
    Info rise1;  // Variável auxiliar para crescimento da árvore
    Info rise2;  // Variável auxiliar para crescimento da árvore
    Info rise3;  // Variável auxiliar para crescimento da árvore
    Info rise4;  // Variável auxiliar para crescimento da árvore
    Info rise5;  // Variável auxiliar para crescimento da árvore


    // Inicializa dados para teste
    strcpy(info1.br_word, "casa");
    strcpy(info2.br_word, "carro");
    strcpy(info3.br_word, "bola");
    strcpy(info4.br_word, "dado");
    strcpy(info5.br_word, "ave");

    printf("%s - %s = %d\n", info1.br_word, info2.br_word, strcmp(info1.br_word, info2.br_word));


    // Insere nós na árvore
    printf("Inserindo palavras na árvore...\n");
    insert_tree_23(NULL, &root, info1, &rise1);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info2, &rise2);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info3, &rise3);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info4, &rise4);
    print_tree(root, 0);
    insert_tree_23(NULL, &root, info5, &rise5);

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