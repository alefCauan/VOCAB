#include <stdio.h>
#include <stdbool.h>
#include "block.h" 


int main() {
    Tree23 *root = NULL;

    // Insere alguns nós para teste
    Info rise;
    insert_tree_23(NULL, &root, (Info){'L', 0, 9}, &rise);   // Blocos 0 a 9 livres
    insert_tree_23(NULL, &root, (Info){'O', 10, 19}, &rise); // Blocos 10 a 19 ocupados
    insert_tree_23(NULL, &root, (Info){'L', 20, 34}, &rise); // Blocos 20 a 34 livres

    // Solicita ao usuário o valor do start_block para encontrar o maior pai lógico
    int start_block;
    printf("Informe o valor do start_block para encontrar o maior pai lógico: ");
    scanf("%d", &start_block);

    // Tenta encontrar o maior pai lógico
    Tree23 *bigger_dad = search_23_bigger_dad(root, start_block);
    if (bigger_dad) {
        printf("Maior pai lógico encontrado:\n");
        printf("[Status: %c, Start: %d, End: %d]\n", bigger_dad->info1.status, bigger_dad->info1.start_block, bigger_dad->info1.end_block);
        if (bigger_dad->two_info) {
            printf("[Status: %c, Start: %d, End: %d]\n", bigger_dad->info2.status, bigger_dad->info2.start_block, bigger_dad->info2.end_block);
        }
    } else {
        printf("Nenhum maior pai lógico encontrado para o start_block %d.\n", start_block);
    }

    // Solicita ao usuário o valor do start_block para encontrar o menor pai lógico
    printf("\nInforme o valor do start_block para encontrar o menor pai lógico: ");
    scanf("%d", &start_block);

    // Tenta encontrar o menor pai lógico
    Tree23 *small_dad = search_23_small_dad(root, start_block);
    if (small_dad) {
        printf("Menor pai lógico encontrado:\n");
        printf("[Status: %c, Start: %d, End: %d]\n", small_dad->info1.status, small_dad->info1.start_block, small_dad->info1.end_block);
        if (small_dad->two_info) {
            printf("[Status: %c, Start: %d, End: %d]\n", small_dad->info2.status, small_dad->info2.start_block, small_dad->info2.end_block);
        }
    } else {
        printf("Nenhum menor pai lógico encontrado para o start_block %d.\n", start_block);
    }

    // Imprime a árvore após as buscas
    printf("\nÁrvore 2-3 atual (in-order):\n");
    print_tree_in_order(root);

    return 0;
}