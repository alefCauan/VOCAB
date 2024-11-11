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


void remove_eng_word_no_children(Binary_tree **root, Binary_tree *current, Binary_tree *parent)
{
    if (parent == NULL) 
        *root = NULL;
    else if (parent->right == current)
        parent->right = NULL;
    else
        parent->left = NULL;

    free(current);
}

void remove_eng_word_one_child(Binary_tree **root, Binary_tree *current, Binary_tree *parent)
{
    Binary_tree *child = (current->left != NULL) ? current->left : current->right;

    if (parent == NULL) 
        *root = child;
    else if (parent->right == current)
        parent->right = child;
    else
        parent->left = child;

    free(current);
}


void remove_eng_word_two_children(Binary_tree **root, Binary_tree *current)
{
    // Encontrar o sucessor (menor valor na subárvore direita)
    Binary_tree *successor = current->right;
    Binary_tree *successor_parent = current;

    while (successor->left != NULL)
    {
        successor_parent = successor;
        successor = successor->left;
    }

    // Copiar os dados do sucessor para o nó atual
    current->info = successor->info;

    // Remover o sucessor da árvore
    if (successor_parent->left == successor)
        successor_parent->left = successor->right;
    else
        successor_parent->right = successor->right;

    free(successor);
}

bool remove_eng_word_bin(Binary_tree **root, Info_bin info_bin)
{
    Binary_tree *current;
    current = *root;
    Binary_tree *parent;
    parent = NULL;
    bool result = true;

    // Procura o nó a ser removido
    while (current != NULL && strcmp(current->info.eng_word, info_bin.eng_word) != 0) 
    {
        parent = current;
        if (strcmp(info_bin.eng_word, current->info.eng_word) > 0)
            current = current->right;
        else
            current = current->left;
    }

    // Se o nó não for encontrado
    if (current != NULL)
    {
        if (current->left == NULL && current->right == NULL)
            remove_eng_word_no_children(root, current, parent);
        else if (current->left != NULL && current->right != NULL)
            remove_eng_word_two_children(root, current);
        else 
            remove_eng_word_one_child(root, current, parent);
    }
    else
        result = false;

    return result;
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