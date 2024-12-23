#include "block.h"

// Function to create a new 2-3 tree node
Tree23 *createNode(char status, int start_block, int end_block) {

    Tree23 *new_node = (Tree23 *)malloc(sizeof(Tree23));
    new_node->info1.status = status;
    new_node->info1.start_block = start_block;
    new_node->info1.end_block = end_block;
    new_node->left_child = NULL;
    new_node->middle_child = NULL;
    new_node->right_child = NULL;
    return new_node;
}

Tree23 *alloc_tree(Info info, Tree23 *left, Tree23 *mid, Tree23 *right)
{
	Tree23 *node;

	node = (Tree23 *)malloc(sizeof(Tree23));

	(*node).info1 = info;
	// (*node).info2 = info;
	
	(*node).two_info = false;
	(*node).left_child = left;
	(*node).middle_child = mid;
	(*node).right_child = right;

	return node;
}

bool is_leaf(Tree23 *root)
{
	bool leaf = false; // não é folha

	if (root->left_child == NULL && root->middle_child == NULL && root->right_child == NULL)
		leaf = true;

	return leaf;
}

void add_tree_23(Tree23 **root, Info info, Tree23 *b_node)
{
    // Adiciona o novo valor ao nó, assumindo que ele ainda tem espaço para mais um valor (não está cheio)
    if (info.start_block > (*root)->info1.start_block)
    {
        // Caso o novo valor seja maior que o valor atual no nó (info1), ele será adicionado como info2
        (*root)->info2 = info;
        (*root)->right_child = b_node; // O novo nó filho é atribuído à direita
    }
    else
    {
        // Caso o novo valor seja menor que info1, os valores são reorganizados
        (*root)->info2 = (*root)->info1; // info1 se torna info2
        (*root)->info1 = info;           // O novo valor se torna info1
        (*root)->right_child = (*root)->middle_child;   // O filho do meio se move para a direita
        (*root)->middle_child = b_node;           // O novo nó filho é atribuído ao meio
    }

    (*root)->two_info = true; // Marca que o nó agora possui dois valores
}

Tree23 *break_node(Tree23 **root, Info info, Info *rise, Tree23 *b_node) 
{
    Tree23 *new_node;

    // Divide o nó cheio em dois nós e retorna o novo nó criado
    if (info.start_block < (*root)->info1.start_block) 
    {
        // O novo valor é o menor e deve ser promovido para o pai (info1 sobe)
        *rise = (*root)->info1; // info1 é promovido
        new_node = alloc_tree((*root)->info2, (*root)->middle_child, (*root)->right_child, NULL); // info2 e filhos vão para o novo nó
        (*root)->info1 = info; // O novo valor se torna info1 no nó original
        (*root)->middle_child = b_node; // O novo filho é atribuído ao meio
    } 
    else if ((*root)->two_info == false || info.start_block < (*root)->info2.start_block) 
    {
        // O novo valor está no meio e deve ser promovido para o pai
        *rise = info; // O novo valor é promovido
        new_node = alloc_tree((*root)->info2, b_node, (*root)->right_child, NULL); // info2 e o filho direito vão para o novo nó
    } 
    else 
    {
        // O novo valor é o maior e deve ser promovido para o pai (info2 sobe)
        *rise = (*root)->info2; // info2 é promovido
        new_node = alloc_tree(info, (*root)->right_child, b_node, NULL); // O novo valor e o filho direito vão para o novo nó
    }

    (*root)->two_info = false; // O nó original agora possui apenas um valor
    (*root)->right_child = NULL;     // Remove o ponteiro para o filho direito

    return new_node; // Retorna o novo nó criado
}

Tree23 *insert_tree_23(Tree23 *Dad, Tree23 **root, Info info, Info *rise)
{
    Tree23 *b_node = NULL;

    if (*root == NULL)
    {
        // Cria um novo nó caso a árvore esteja vazia
        *root = alloc_tree(info, NULL, NULL, NULL);
    }
    else if (is_leaf(*root))
    {
        // Caso o nó atual seja uma folha (não possui filhos)
        if ((*root)->two_info == false)
        {
            // Caso o nó tenha espaço, adiciona o novo valor diretamente
            add_tree_23(root, info, b_node);
        }
        else
        {
            // Caso o nó esteja cheio, realiza uma divisão (split)
            Tree23 *new_node;
            new_node = break_node(root, info, rise, b_node);

            if (Dad == NULL)
            {
                // Se não houver pai, cria um novo nó raiz
                Tree23 *parent = alloc_tree(*rise, *root, new_node, NULL);
                *root = parent; // A nova raiz se torna o nó atual
            }
            else
            {
                // Se houver pai, o novo nó criado é retornado para ser processado no nível superior
                b_node = new_node;
            }
        }
    }
    else
    {
        // Caso o nó atual não seja uma folha
        if (info.start_block < (*root)->info1.start_block)
        {
            // Se o valor for menor que info1, desce para o filho esquerdo
            b_node = insert_tree_23(*root, &((*root)->left_child), info, rise);
        }
        else if ((*root)->two_info == false || info.start_block < (*root)->info2.start_block)
        {
            // Se o valor estiver entre info1 e info2 (ou não houver info2), desce para o filho do meio
            b_node = insert_tree_23(*root, &((*root)->middle_child), info, rise);
        }
        else
        {
            // Se o valor for maior que info2, desce para o filho direito
            b_node = insert_tree_23(*root, &((*root)->right_child), info, rise);
        }

        if (b_node != NULL)
        {
            // Caso um novo nó tenha sido criado em um nível inferior
            if ((*root)->two_info == false)
            {
                // Caso o nó atual tenha espaço, adiciona o valor promovido
                add_tree_23(root, *rise, b_node);
                b_node = NULL; // Zera o nó promovido
            }
            else
            {
                // Caso o nó atual esteja cheio, realiza uma divisão (split)
                Info rise1;
                Tree23 *new_node;

                new_node = break_node(root, *rise, &rise1, b_node);

                if (Dad == NULL)
                {
                    // Se não houver pai, cria um novo nó raiz
                    Tree23 *parent = alloc_tree(rise1, *root, new_node, NULL);
                    *root = parent; // A nova raiz se torna o nó atual
                    b_node = NULL;
                }
                else
                {
                    // Se houver pai, atualiza o nó promovido e retorna para o nível superior
                    b_node = new_node;
                    *rise = rise1;
                }
            }
        }
    }

    return b_node; // Retorna o nó promovido, se houver
}

// Função para imprimir a árvore em ordem
void print_tree_in_order(Tree23 *root) {
    if (root == NULL) {
        return; // Se o nó for nulo, não há nada a imprimir
    }

    // Primeiro, percorre o filho esquerdo
    print_tree_in_order(root->left_child);

    // Imprime o primeiro valor (info1)
    printf("Status: %c, Blocks: %d - %d\n", root->info1.status, root->info1.start_block, root->info1.end_block);

    // Depois, percorre o filho do meio
    print_tree_in_order(root->middle_child);

    // Se o nó tiver dois valores, imprime o segundo valor (info2)
    if (root->two_info) {
        printf("Status: %c, Blocks: %d - %d\n", root->info2.status, root->info2.start_block, root->info2.end_block);
        
        // Percorre o filho direito, se houver
        print_tree_in_order(root->right_child);
    }
}

// Função para concatenar nós adjacentes com o mesmo status
void concatenate_adjacent_nodes(Tree23 *root) {
    // TODO: CONCATENAÇÃO DOS NÓS COM A FUNCÇÃO DE REMOVER 
}

