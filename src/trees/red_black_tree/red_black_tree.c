
#include "red_black_tree.h"

// Função para alocar um nó na árvore Rubro-Negra
Red_Black_Tree *allocate_red_black(Info_rb info) {
    Red_Black_Tree *node = (Red_Black_Tree *)malloc(sizeof(Red_Black_Tree));
    if (node == NULL) {
        perror("Erro ao alocar nó da árvore Rubro-Negra");
        exit(EXIT_FAILURE);
    }

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
void deallocate_red_black_tree(Red_Black_Tree *root) {
    if (root) {
        deallocate_red_black_tree(root->left);  // Desaloca subárvore esquerda
        deallocate_red_black_tree(root->right); // Desaloca subárvore direita

        free(root); 
    }
}


// Funções auxiliares
int color(Red_Black_Tree *H) {
    return (H == NULL) ? BLACK : H->color;
}

void rotateLeft(Red_Black_Tree **root) {
    if (root && *root && (*root)->right) {
        Red_Black_Tree *aux = (*root)->right;
        (*root)->right = aux->left;
        aux->left = *root;
        aux->color = (*root)->color;
        (*root)->color = RED;
        *root = aux;
    }
}

void rotateRight(Red_Black_Tree **root) {
    if (root && *root && (*root)->left) {
        Red_Black_Tree *aux = (*root)->left;
        (*root)->left = aux->right;
        aux->right = *root;
        aux->color = (*root)->color;
        (*root)->color = RED;
        *root = aux;
    }
}

void swapColor(Red_Black_Tree *H) {
    if (H != NULL) {
        H->color = !H->color;
        if (H->left) H->left->color = !H->left->color;
        if (H->right) H->right->color = !H->right->color;
    }
}

void move2LeftRED(Red_Black_Tree **H) {
    if (H && *H) {
        swapColor(*H);
        if ((*H)->right && color((*H)->right->left) == RED) {
            rotateRight(&((*H)->right));
            rotateLeft(H);
            swapColor(*H);
        }
    }
}

void move2RightRED(Red_Black_Tree **H) {
    if (H && *H) {
        swapColor(*H);
        if ((*H)->left && color((*H)->left->left) == RED) {
            rotateRight(H);
            swapColor(*H);
        }
    }
}

Red_Black_Tree* findMin(Red_Black_Tree* H) {
    while (H && H->left) {
        H = H->left;
    }
    return H;
}


void balance(Red_Black_Tree **H) {
    if (H && *H) {
        if (color((*H)->right) == RED) {
            rotateLeft(H);
        }
        if (color((*H)->left) == RED && color((*H)->left->left) == RED) {
            rotateRight(H);
        }
        if (color((*H)->left) == RED && color((*H)->right) == RED) {
            swapColor(*H);
        }
    }
}

void removeMin(Red_Black_Tree **H) {
    if (H && *H) {
        if ((*H)->left == NULL) {
            free(*H);
            *H = NULL;
        } else {
            if (color((*H)->left) == BLACK && color((*H)->left->left) == BLACK) {
                move2LeftRED(H);
            }
            removeMin(&((*H)->left));
            balance(H);
        }
    }
}

int removeNode(Red_Black_Tree **H, const char *word) {
    int found = 0; 

    if (H && *H) {
        if (strcmp(word, (*H)->info.eng_word) < 0) {
            // Continua para o lado esquerdo
            if ((*H)->left && color((*H)->left) == BLACK && color((*H)->left->left) == BLACK) {
                move2LeftRED(H);
            }
            found = removeNode(&((*H)->left), word);
        } else {
            if (color((*H)->left) == RED) {
                rotateRight(H);
            }

            if (strcmp(word, (*H)->info.eng_word) == 0) {
                // Encontrou o nó para remoção
                found = 1;
                if ((*H)->right == NULL) {
                    // Nó sem subárvore direita, apenas remove
                    free(*H);
                    *H = NULL;
                } else {
                    // Substitui o nó pelo menor da subárvore direita
                    Red_Black_Tree *min = findMin((*H)->right);
                    (*H)->info = min->info;
                    removeMin(&((*H)->right));
                }
            } else {
                if ((*H)->right && color((*H)->right) == BLACK && color((*H)->right->left) == BLACK) {
                    move2RightRED(H);
                }
                found = removeNode(&((*H)->right), word);
            }
        }

        balance(H);
    }

    return found; 
}

int removeInTree(Red_Black_Tree **root, const char *palavra) {
    int result = removeNode(root, palavra); 
    if (*root) {
        (*root)->color = BLACK; 
    }
    return result; 
}

// Insere um elemento na árvore Rubro-Negra
Red_Black_Tree* insert(Red_Black_Tree **H, Info_rb info) {
    Red_Black_Tree *inserted = NULL;

    if (*H == NULL) { // Caso base: cria um novo nó
        Red_Black_Tree *new = allocate_red_black(info);        
        *H = new;
        inserted = new;
    } else {
        // Insere no lado esquerdo ou direito
        if (strcmp(info.eng_word, (*H)->info.eng_word) < 0) {
            inserted = insert(&((*H)->left), info);
        } else if (strcmp(info.eng_word, (*H)->info.eng_word) > 0) {
            inserted = insert(&((*H)->right), info);
        } else {
            // Palavra já existe, nada é alterado
            inserted = NULL;
        }

        // Reequilibra a árvore após a inserção
        if (cor((*H)->right) == RED && cor((*H)->left) != RED) {
            rotateLeft(H);
        }
        if (cor((*H)->left) == RED && cor((*H)->left->left) == RED) {
            rotateRight(H);
        }
        if (cor((*H)->left) == RED && cor((*H)->right) == RED) {
            swapColor(*H);
        }
    }

    return inserted;
}


// Função principal para inserir, garantindo que a root seja preta
Red_Black_Tree* register_rb(Red_Black_Tree* root, Info_rb info) {
    root = insert(&root, info);
    if (root) root->color = BLACK;
    return root;
}
