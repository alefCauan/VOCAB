#include "../src/trees/tree_23/tree_23.h"
#include <assert.h>

// Função auxiliar para criar Info com uma palavra
Info create_info(const char* word) {
    Info info;
    strcpy(info.br_word, word);
    return info;
}

// Função para verificar se a árvore está balanceada
int get_height(Zwei_drei_tree* root) 
{
    if (root == NULL) return 0;
    
    int left = get_height(root->left);
    int mid = get_height(root->mid);
    int right = get_height(root->right);
    
    return 1 + (left > mid ? (left > right ? left : right) : (mid > right ? mid : right));
}

// Verifica se todas as folhas estão no mesmo nível
bool verify_leaf_level(Zwei_drei_tree* root, int current_level, int* leaf_level) {
    if (root == NULL) return true;
    
    if (is_leaf(root)) {
        if (*leaf_level == -1) {
            *leaf_level = current_level;
        } else if (*leaf_level != current_level) {
            return false;
        }
        return true;
    }
    
    return verify_leaf_level(root->left, current_level + 1, leaf_level) &&
           verify_leaf_level(root->mid, current_level + 1, leaf_level) &&
           (root->right == NULL || verify_leaf_level(root->right, current_level + 1, leaf_level));
}

// Função para verificar propriedades da árvore 2-3
void verify_tree_properties(Zwei_drei_tree* root) 
{
    if (root == NULL) return;

    // Verifica se as folhas estão no mesmo nível
    int leaf_level = -1;
    assert(verify_leaf_level(root, 0, &leaf_level) && "Folhas em níveis diferentes!");

    // Verifica ordenação
    if (root->two_info) {
        assert(strcmp(root->info1.br_word, root->info2.br_word) < 0 && "Nó com duas informações fora de ordem!");
    }

    // Verifica filhos
    if (!is_leaf(root)) {
        assert(root->left != NULL && root->mid != NULL && "Nó interno sem filhos obrigatórios!");
        if (root->two_info) {
            assert(root->right != NULL && "Nó com duas informações sem filho direito!");
        }
    }

    // Recursão para os filhos
    if (!is_leaf(root)) {
        verify_tree_properties(root->left);
        verify_tree_properties(root->mid);
        if (root->right) {
            verify_tree_properties(root->right);
        }
    }
}

int main() {
    Zwei_drei_tree *root = NULL;
    Info rise;  // Variável auxiliar para crescimento da árvore

    printf("=== Teste Robusto da Árvore 2-3 ===\n\n");

    // Array com palavras para teste (em ordem alfabética para facilitar verificação)
    const char* words[] = {
        "amor", "bola", "casa", "dado", "eco",
        "faca", "gato", "hotel", "iglu", "java",
        "kiwi", "lima", "mapa", "nabo", "ovo"
    };
    const int n_words = sizeof(words) / sizeof(words[0]);

    // 1. Teste de Inserção
    printf("1. Testando inserções...\n");
    for (int i = 0; i < n_words; i++) {
        Info info = create_info(words[i]);
        insert_tree_23(NULL, &root, info, &rise);
        printf("Inserido: %s\n", words[i]);
        print_tree(root, 0);
        printf("\n");
        verify_tree_properties(root);
    }

    // 2. Teste de Busca
    printf("\n2. Testando buscas...\n");
    for (int i = 0; i < n_words; i++) {
        Info info = create_info(words[i]);
        int a;
        assert(search_23_tree(root, info.br_word, &a) && "Busca falhou para palavra existente!");
        printf("Encontrado: %s\n", words[i]);
    }

    // 3. Teste de Remoção - casos específicos
    printf("\n3. Testando remoções específicas...\n");

    // // 3.1 Remove folha com duas informações
    // printf("\nRemovendo 'amor' (folha com duas informações)...\n");
    // remove_23(&root, create_info("amor"));
    // print_tree(root, 0);
    // verify_tree_properties(root);

    // // 3.2 Remove elemento que força redistribuição
    // printf("\nRemovendo 'casa' (força redistribuição)...\n");
    // remove_23(&root, create_info("casa"));
    // print_tree(root, 0);
    // verify_tree_properties(root);

    // // 3.3 Remove elemento que força fusão
    // printf("\nRemovendo 'eco' (força fusão)...\n");
    // remove_23(&root, create_info("eco"));
    // print_tree(root, 0);
    // verify_tree_properties(root);

    // // 3.4 Remove elemento da raiz
    // printf("\nRemovendo elemento da raiz...\n");
    // remove_23(&root, create_info("iglu"));
    // print_tree(root, 0);
    // verify_tree_properties(root);

    // 4. Teste de Remoção em massa
    printf("\n4. Testando remoção em massa...\n");
    for (int i = n_words - 1; i >= 0; i--) {
        Info info = create_info(words[i]);
        int info1;
        if (search_23_tree(root, info.br_word, &info1)) {  // só remove se existir
            printf("\nRemovendo: %s\n", words[i]);
            remove_23(&root, info.br_word);
            print_tree(root, 0);
            verify_tree_properties(root);
        }
    }

    // 5. Teste final - árvore deve estar vazia
    printf("\n5. Verificação final...\n");
    assert(root == NULL && "Árvore deveria estar vazia após todas as remoções!");
    printf("Árvore está vazia como esperado!\n");

    printf("\n=== Todos os testes passaram com sucesso! ===\n");

    deallocate_tree(root);

    return 0;
}