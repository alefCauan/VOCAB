#include <stdio.h>
#include <stdbool.h>
#include "block.h" // Assuma que contém as definições de Tree23 e Info


bool free_blocks(Tree23 *root, int start_block, int end_block) {
    bool free_result = false;

    if (root == NULL) {
        return free_result; // Árvore vazia
    }

    // Verifica se o primeiro intervalo (info1) contém os blocos a serem liberados
    if (root->info1.status == 'O' &&
        root->info1.start_block <= start_block &&
        root->info1.end_block >= end_block) {

        printf("Nó encontrado:\n");
        printf("Blocos liberados: %d - %d\n", start_block, end_block);

        // Atualiza o status para Livre
        if (root->info1.start_block == start_block && root->info1.end_block == end_block) {
            // Caso os blocos correspondam exatamente ao intervalo do nó
            root->info1.status = 'L';
        } else if (root->info1.start_block == start_block) {
            // Se os blocos a liberar estão no início
            Info remaining_info = {'O', end_block + 1, root->info1.end_block};
            root->info1.end_block = end_block;
            root->info1.status = 'L';
            insert_tree_23(NULL, &root, remaining_info, NULL);
        } else if (root->info1.end_block == end_block) {
            // Se os blocos a liberar estão no final
            Info remaining_info = {'O', root->info1.start_block, start_block - 1};
            root->info1.start_block = start_block;
            root->info1.status = 'L';
            insert_tree_23(NULL, &root, remaining_info, NULL);
        } else {
            // Se os blocos estão no meio do intervalo
            Info left_info =  {'O', root->info1.start_block, start_block - 1};
            Info right_info = {'O', end_block + 1, root->info1.end_block};
            root->info1.start_block = start_block;
            root->info1.end_block = end_block;
            root->info1.status = 'L';
            Info rise;
            insert_tree_23(NULL, &root, left_info,  &rise);
            insert_tree_23(NULL, &root, right_info, &rise);
        }

        // Concatenar nós adjacentes
        concatenate_adjacent_nodes(root);
        free_result = true;
    }

    // Verifica se o segundo intervalo (info2) contém os blocos a serem liberados
    if (!free_result && root->two_info &&
        root->info2.status == 'O' &&
        root->info2.start_block <= start_block &&
        root->info2.end_block >= end_block) {

        printf("Nó encontrado:\n");
        printf("Blocos liberados: %d - %d\n", start_block, end_block);

        // Atualiza o status para Livre
        if (root->info2.start_block == start_block && root->info2.end_block == end_block) {
            // Caso os blocos correspondam exatamente ao intervalo do nó
            root->info2.status = 'L';
        } else if (root->info2.start_block == start_block) {
            // Se os blocos a liberar estão no início
            Info remaining_info = {'O', end_block + 1, root->info2.end_block};
            root->info2.end_block = end_block;
            root->info2.status = 'L';
            insert_tree_23(NULL, &root, remaining_info, NULL);
        } else if (root->info2.end_block == end_block) {
            // Se os blocos a liberar estão no final
            Info remaining_info = {'O', root->info2.start_block, start_block - 1};
            root->info2.start_block = start_block;
            root->info2.status = 'L';
            insert_tree_23(NULL, &root, remaining_info, NULL);
        } else {
            // Se os blocos estão no meio do intervalo
            Info left_info = {'O', root->info2.start_block, start_block - 1};
            Info right_info = {'O', end_block + 1, root->info2.end_block};
            root->info2.start_block = start_block;
            root->info2.end_block = end_block;
            root->info2.status = 'L';
            insert_tree_23(NULL, &root, left_info, NULL);
            insert_tree_23(NULL, &root, right_info, NULL);
        }

        // Concatenar nós adjacentes
        concatenate_adjacent_nodes(root);
        free_result = true;
    }

    // Procura nos filhos se a liberação ainda não foi realizada
    if (!free_result) {
        free_result = free_blocks(root->left_child, start_block, end_block) ||
                      free_blocks(root->middle_child, start_block, end_block) ||
                      (root->two_info && free_blocks(root->right_child, start_block, end_block));
    }

    return free_result;
}


// Função principal
int main() 
{
    Tree23 *root = NULL;
    Info rise;

    // Insere alguns nós para teste
    insert_tree_23(NULL, &root, (Info){'O', 0, 9}, &rise);   // Nó ocupado: 0-9
    insert_tree_23(NULL, &root, (Info){'L', 10, 19}, &rise); // Nó livre: 10-19
    insert_tree_23(NULL, &root, (Info){'O', 20, 29}, &rise); // Nó ocupado: 20-29
    // insert_tree_23(NULL, &root, (Info){'O', 30, 39}, &rise); // Nó ocupado: 20-29
    // insert_tree_23(NULL, &root, (Info){'L', 40, 49}, &rise); // Nó ocupado: 20-29
    // insert_tree_23(NULL, &root, (Info){'O', 50, 59}, &rise); // Nó ocupado: 20-29

    // Solicita ao usuário os blocos a liberar
    int start_block, end_block;
    printf("Informe o bloco inicial e o bloco final para liberar (ex: 0 4): ");
    scanf("%d %d", &start_block, &end_block);

    // Tenta liberar os blocos
    if (!free_blocks(root, start_block, end_block)) {
        printf("Não foi possível liberar os blocos %d - %d.\n", start_block, end_block);
    }

    // Imprime a árvore após a liberação
    printf("\nÁrvore após a liberação:\n");
    print_tree_in_order(root);

    return 0;
}
