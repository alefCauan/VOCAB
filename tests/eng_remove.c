#include "../src/trees/binary_tree/binary.h"


// Função principal de teste
int main() {
    Binary_tree *root = NULL;

    Info_bin words[] = {
        {"house", 1}, {"car", 2}, {"tree", 3}, {"dog", 1}, {"apple", 2}, {"zebra", 3}, {"cat", 1}
    };

    for (int i = 0; i < 7; i++) {
        Binary_tree *new_node = allocate_binary(words[i]);  // Aloca um novo nó da árvore binária
        insert_bin(&root, new_node);  // Insere o nó alocado na árvore binária
    }


    // Exibe a árvore inicial
    printf("Árvore binária inicial:\n");
    print_binary_tree(root, 0);
    printf("\n");

    // Caso 1: Remoção de um nó sem filhos
    printf("Removendo 'dog' (nó sem filhos):\n");
    Info_bin target1 = {"dog"};
    remove_eng_word_bin(&root, target1);
    print_binary_tree(root, 0);
    printf("\n");

    // Caso 2: Remoção de um nó com um filho
    printf("Removendo 'cat' (nó com um filho):\n");
    Info_bin target2 = {"cat"};
    remove_eng_word_bin(&root, target2);
    print_binary_tree(root, 0);
    printf("\n");

    // Caso 3: Remoção de um nó com dois filhos
    printf("Removendo 'house' (nó com dois filhos):\n");
    Info_bin target3 = {"house"};
    remove_eng_word_bin(&root, target3);
    print_binary_tree(root, 0);
    printf("\n");

    // Caso 4: Remoção de um nó inexistente
    printf("Tentando remover 'nonexistent' (nó inexistente):\n");
    Info_bin target4 = {"nonexistent"};
    if (!remove_eng_word_bin(&root, target4)) {
        printf("Palavra 'nonexistent' não encontrada.\n");
    }
    print_binary_tree(root, 0);

    return 0;
}
