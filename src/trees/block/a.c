
#include "block.h" // Assuma que contém as definições de `Tree23` e `Info`

// Função para cadastrar nós na árvore
void add_nodes(Tree23 **root) {
    int start_block, end_block;
    char status;
    Info rise;

    printf("Cadastro de nós da árvore 2-3:\n");

    // Primeiro nó
    printf("Informe se o primeiro nó é livre (L) ou ocupado (O): ");
    scanf(" %c", &status); // Lê o status (L ou O)

    printf("Informe o número do bloco inicial do primeiro nó: ");
    scanf("%d", &start_block); // Lê o número do bloco inicial

    printf("Informe o número do bloco final do primeiro nó: ");
    scanf("%d", &end_block); // Lê o número do bloco final

    // Insere o primeiro nó na árvore
    insert_tree_23(NULL, root, (Info){status, start_block, end_block}, &rise);

    // Loop para cadastrar os demais nós
    while (end_block != LAST_BLOCK) {
        printf("Informe o número do bloco final do próximo nó: ");
        scanf("%d", &end_block);

        // Atualiza o bloco inicial com base no último bloco final
        start_block = (*root)->info1.end_block + 1;

        // Pergunta o status do próximo bloco
        printf("O próximo nó é livre (L) ou ocupado (O): ");
        scanf(" %c", &status);

        // Insere o novo nó na árvore
        insert_tree_23(NULL, root, (Info){status, start_block, end_block}, &rise);
        }
    }


int main() {
    Tree23 *root = NULL;

    // Chama a função de cadastro
    add_nodes(&root);

    // Imprime a árvore em ordem
    printf("Árvore 2-3 em ordem:\n");
    print_tree_in_order(root);

    return 0;
}
