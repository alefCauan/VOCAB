#include <stdio.h>
#include <stdbool.h>
#include "block.h" // Assuma que contém as definições de Tree23 e Info

bool allocate_blocks(Tree23 *root, int required_blocks) {
    bool allocation_result = false; // Variável auxiliar para armazenar o resultado da alocação

    if (root == NULL) {
        allocation_result = false; // Não há nós na árvore
    } else {
        // Verifica o primeiro valor do nó
        if (root->info1.status == 'L' &&
            (root->info1.end_block - root->info1.start_block + 1) >= required_blocks) {

            // Calcula os blocos restantes após a alocação
            int remaining_blocks = (root->info1.end_block - root->info1.start_block + 1) - required_blocks;

            printf("Nó encontrado:\n");
            printf("Status: Livre -> Ocupado\n");
            printf("Blocos alocados: %d - %d\n", root->info1.start_block, root->info1.start_block + required_blocks - 1);

            // Atualiza o nó atual para "Ocupado" para os blocos alocados
            int old_end_block = root->info1.end_block;
            root->info1.status = 'O';
            root->info1.end_block = root->info1.start_block + required_blocks - 1;

            // Atualiza os blocos restantes em um novo nó livre (se houver)
            if (remaining_blocks > 0) {
                Info remaining_info = {'L', root->info1.end_block + 1, old_end_block};
                insert_tree_23(NULL, &root, remaining_info, NULL);
            }

            // Concatenar nós adjacentes
            concatenate_adjacent_nodes(root);
            allocation_result = true;
        }

        // Verifica o segundo valor do nó (se existir)
        if (!allocation_result && root->two_info &&
            root->info2.status == 'L' &&
            (root->info2.end_block - root->info2.start_block + 1) >= required_blocks) {

            // Calcula os blocos restantes após a alocação
            int remaining_blocks = (root->info2.end_block - root->info2.start_block + 1) - required_blocks;

            printf("Nó encontrado:\n");
            printf("Status: Livre -> Ocupado\n");
            printf("Blocos alocados: %d - %d\n", root->info2.start_block, root->info2.start_block + required_blocks - 1);

            // Atualiza o nó atual para "Ocupado" para os blocos alocados
            int old_end_block = root->info2.end_block;
            root->info2.status = 'O';
            root->info2.end_block = root->info2.start_block + required_blocks - 1;

            // Atualiza os blocos restantes em um novo nó livre (se houver)
            if (remaining_blocks > 0) {
                Info remaining_info = {'L', root->info2.end_block + 1, old_end_block};
                insert_tree_23(NULL, &root, remaining_info, NULL);
            }

            // Concatenar nós adjacentes
            concatenate_adjacent_nodes(root);
            allocation_result = true;
        }

        // Procura nos filhos se a alocação ainda não foi realizada
        if (!allocation_result) {
            allocation_result = allocate_blocks(root->left_child, required_blocks) ||
                                allocate_blocks(root->middle_child, required_blocks) ||
                                (root->two_info && allocate_blocks(root->right_child, required_blocks));
        }
    }

    return allocation_result; // Retorna o resultado da alocação
}


int main() {
    Tree23 *root = NULL;

    // Insere alguns nós para teste
    Info rise;
    insert_tree_23(NULL, &root, (Info){'L', 0, 9}, &rise);  // Blocos 0 a 9 livres
    insert_tree_23(NULL, &root, (Info){'O', 10, 19}, &rise); // Blocos 20 a 29 ocupados
    insert_tree_23(NULL, &root, (Info){'L', 20, 29}, &rise); // Blocos 10 a 19 livres

    // Solicita ao usuário a quantidade de blocos necessários
    int required_blocks;
    printf("Informe a quantidade de blocos que deseja alocar: ");
    scanf("%d", &required_blocks);

    // Tenta alocar os blocos
    if (!allocate_blocks(root, required_blocks)) {
        printf("Não há blocos livres suficientes para alocar %d blocos.\n", required_blocks);
    }

    // Imprime a árvore após a alocação
    printf("\nÁrvore após a alocação:\n");
    print_tree_in_order(root);

    return 0;
}
