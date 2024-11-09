#include "binary.h"

Binary_tree *allocate_binary(Info_bin info) 
{
    Binary_tree *node = (Binary_tree *)malloc(sizeof(Binary_tree));

    if (node == NULL) 
    {
        perror("Erro ao alocar nó da árvore binária");
        exit(EXIT_FAILURE);
    }

    strcpy(node->info.eng_word, info.eng_word);
    node->info.unit = info.unit;

    node->left = NULL;
    node->right = NULL;

    return node;
}

void deallocate_binary_tree(Binary_tree *root)
{
    if(root)
    {
        deallocate_binary_tree(root->left);
        deallocate_binary_tree(root->right);

        free(root);
    }
}

Binary_tree *search_bin(Binary_tree *root, Info_bin info) 
{
    Binary_tree *result = NULL;  

    if (root != NULL) 
    {
        if(strcmp(root->info.eng_word, info.eng_word) == 0)
            result = root;
        else if (strcmp(info.eng_word, root->info.eng_word) < 0) 
            result = search_bin(root->left, info);
        else 
            result = search_bin(root->right, info);
    }

    return result;  
}

bool insert_bin(Binary_tree **root, Binary_tree *new)
{
    bool result = true;

    if ((*root) == NULL)
        (*root) = new;  
    else if (strcmp(new->info.eng_word, (*root)->info.eng_word) < 0)
        result = insert_bin(&(*root)->left, new);  
    else if (strcmp(new->info.eng_word, (*root)->info.eng_word) > 0) 
        result = insert_bin(&(*root)->right, new);  
    else 
        result = false;

    return root;  
}

void register_bin(Binary_tree **root, Info_bin info)
{
    Binary_tree *new = allocate_binary(info);

    if (!insert_bin(root, new))
    {
        // TODO: ERROR
    }
}

// Função para imprimir a árvore binária em ordem alfabética
void print_binary_tree(Binary_tree *root, int level) 
{
    if (root != NULL)
    {
        // Percorre o nó da esquerda (ordem in-order)
        print_binary_tree(root->left, level + 1);

        // Imprime o nível e a palavra em inglês
        for (int i = 0; i < level; i++) 
            printf("  ");
            
        printf("* %s\n", root->info.eng_word);

        // Percorre o nó da direita
        print_binary_tree(root->right, level + 1);
    }
}

void show_all_eng_words(Binary_tree *root)
{
    if(root)
    {
        show_all_eng_words(root->left);
        printf("  %s", root->info.eng_word);
        show_all_eng_words(root->right);
    }
}