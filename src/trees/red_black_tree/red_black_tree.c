
#include "red_black_tree.h"
#include "../../utils/aux.h"

// Função para alocar um nó na árvore Rubro-Negra
Red_Black_Tree *allocate_red_black(Info_rb info) 
{
    Red_Black_Tree *node = (Red_Black_Tree *)malloc(sizeof(Red_Black_Tree));
    
    ASSERT_ALLOC(node, "allocate red_black");

    // Copia os dados
    strcpy(node->info.eng_word, info.eng_word);
    node->info.unit = info.unit;

    // Configurações iniciais
    node->color = RED;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Função para desalocar toda a árvore Rubro-Negra
void deallocate_red_black_tree(Red_Black_Tree *root) 
{
    if (root) 
    {
        deallocate_red_black_tree(root->left);  // Desaloca subárvore esquerda
        deallocate_red_black_tree(root->right); // Desaloca subárvore direita

        free(root); 
    }
}


// Funções auxiliares
Color color(Red_Black_Tree *root) 
{
    return (root == NULL) ? BLACK : root->color;
}

void rotateLeft(Red_Black_Tree **root) 
{
    if (root && *root && (*root)->right) 
    {
        Red_Black_Tree *aux = (*root)->right;
        (*root)->right = aux->left;
        aux->left = *root;
        aux->color = (*root)->color;
        (*root)->color = RED;
        *root = aux;
    }
}

void rotateRight(Red_Black_Tree **root) 
{
    if (root && *root && (*root)->left) 
    {
        Red_Black_Tree *aux = (*root)->left;

        (*root)->left = aux->right;
        aux->right = *root;
        aux->color = (*root)->color;
        (*root)->color = RED;
        *root = aux;
    }
}

void swapColor(Red_Black_Tree *root) 
{
    if (root != NULL) 
    {
        root->color = !root->color;
        if (root->left) 
            root->left->color = !root->left->color;
        if (root->right) 
            root->right->color = !root->right->color;
    }
}

void move2LeftRED(Red_Black_Tree **root) 
{
    if (root && *root) 
    {
        swapColor(*root);
        if ((*root)->right && color((*root)->right->left) == RED) 
        {
            rotateRight(&((*root)->right));
            rotateLeft(root);
            swapColor(*root);
        }
    }
}

void move2RightRED(Red_Black_Tree **root) 
{
    if (root && *root) 
    {
        swapColor(*root);
        if ((*root)->left && color((*root)->left->left) == RED) 
        {
            rotateRight(root);
            swapColor(*root);
        }
    }
}

Red_Black_Tree *findMin(Red_Black_Tree *root) 
{
    while (root && root->left) 
        root = root->left;
    
    return root;
}


void balance(Red_Black_Tree **root) 
{
    if (root && *root) 
    {
        if (color((*root)->right) == RED) 
            rotateLeft(root);
        if (color((*root)->left) == RED && color((*root)->left->left) == RED) 
            rotateRight(root);
        if (color((*root)->left) == RED && color((*root)->right) == RED) 
            swapColor(*root);
    }
}

void removeMin(Red_Black_Tree **root) 
{
    if (root && *root) 
    {
        if ((*root)->left == NULL) 
        {
            free(*root);
            *root = NULL;
        } 
        else 
        {
            if (color((*root)->left) == BLACK && color((*root)->left->left) == BLACK) 
                move2LeftRED(root);
            
            removeMin(&((*root)->left));
            balance(root);
        }
    }
}

bool removeNode(Red_Black_Tree **root, const char *word) 
{
    bool found = false; 

    if (root && *root) 
    {
        if (strcmp(word, (*root)->info.eng_word) < 0) 
        {
            // Continua para o lado esquerdo
            if ((*root)->left && color((*root)->left) == BLACK && color((*root)->left->left) == BLACK) 
                move2LeftRED(root);
            
            found = removeNode(&((*root)->left), word);
        } 
        else 
        {
            if (color((*root)->left) == RED) 
                rotateRight(root);

            if (strcmp(word, (*root)->info.eng_word) == 0) 
            {
                found = true;

                if ((*root)->right == NULL) 
                {
                    free(*root);
                    *root = NULL;
                } 
                else 
                {
                    Red_Black_Tree *min = findMin((*root)->right);
                    (*root)->info = min->info;

                    removeMin(&((*root)->right));
                }
            } 
            else 
            {
                if ((*root)->right && color((*root)->right) == BLACK 
                && color((*root)->right->left) == BLACK) 
                    move2RightRED(root);
                
                found = removeNode(&((*root)->right), word);
            }
        }

        balance(root);
    }

    return found; 
}

bool removeInTree(Red_Black_Tree **root, const char *palavra) 
{
    bool result = removeNode(root, palavra); 

    if (*root) 
        (*root)->color = BLACK; 
    
    return result; 
}

// Insere um elemento na árvore Rubro-Negra
Red_Black_Tree *insert(Red_Black_Tree **root, Info_rb info) 
{
    Red_Black_Tree *inserted = NULL;

    if (*root == NULL) 
    { // Caso base: cria um novo nó
        Red_Black_Tree *new = allocate_red_black(info);        
        *root = new;
        inserted = new;
    } 
    else 
    {
        // Insere no lado esquerdo ou direito
        if (strcmp(info.eng_word, (*root)->info.eng_word) < 0) 
            inserted = insert(&((*root)->left), info);
        else if (strcmp(info.eng_word, (*root)->info.eng_word) > 0) 
            inserted = insert(&((*root)->right), info);
        else 
            inserted = NULL;
        
        balance(root);
    }

    return inserted;
}


// Função principal para inserir, garantindo que a root seja preta
Red_Black_Tree* register_rb(Red_Black_Tree *root, Info_rb info) 
{
    root = insert(&root, info);

    if (root) 
        root->color = BLACK;

    return root;
}
