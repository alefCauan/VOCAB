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

Tree23 *alloc_tree(Info info, Tree23 *left, Tree23 *middle_child, Tree23 *right_child)
{
	Tree23 *node;

	node = (Tree23 *)malloc(sizeof(Tree23));

	(*node).info1 = info;
	// (*node).info2 = info;
	
	(*node).two_info = false;
	(*node).left_child = left;
	(*node).middle_child = middle_child;
	(*node).right_child = right_child;

	return node;
}


void deallocateTree2(Tree23 **node)
{
    free(*node);
    *node = NULL;
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

Tree23 *break_node(Tree23 **root, Info info, Info *rise, Tree23 *b_node) {
    Tree23 *new_node;

    if (info.start_block < (*root)->info1.start_block) 
    {
        // O novo valor é o menor e deve ser promovido para o pai
        *rise = (*root)->info1; // info1 é promovido
        new_node = alloc_tree((*root)->info2, (*root)->middle_child, (*root)->right_child, NULL);
        (*root)->info1 = info; // O novo valor se torna info1
        (*root)->middle_child = b_node; // O novo filho é atribuído ao meio
    } 
    else if (!(*root)->two_info || info.start_block < (*root)->info2.start_block) 
    {
        // O novo valor está no meio e deve ser promovido
        *rise = info; // O novo valor é promovido
        new_node = alloc_tree((*root)->info2, b_node, (*root)->right_child, NULL);
    } 
    else 
    {
        // O novo valor é o maior e deve ser promovido para o pai
        *rise = (*root)->info2; // info2 é promovido
        new_node = alloc_tree(info, (*root)->right_child, b_node, NULL);
    }

    // Atualiza o nó atual para refletir a divisão
    (*root)->two_info = false; // O nó original agora tem apenas um valor
    (*root)->right_child = NULL; // Remove o filho direito (agora no novo nó)

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


bool is_info1(Tree23 *node, int start_block) {
    if (node == NULL) return false; // Evita acesso inválido à memória
    return node->info1.start_block == start_block;
}


bool is_info2(Tree23 *node, int start_block, int end_block) {
    return node->two_info &&
           node->info2.start_block == start_block && node->info2.end_block == end_block;
}


static int height(Tree23 *node)
{
    int h = -1;

    if(node != NULL)
        h = 1 + height(node->left_child);

    return h;
}


static int is_removable(Tree23 *root)
{
    int possible = 0;

    if(root != NULL)
    {
        possible = root->two_info;

        if(!possible)
        {
            possible = is_removable(root->middle_child);

            if(!possible)
                possible = is_removable(root->left_child);
        }
    }

    return possible;
}


static Tree23 *join_node(Tree23 *child1, Info info, Tree23 *bigger_node, Tree23 **root) {
    // Adiciona o novo valor ao nó `child1` com o nó maior
    add_tree_23(&child1, info, bigger_node);

    if ((*root)->two_info) {
        // Se o nó raiz possui dois valores, atualiza para conter apenas um
        (*root)->two_info = false;
    } else {
        // Caso contrário, desaloca a raiz
        free(*root);
        *root = NULL;
    }

    return child1; // Retorna o nó atualizado
}


Info bigger_info_node(Tree23 *root)
{
    return root->two_info ? root->info2 : root->info1;
}

Tree23 *search_23_lower_child(Tree23 *root, Tree23 **dad) {
    Tree23 *child = root;

    while (!is_leaf(child)) {
        *dad = child;
        child = child->left_child;
    }

    return child;
}

Tree23 *search_23_bigger_child(Tree23 *root, Tree23 **dad, Info *bigger_value) {
    Tree23 *child = root;

    while (!is_leaf(child)) {
        *dad = child;
        if (!child->two_info)
            child = child->middle_child;
        else
            child = child->right_child;
    }

    if (child != NULL) {
        *bigger_value = child->info2; // O maior valor será sempre `info2` em um nó com dois valores
    }

    return child;
}


Tree23 *search_23_dad(Tree23 *root, int start_block) {
    Tree23 *dad = NULL;

    if (root != NULL) {
        // Verifica se o `start_block` não pertence a nenhum intervalo atual
        if (!((root->info1.start_block <= start_block && start_block <= root->info1.end_block) ||
              (root->two_info && root->info2.start_block <= start_block && start_block <= root->info2.end_block))) {

            // Decide para qual filho seguir com base em `start_block`
            if (start_block < root->info1.start_block) {
                dad = search_23_dad(root->left_child, start_block);
            } else if (!root->two_info || start_block < root->info2.start_block) {
                dad = search_23_dad(root->middle_child, start_block);
            } else {
                dad = search_23_dad(root->right_child, start_block);
            }

            // Caso nenhum filho seja adequado, retorna o nó atual como pai
            if (dad == NULL) {
                dad = root;
            }
        }
    }

    return dad;
}


Tree23 *search_23_bigger_dad(Tree23 *root, int start_block) {
    Tree23 *dad = NULL;

    if (root != NULL) {
        if (!(start_block >= root->info1.start_block && start_block <= root->info1.end_block) &&
            !(root->two_info && start_block >= root->info2.start_block && start_block <= root->info2.end_block)) {
            if (start_block < root->info1.start_block) {
                dad = search_23_bigger_dad(root->left_child, start_block);
            } else if (!root->two_info || start_block < root->info2.start_block) {
                dad = search_23_bigger_dad(root->middle_child, start_block);
            } else {
                dad = search_23_bigger_dad(root->right_child, start_block);
            }

            if (dad == NULL &&
                ((root->two_info == false && start_block > root->info1.start_block) ||
                 (root->two_info && start_block > root->info2.start_block))) {
                dad = root;
            }
        }
    }

    return dad;
}

Tree23 *search_23_small_dad(Tree23 *root, int start_block) {
    Tree23 *dad = NULL;

    if (root != NULL) {
        if (!(start_block >= root->info1.start_block && start_block <= root->info1.end_block) &&
            !(root->two_info && start_block >= root->info2.start_block && start_block <= root->info2.end_block)) {
            if (start_block < root->info1.start_block) {
                dad = search_23_small_dad(root->left_child, start_block);
            } else if (!root->two_info || start_block < root->info2.start_block) {
                dad = search_23_small_dad(root->middle_child, start_block);
            } else {
                dad = search_23_small_dad(root->right_child, start_block);
            }

            if (dad == NULL && start_block < root->info1.start_block) {
                dad = root;
            }
        }
    }

    return dad;
}

static Tree23 *search_23_small_dad_info2(Tree23 *root, int start_block) {
    Tree23 *dad = NULL;

    if (root != NULL) {
        if (!(root->info1.start_block <= start_block && start_block <= root->info1.end_block) &&
            !(root->two_info && root->info2.start_block <= start_block && start_block <= root->info2.end_block)) {

            if (start_block < root->info1.start_block) {
                dad = search_23_small_dad_info2(root->left_child, start_block);
            } else if (!root->two_info || start_block < root->info2.start_block) {
                dad = search_23_small_dad_info2(root->middle_child, start_block);
            } else {
                dad = search_23_small_dad_info2(root->right_child, start_block);
            }

            if (dad == NULL && root->two_info && start_block > root->info2.start_block) {
                dad = root;
            }
        }
    }

    return dad;
}

static int wave(Info saindo, Info *input, Tree23 *dad, Tree23 **source, Tree23 **root, Tree23 **bigger_node, 
                int (*remove_func)(Tree23 **, int, Tree23 *, Tree23 **, Tree23 **)) {
    // Remove o valor especificado usando a função passada por parâmetro
    int removed = remove_func(root, saindo.start_block, dad, source, bigger_node);

    // Atualiza o valor de entrada com o valor removido
    *input = saindo;

    return removed;
}


int remove_wave1(Tree23 **root, int start_block, Tree23 *dad, Tree23 **source, Tree23 **bigger_node) {
    int removed = 0;

    if (*root != NULL) {
        // Verifica se o valor está no info1 ou info2 do nó atual
        int info1 = ((*root)->info1.start_block <= start_block && start_block <= (*root)->info1.end_block);
        int info2 = ((*root)->two_info &&
                     (*root)->info2.start_block <= start_block && start_block <= (*root)->info2.end_block);

        if (info1 || info2) {
            removed = 1;

            if (is_leaf(*root)) {
                // Caso o nó atual seja uma folha
                if ((*root)->two_info) {
                    // Se o nó tem dois valores, ajusta os campos
                    if (info1)
                        (*root)->info1 = (*root)->info2;

                    (*root)->two_info = false;
                } else {
                    // Caso o nó tenha apenas um valor
                    if (dad == NULL) {
                        // Se não houver pai, desaloca o nó
                        free(*root);
                        *root = NULL;
                    } else {
                        Tree23 *dad_aux;
                        Info info_dad;

                        // Verifica se o nó atual é filho esquerdo ou filho do meio
                        if (*root == dad->left_child || (dad->two_info && *root == dad->middle_child)) {
                            dad_aux = search_23_dad(*source, dad->info1.start_block);

                            if (*root == dad->left_child)
                                info_dad = dad->info1;
                            else
                                info_dad = dad->info2;

                            removed = wave(info_dad, &((*root)->info1), dad_aux, source, &dad, bigger_node, remove_wave1);
                        } else {
                            // Caso seja o filho do meio ou direito
                            dad_aux = search_23_bigger_dad(*source, (*root)->info1.start_block);
                            Tree23 *minor_dad = search_23_small_dad_info2(*source, (*root)->info1.start_block);

                            if (dad_aux != NULL) {
                                if (dad_aux->info1.start_block > (*root)->info1.start_block)
                                    info_dad = dad_aux->info1;
                                else
                                    info_dad = dad_aux->info2;
                            }

                            int minor_dad_height = height(minor_dad);
                            int dad_aux_height = height(dad_aux);

                            if (dad_aux == NULL || (dad_aux != dad && minor_dad != NULL &&
                                minor_dad_height <= dad_aux_height &&
                                (info_dad.start_block > minor_dad->info2.start_block))) {
                                *bigger_node = dad;
                                (*root)->two_info = false;
                                removed = -1;
                            } else {
                                Tree23 *grandpa = search_23_dad(*source, info_dad.start_block);
                                removed = wave(info_dad, &((*root)->info1), grandpa, source, &dad_aux, bigger_node, remove_wave1);
                            }
                        }
                    }
                }
            } else if (info2) {
                // Caso o valor esteja no info2 e o nó não seja folha
                removed = remove_internal_node1(source, *root, &((*root)->info2), (*root)->middle_child, (*root)->right_child, bigger_node);
            } else if (info1) {
                // Caso o valor esteja no info1 e o nó não seja folha
                removed = remove_internal_node1(source, *root, &((*root)->info1), (*root)->left_child, (*root)->middle_child, bigger_node);
            }
        } else {
            // Se o valor não está no nó atual, continua a busca nos filhos
            if (start_block < (*root)->info1.start_block) {
                removed = remove_wave1(&(*root)->left_child, start_block, *root, source, bigger_node);
            } else if (!(*root)->two_info || start_block < (*root)->info2.start_block) {
                removed = remove_wave1(&(*root)->middle_child, start_block, *root, source, bigger_node);
            } else {
                removed = remove_wave1(&(*root)->right_child, start_block, *root, source, bigger_node);
            }
        }
    }

    return removed;
}

int remove_wave2(Tree23 **root, int start_block, Tree23 *dad, Tree23 **source, Tree23 **bigger_node) {
    int removed = 0;

    if (*root != NULL) {
        // Verifica se o valor está no info1 ou info2 do nó atual
        int info1 = ((*root)->info1.start_block <= start_block && start_block <= (*root)->info1.end_block);
        int info2 = ((*root)->two_info &&
                     (*root)->info2.start_block <= start_block && start_block <= (*root)->info2.end_block);

        if (info1 || info2) {
            removed = 1;

            if (is_leaf(*root)) {
                // Caso o nó atual seja uma folha
                if ((*root)->two_info) {
                    // Se o nó tem dois valores, ajusta os campos
                    if (info1)
                        (*root)->info1 = (*root)->info2;

                    (*root)->two_info = false;
                } else {
                    // Caso o nó tenha apenas um valor
                    if (dad == NULL) {
                        // Se não houver pai, desaloca o nó
                        deallocateTree2(root);
                        *root = NULL;
                    } else {
                        Tree23 *dad_aux;
                        Info info_dad;

                        // Verifica se o nó atual é filho do meio ou filho direito
                        if (*root == dad->middle_child || (dad->two_info && *root == dad->right_child)) {
                            dad_aux = search_23_dad(*source, dad->info1.start_block);

                            if (*root == dad->middle_child)
                                info_dad = dad->info1;
                            else
                                info_dad = dad->info2;

                            removed = wave(info_dad, &((*root)->info1), dad_aux, source, &dad, bigger_node, remove_wave2);
                        } else {
                            // Caso seja o filho esquerdo
                            dad_aux = search_23_small_dad(*source, (*root)->info1.start_block);
                            Tree23 *minor_dad = search_23_small_dad_info2(*source, (*root)->info1.start_block);
                            Tree23 *grandpa;

                            if (dad_aux == NULL || (dad_aux != dad && minor_dad != NULL)) {
                                removed = -1;
                                *bigger_node = dad;
                            } else {
                                if (dad_aux->two_info && (dad_aux->info2.start_block < (*root)->info1.start_block))
                                    info_dad = dad_aux->info2;
                                else
                                    info_dad = dad_aux->info1;

                                grandpa = search_23_dad(*source, info_dad.start_block);
                                removed = wave(info_dad, &((*root)->info1), grandpa, source, &dad_aux, bigger_node, remove_wave2);
                            }
                        }
                    }
                }
            } else if (info2) {
                // Caso o valor esteja no info2 e o nó não seja folha
                removed = remove_internal_node2(source, *root, &((*root)->info2), (*root)->right_child, (*root)->middle_child, bigger_node);
            } else if (info1) {
                // Caso o valor esteja no info1 e o nó não seja folha
                removed = remove_internal_node2(source, *root, &((*root)->info1), (*root)->middle_child, (*root)->left_child, bigger_node);
            }
        } else {
            // Se o valor não está no nó atual, continua a busca nos filhos
            if (start_block < (*root)->info1.start_block) {
                removed = remove_wave2(&(*root)->left_child, start_block, *root, source, bigger_node);
            } else if (!(*root)->two_info || start_block < (*root)->info2.start_block) {
                removed = remove_wave2(&(*root)->middle_child, start_block, *root, source, bigger_node);
            } else {
                removed = remove_wave2(&(*root)->right_child, start_block, *root, source, bigger_node);
            }
        }
    }

    return removed;
}



static int remove_internal_node1(Tree23 **source, Tree23 *root, Info *info, Tree23 *child1, Tree23 *child2, Tree23 **bigger_node) {
    int removed;
    Tree23 *child, *dad;
    Info info_filho;

    dad = root;

    // Busca o maior filho do nó esquerdo
    child = search_23_bigger_child(child1, &dad, &info_filho);

    if (child->two_info) {
        // Se o nó filho tem dois valores, remove o maior
        *info = info_filho;
        child->two_info = false;
    } else {
        // Caso contrário, busca o menor filho do nó direito
        child = search_23_lower_child(child2, &dad);

        // Remove o valor e propaga alterações
        removed = wave(child->info1, info, dad, source, &child, bigger_node, remove_wave1);
    }

    return removed;
}

static int remove_internal_node2(Tree23 **source, Tree23 *root, Info *info, Tree23 *child1, Tree23 *child2, Tree23 **bigger_node) {
    int removed;
    Tree23 *child, *dad;
    Info info_child;

    dad = root;

    // Busca o menor filho do nó esquerdo
    child = search_23_lower_child(child1, &dad);

    if (child->two_info) {
        // Se o nó filho tem dois valores, promove o menor
        *info = child->info1;
        child->info1 = child->info2;
        child->two_info = false;
    } else {
        // Caso contrário, busca o maior filho do nó direito
        child = search_23_bigger_child(child2, &dad, &info_child);

        // Remove o valor e propaga alterações
        removed = wave(info_child, info, dad, source, &child, bigger_node, remove_wave2);
    }

    return removed;
}



int remove_23(Tree23 **root, int start_block) {
    Tree23 *bigger_node = NULL, *join_pos = NULL;

    // Primeiro passo: tentar remover usando a função remove_wave1
    int removed = remove_wave1(root, start_block, NULL, root, &join_pos);

    if (removed == -1) {
        removed = 1;

        // Obtém o maior valor do nó onde ocorreu a fusão
        Info join_value = bigger_info_node(join_pos);

        // Rebalanceia a árvore
        int removed_aux = rebalance_23(root, join_value.start_block, &bigger_node);

        if (removed_aux == -1) {
            Tree23 *dad = NULL, *join_pos2 = NULL;
            Info *input = NULL;

            // Procura o pai do nó a partir do valor de fusão
            dad = search_23_dad(*root, join_value.start_block);

            // Determina qual campo do nó filho será manipulado
            if (is_info1(join_pos, join_value.start_block)) {
                input = &(join_pos->middle_child->info1);
            } else {
                input = &(join_pos->right_child->info1);
            }

            // Aplica a função `wave` para remover e propagar alterações
            removed_aux = wave(join_value, input, dad, root, &join_pos, &join_pos2, remove_wave2);

            if (removed_aux == -1) {
                // Caso precise continuar propagando alterações
                join_value = join_pos2->info1;
                dad = search_23_dad(*root, join_value.start_block);
                removed_aux = wave(join_value, &(join_pos2->left_child->info1), dad, root, &join_pos2, &join_pos, remove_wave1);

                join_value = bigger_info_node(join_pos);
                bigger_node = NULL;
                removed_aux = rebalance_23(root, join_value.start_block, &bigger_node);
            }
        }

        // Se a raiz foi removida, ajusta a nova raiz
        if (*root == NULL) {
            *root = bigger_node;
        }
    }

    return removed;
}

static int balance_23(Tree23 **root, Tree23 *child1, Tree23 **child2, Info info, Tree23 **bigger_node) {
    int balanced = 0;

    // Verifica se o filho 2 está vazio ou não possui dois valores
    if (*child2 == NULL || !(*child2)->two_info) {
        if (*child2 != NULL) {
            // Desaloca o segundo filho 
            deallocateTree2(child2);
        }

        // Junta o filho 1, o info e o maior nó em um único nó
        *bigger_node = join_node(child1, info, *bigger_node, root);
        balanced = 1;
    }

    return balanced;
}

int rebalance_23(Tree23 **root, int start_block, Tree23 **bigger_node) {
    int balanced = 0;

    if (*root != NULL) {
        if (!is_leaf(*root)) {
            // Decide para qual filho continuar a rebalancear com base no `start_block`
            if (start_block < (*root)->info1.start_block) {
                balanced = rebalance_23(&((*root)->left_child), start_block, bigger_node);
            } else if (!(*root)->two_info || start_block < (*root)->info2.start_block) {
                if ((*root)->left_child->two_info && !is_removable((*root)->middle_child)) {
                    balanced = -1;
                } else {
                    balanced = rebalance_23(&((*root)->middle_child), start_block, bigger_node);
                }
            } else {
                if ((*root)->middle_child->two_info && !is_removable((*root)->right_child)) {
                    balanced = -1;
                } else {
                    balanced = rebalance_23(&((*root)->right_child), start_block, bigger_node);
                }
            }

            // Reorganiza os nós após rebalancear
            if (balanced != -1) {
                if (!(*root)->two_info) {
                    balanced = balance_23(root, (*root)->left_child, &((*root)->middle_child), (*root)->info1, bigger_node);
                } else {
                    balanced = balance_23(root, (*root)->middle_child, &((*root)->right_child), (*root)->info2, bigger_node);
                }
            }
        }
    }

    return balanced;
}
