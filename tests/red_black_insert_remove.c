#include "../src/trees/red_black_tree/red_black_tree.h"

// Função para criar e inicializar um Info_rb para teste
Info_rb create_info_rb(const char *br_word, int unit, const char *translations[], int num_translations) {
    Info_rb info;
    info.eng_words = NULL;  // Inicializa a árvore binária de traduções

    strncpy(info.br_word, br_word, sizeof(info.br_word));
    info.unit = unit;

    // Adiciona as traduções na árvore binária associada
    for (int i = 0; i < num_translations; i++) {
        Info_bin bin_info;
        strncpy(bin_info.eng_word, translations[i], sizeof(bin_info.eng_word));
        bin_info.unit = unit;

        Binary_tree *new_node = allocate_binary(bin_info);
        insert_bin(&(info.eng_words), new_node);  // Insere tradução na árvore binária
    }

    return info;
}

// Função para imprimir as palavras e traduções na árvore Rubro-Negra
void print_red_black_tree(Red_black_tree *root) 
{
    if (root) {
        printf("Palavra (PT): %s, cor: %d\n", root->info.br_word, root->color);
        printf("Traduções (EN): ");
        print_binary_tree(root->info.eng_words, 0);  // Função para imprimir a árvore binária
        printf("\n");

        print_red_black_tree(root->left);
        print_red_black_tree(root->right);
    }
}

int main() {
    // Inicializa a árvore Rubro-Negra
    Red_black_tree *rb_root = NULL;

    // Define palavras em português e suas traduções
    const char *translations1[] = {"house", "home"};
    const char *translations2[] = {"car", "automobile"};
    const char *translations3[] = {"tree", "wood"};
    const char *translations4[] = {"dog", "puppy"};
    const char *translations5[] = {"apple", "fruit"};

    // Insere palavras em português com suas traduções
    rb_root = register_rb(rb_root, create_info_rb("casa", 1, translations1, 2));
    rb_root = register_rb(rb_root, create_info_rb("carro", 1, translations2, 2));
    rb_root = register_rb(rb_root, create_info_rb("arvore", 1, translations3, 2));
    rb_root = register_rb(rb_root, create_info_rb("cachorro", 1, translations4, 2));
    rb_root = register_rb(rb_root, create_info_rb("maca", 1, translations5, 2));

    // Imprime a árvore Rubro-Negra com as traduções
    printf("Árvore Rubro-Negra após inserções:\n");
    print_red_black_tree(rb_root);

    // Libera memória
    deallocate_red_black_tree(rb_root);

    return 0;
}
