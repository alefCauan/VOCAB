#include "../src/trees/red_black_tree/red_black_tree.h"

// Função auxiliar para imprimir a árvore (apenas para depuração)
void printTree(Red_black_tree *root, int depth) {
    if (root == NULL) {
        return;
    }
    printTree(root->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("%s (%s)\n", root->info.br_word, root->color == RED ? "RED" : "BLACK");
    printTree(root->left, depth + 1);
}

// Função principal de teste
int main() {
    Red_black_tree *root = NULL;

    // Dados de teste para inserção
    Info_rb words[] = {
        {"abobora", 1},
        {"cachorro", 2},
        {"papagaio", 3},
        {"ola", 4},
        {"zebra", 5},
        {"casa", 6},
        {"pera", 7},
        {"uva", 7},
        {"gato", 7}
    };
    int numWords = sizeof(words) / sizeof(words[0]);

    // Teste: Inserção
    printf("Inserindo palavras na árvore Rubro-Negra:\n");
    for (int i = 0; i < numWords; i++) {
        root = register_rb(root, words[i]);
        printf("Inserido: %s\n", words[i].br_word);
    }

    // Imprime a árvore após inserção
    printf("\nÁrvore após inserções:\n");
    printTree(root, 0);

    // Teste: Remoção
    remove_in_tree(&root, words[8].br_word);

    // Imprime a árvore após remoção
    printf("\nÁrvore após remoções:\n");
    printTree(root, 0);

    // Teste: Remoção
    remove_in_tree(&root, words[2].br_word);

    // Imprime a árvore após remoção
    printf("\nÁrvore após remoções:\n");
    printTree(root, 0);

    // Desaloca a árvore
    deallocate_red_black_tree(root);
    root = NULL;

    printf("\nÁrvore desalocada com sucesso.\n");
    return 0;
}
