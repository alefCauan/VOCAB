#include <stdio.h>
#include <stdbool.h>
#include "block.h" 

int main() {
    Tree23 *root = NULL;
    Info rise;

    // Insere blocos na árvore
    insert_tree_23(NULL, &root, (Info){'O', 0, 9}, &rise);
    insert_tree_23(NULL, &root, (Info){'L', 10, 19}, &rise);
    insert_tree_23(NULL, &root, (Info){'O', 20, 29}, &rise);
    insert_tree_23(NULL, &root, (Info){'L', 30, 35}, &rise);
    insert_tree_23(NULL, &root, (Info){'O', 36, 40}, &rise);
    insert_tree_23(NULL, &root, (Info){'L', 41, 50}, &rise);



    // Remove o bloco 20-29
    Tree23 *bigger_node = NULL;
    int removed = remove_23(&root, 0);


    // Resultado
    if (removed) {
        printf("Bloco removido com sucesso.\n");
    } else {
        printf("Falha ao remover o bloco.\n");
    }

    // Imprime a árvore atualizada
    printf("Árvore após a remoção:\n");
    print_tree_in_order(root);

    return 0;
}
