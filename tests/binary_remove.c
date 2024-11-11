#include "../src/trees/binary_tree/binary.h"


int main() 
{
    Binary_tree *root = NULL;

    // Definindo alguns nós para inserir
    Info_bin info1 = {"apple", 1};
    Info_bin info2 = {"banana", 2};
    Info_bin info3 = {"cherry", 3};
    Info_bin info4 = {"date", 4};
    Info_bin info5 = {"fig", 5};
    Info_bin info6 = {"ababa", 1};


    // Inserindo os nós na árvore binária
    register_bin(&root, info1);
    register_bin(&root, info2);
    register_bin(&root, info3);
    register_bin(&root, info4);
    register_bin(&root, info5);
    register_bin(&root, info6);

    printf("Árvore após as inserções:\n");
    print_binary_tree(root, 0);

    // Removendo alguns nós da árvore binária
    remove_eng_word_bin(&root, info3); // Removendo "cherry"
    printf("\nÁrvore após remover 'cherry':\n");
    print_binary_tree(root, 0);

    remove_eng_word_bin(&root, info1); // Removendo "apple"
    printf("\nÁrvore após remover 'apple':\n");
    print_binary_tree(root, 0);

    remove_eng_word_bin(&root, info5); // Removendo "fig"
    printf("\nÁrvore após remover 'fig':\n");
    print_binary_tree(root, 0);

    // Desalocar a árvore binária
    deallocate_binary_tree(root);

    return 0;
}

