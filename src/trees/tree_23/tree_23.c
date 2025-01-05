#include "tree_23.h"

Zwei_drei_tree *alloc_tree(Info info, Zwei_drei_tree *left, Zwei_drei_tree *mid, Zwei_drei_tree *right)
{
	Zwei_drei_tree *node;

	node = (Zwei_drei_tree *)malloc(sizeof(Zwei_drei_tree));

	(*node).info1 = info;
	// (*node).info2 = info;
	
	(*node).two_info = false;
	(*node).left = left;
	(*node).mid = mid;
	(*node).right = right;

	return node;
}

void deallocate_tree(Zwei_drei_tree *root)
{
	if(root)
	{
		if((*root).info1.eng_words)
        	deallocate_binary_tree(root->info1.eng_words);
        if ((*root).two_info && (*root).info2.eng_words) 
            deallocate_binary_tree(root->info2.eng_words);

		deallocate_tree(root->left);
		deallocate_tree(root->mid);
		if(root->two_info)
			deallocate_tree(root->right);

		free(root);
	}
}

void deallocate_tree2(Zwei_drei_tree **node)
{
    free(*node);
    *node = NULL;
}

bool is_leaf(Zwei_drei_tree *root)
{
	bool leaf = false; // não é folha

	if (root->left == NULL )
		leaf = true;

	return leaf;
}

// Busca o menor valor à direita (sucessor)
void lower_info_right(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node) 
{
    // Vai até o extremo esquerdo da subárvore direita
    *parent_node = node;

    while (node->left != NULL) 
	{
        *parent_node = node;
        node = node->left;
    }

    *result_node = node;
}

void lower_info_left(Zwei_drei_tree *node, Zwei_drei_tree **result_node, Zwei_drei_tree **parent_node) 
{
    // Vai até o extremo direito da subárvore esquerda
    *parent_node = node;

    while (node->right != NULL) 
	{
        *parent_node = node;
        node = node->right;
    }

    *result_node = node;
}

void add_tree_23(Zwei_drei_tree **root, Info info, Zwei_drei_tree *b_node)
{
	if (strcmp(info.br_word, (*root)->info1.br_word) > 0)
	{
		(*root)->info2 = info;
		(*root)->right = b_node;
	}
	else
	{
		(*root)->info2 = (*root)->info1;
		(*root)->info1 = info;
		(*root)->right = (*root)->mid;
		(*root)->mid = b_node;
	}

	(*root)->two_info = true;
}

Zwei_drei_tree *break_node(Zwei_drei_tree **root, Info info, Info *rise, Zwei_drei_tree *b_node) 
{
    Zwei_drei_tree *new_node;

    if (strcmp(info.br_word, (*root)->info1.br_word) < 0) 
	{
        // Novo valor é o menor, `info1` deve subir, `info2` vai para o novo nó
        *rise = (*root)->info1;
        new_node = alloc_tree((*root)->info2, (*root)->mid, (*root)->right, NULL);
        (*root)->info1 = info;
        (*root)->mid = b_node;
    } 
    else if (strcmp(info.br_word, (*root)->info2.br_word) < 0) 
	{
        // Novo valor está node meio, `info` deve subir
        *rise = info;
        new_node = alloc_tree((*root)->info2, b_node, (*root)->right, NULL);
    } 
    else 
	{
        // Novo valor é o bigger_node, `info2` deve subir, `info` vai para o novo nó
        *rise = (*root)->info2;
        new_node = alloc_tree(info, (*root)->right, b_node, NULL);
    }

    (*root)->two_info = false;
    (*root)->right = NULL;

    return new_node;
}

Zwei_drei_tree *insert_tree_23(Zwei_drei_tree *Dad, Zwei_drei_tree **root, Info info, Info *rise)
{
	Zwei_drei_tree *b_node;
	b_node = NULL;
    
	if (*root == NULL)
		*root = alloc_tree(info, NULL, NULL, NULL);
	else
	{
		if (is_leaf(*root))
		{
			if ((*root)->two_info == false)
				add_tree_23(root, info, b_node);
			else // quando não tem espaço
			{
				Zwei_drei_tree *new;
				new = break_node(root, info, rise, b_node);
				if (Dad == NULL)
				{
					Zwei_drei_tree *node;
					node = alloc_tree(*rise, *root, new, NULL);
					*root = node;
				}
				else
					b_node = new;
			}
		}
		else
		{ // quando não é folha
			if (strcmp(info.br_word, (*root)->info1.br_word) < 0) 
				b_node = insert_tree_23(*root, &((*root)->left), info, rise);
			else if ((*root)->two_info == false || (strcmp(info.br_word, (*root)->info2.br_word) < 0))
				b_node = insert_tree_23(*root, &((*root)->mid), info, rise);
			else
				b_node = insert_tree_23(*root, &((*root)->right), info, rise);

			if (b_node != NULL)
			{
				if ((*root)->two_info == false)
				{
					add_tree_23(root, *rise, b_node);
					b_node = NULL;
				}
				else // quando não tem espaço
				{
					Info rise1;
					Zwei_drei_tree *new;

					new = break_node(root, *rise, &rise1, b_node);

					if (Dad == NULL)
					{
						Zwei_drei_tree *node;
						node = alloc_tree(rise1, *root, new, NULL);
						*root = node;
						b_node = NULL;
					}
					else
					{
						b_node = new;
						*rise = rise1; // Ela botou isso que nao tinha
					}
				}
			}
		}
	}
	return b_node;
}

int is_info1(Zwei_drei_tree node, char *info)
{
    return strcmp(info, node.info1.br_word) == 0;
}

int is_info2(Zwei_drei_tree node, char *info)
{
    return node.two_info && (strcmp(info, node.info2.br_word) == 0);
}

static int height(Zwei_drei_tree *node)
{
    int h = -1;

    if(node != NULL)
        h = 1 + height(node->left);

    return h;
}

static int is_removable(Zwei_drei_tree *root)
{
    int possible = 0;

    if(root != NULL)
    {
        possible = root->two_info;

        if(!possible)
        {
            possible = is_removable(root->mid);

            if(!possible)
                possible = is_removable(root->left);
        }
    }

    return possible;
}


static Zwei_drei_tree *join_node(Zwei_drei_tree *child1, Info info, Zwei_drei_tree *bigger_node, Zwei_drei_tree **root)
{
    add_tree_23(&child1, info, bigger_node);

    if((*root)->two_info)
        (*root)->two_info = false;
    else
        deallocate_tree2(root);

    return child1;
}

Info bigger_info_node(Zwei_drei_tree *root)
{
    return root->two_info ? root->info2 : root->info1;
}

Zwei_drei_tree *search_23(Zwei_drei_tree *root, char *info)
{
    Zwei_drei_tree *node;
    node = NULL;

    if(root != NULL)
    {
        if(is_info1(*root, info) || is_info2(*root, info))
            node = root;
        else if(strcmp(info, root->info1.br_word) < 0)
            node = search_23(root->left, info);
        else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
            node = search_23(root->mid, info);
        else
            node = search_23(root->right, info);
    }

    return node;
}

Zwei_drei_tree *search_23_lower_child(Zwei_drei_tree *root, Zwei_drei_tree **dad)
{
    Zwei_drei_tree *child;
    child = root;

    while(!is_leaf(child))
    {
        *dad = child;
        child = child->left;
    }

    return child;
}

Zwei_drei_tree *search_23_bigger_child(Zwei_drei_tree *root, Zwei_drei_tree **dad, Info *bigger_value)
{
    Zwei_drei_tree *child;
    child = root;

    while(!is_leaf(child))
    {
        *dad = child;
        if(child->two_info == false)
            child = child->mid;
        else
            child = child->right;
    }

    if(child != NULL)
        *bigger_value = bigger_info_node(child);

    return child;
}

Zwei_drei_tree *search_23_dad(Zwei_drei_tree *root, char *info)
{
    Zwei_drei_tree *dad;
    dad = NULL;

    if(root != NULL)
    {
        if(!is_info1(*root, info) && !is_info2(*root, info))
        {
            if(strcmp(info, root->info1.br_word) < 0)
                dad = search_23_dad(root->left, info);
            else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
                dad = search_23_dad(root->mid, info);
            else
                dad = search_23_dad(root->right, info);

            if(dad == NULL)
                dad = root;
        }
    }

    return dad;
}

Zwei_drei_tree *search_23_bigger_dad(Zwei_drei_tree *root, char *info)
{
    Zwei_drei_tree *dad;
    dad = NULL;

    if(root != NULL)
    {
        if(!is_info1(*root, info) && !is_info2(*root, info))
        {
            if(strcmp(info, root->info1.br_word) < 0)
                dad = search_23_bigger_dad(root->left, info);
            else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
                dad = search_23_bigger_dad(root->mid, info);
            else
                dad = search_23_bigger_dad(root->right, info);

            if(dad == NULL &&
            ((root->two_info == false && (strcmp(root->info1.br_word, info) > 0)) || (root->two_info && (strcmp(root->info2.br_word, info) > 0))))
                dad = root;
        }
    }

    return dad;
}

Zwei_drei_tree *search_23_small_dad(Zwei_drei_tree *root, char *info)
{
    Zwei_drei_tree *dad;
    dad = NULL;

    if(root != NULL)
    {
        if(!is_info1(*root, info) && !is_info2(*root, info))
        {
            if(strcmp(info, root->info1.br_word) < 0)
                dad = search_23_small_dad(root->left, info);
            else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
                dad = search_23_small_dad(root->mid, info);
            else
                dad = search_23_small_dad(root->right, info);

            if(dad == NULL && (strcmp(root->info1.br_word, info) < 0))
                dad = root;
        }
    }

    return dad;
}

static Zwei_drei_tree *search_23_small_dad_info2(Zwei_drei_tree *root, char *info)
{
    Zwei_drei_tree *dad;
    dad = NULL;

    if(root != NULL)
    {
        if(!is_info1(*root, info) && !is_info2(*root, info))
        {
            if(strcmp(info, root->info1.br_word) < 0)
                dad = search_23_small_dad_info2(root->left, info);
            else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
                dad = search_23_small_dad_info2(root->mid, info);
            else
                dad = search_23_small_dad_info2(root->right, info);

            if(dad == NULL && root->two_info && (strcmp(root->info2.br_word, info) < 0))
                dad = root;
        }
    }

    return dad;
}

static int wave(Info saindo, Info *input, Zwei_drei_tree *dad, Zwei_drei_tree **source, Zwei_drei_tree **root, Zwei_drei_tree **bigger_node, int (*remove_func)(Zwei_drei_tree **, char *, Zwei_drei_tree *, Zwei_drei_tree **, Zwei_drei_tree **))
{
    int removed = remove_func(root, saindo.br_word, dad, source, bigger_node);
    *input = saindo;
    return removed;
}


static int remove_internal_node1(Zwei_drei_tree **source, Zwei_drei_tree* root, Info *info, Zwei_drei_tree *child1, Zwei_drei_tree *child2, Zwei_drei_tree **bigger_node)
{
    int removed;
    Zwei_drei_tree *child, *dad;
    Info info_filho;

    dad = root;

    child = search_23_bigger_child(child1, &dad, &info_filho);

    if(child->two_info)
    {
        *info = info_filho;
        child->two_info = false;
    }
    else
    {
        child = search_23_lower_child(child2, &dad);
        removed = wave(child->info1, info, dad, source, &child, bigger_node, remove_wave1);
    }

    return removed;
}

static int remove_internal_node2(Zwei_drei_tree **source, Zwei_drei_tree* root, Info *info, Zwei_drei_tree *child1, Zwei_drei_tree *child2, Zwei_drei_tree **bigger_node)
{
    int removed;
    Zwei_drei_tree *child, *dad;
    Info info_child;

    dad = root;

    child = search_23_lower_child(child1, &dad);

    if(child->two_info)
    {
        *info = child->info1;
        child->info1 = child->info2;
        child->two_info = false;
    }
    else
    {
        child = search_23_bigger_child(child2, &dad, &info_child);
        removed = wave(info_child, info, dad, source, &child, bigger_node, remove_wave2);
    }

    return removed;
}

int remove_wave1(Zwei_drei_tree **root, char *info, Zwei_drei_tree *dad, Zwei_drei_tree **source, Zwei_drei_tree **bigger_node)
{
    int removed = 0;

    if(*root != NULL)
    {
        int info1 = is_info1(**root, info);
        int info2 = is_info2(**root, info);

        if(info1 || info2)
        {
            removed = 1;
            if(is_leaf(*root))
            {
                if((*root)->two_info)
                {
                    if(info1)
                        (*root)->info1 = (*root)->info2;

                    (*root)->two_info = false;
                }
                else
                {
                    if(dad == NULL)
                        deallocate_tree2(root);
                    else
                    {
                        Zwei_drei_tree *dad_aux;
                        Info info_dad;
                        if(*root == dad->left || (dad->two_info && *root == dad->mid))
                        {
                            dad_aux = search_23_dad(*source, dad->info1.br_word);
                            
                            if(*root == dad->left)
                                info_dad = dad->info1;
                            else 
                                info_dad = dad->info2;

                            removed = wave(info_dad, &((*root)->info1), dad_aux, source, &dad, bigger_node, remove_wave1);
                        }
                        else // Filho do mid (com dad de 1 info) ou da direita
                        {
                            dad_aux = search_23_bigger_dad(*source, (*root)->info1.br_word);

                            Zwei_drei_tree *minor_dad;
                            minor_dad = search_23_small_dad_info2(*source, (*root)->info1.br_word);


                            if(dad_aux != NULL)
                            {
                                if(strcmp(dad_aux->info1.br_word, (*root)->info1.br_word) > 0)
                                    info_dad = dad_aux->info1;
                                else
                                    info_dad = dad_aux->info2;
                            }

                            int minor_dad_height = height(minor_dad);
                            int dad_aux_height = height(dad_aux);

                 
                            if(dad_aux == NULL || (dad_aux != dad && minor_dad != NULL && minor_dad_height <= dad_aux_height && (strcmp(info_dad.br_word, minor_dad->info2.br_word) > 0)))
                            {
                                *bigger_node = dad;
                                (*root)->two_info = false;
                                removed = -1;
                            }
                            else
                            {

                                Zwei_drei_tree *gradpa;
                                gradpa = search_23_dad(*source, info_dad.br_word);
                                removed = wave(info_dad, &((*root)->info1), gradpa, source, &dad_aux, bigger_node, remove_wave1);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removed = remove_internal_node1(source, *root, &((*root)->info2), (*root)->mid, (*root)->right, bigger_node);
            else if(info1)
                removed = remove_internal_node1(source, *root, &((*root)->info1), (*root)->left, (*root)->mid, bigger_node);
        }
        else
        {
            if(strcmp(info, (*root)->info1.br_word) < 0)
                removed = remove_wave1(&(*root)->left, info, *root, source, bigger_node);
            else if((*root)->two_info == false || (strcmp(info, (*root)->info2.br_word) < 0))
                removed = remove_wave1(&(*root)->mid, info, *root, source, bigger_node);
            else
                removed = remove_wave1(&(*root)->right, info, *root, source, bigger_node);
        }
    }
    return removed;
}

int remove_wave2(Zwei_drei_tree **root, char *info, Zwei_drei_tree *dad, Zwei_drei_tree **source, Zwei_drei_tree **bigger_node)
{
    int removed = 0;

    if(*root != NULL)
    {
        int info1 = is_info1(**root, info);
        int info2 = is_info2(**root, info);

        if(info1 || info2)
        {
            removed = 1;
            if(is_leaf(*root))
            {
                if((*root)->two_info)
                {
                    if(info1)
                        (*root)->info1 = (*root)->info2;

                    (*root)->two_info = false;
                }
                else
                {
                    if(dad == NULL)
                        deallocate_tree2(root);
                    else
                    {
                        Zwei_drei_tree *dad_aux;
                        Info info_dad;
                        if(*root == dad->mid || (dad->two_info && *root == dad->right))
                        {
                            dad_aux = search_23_dad(*source, dad->info1.br_word);
                            
                            if(*root == dad->mid)
                                info_dad = dad->info1;
                            else 
                                info_dad = dad->info2;

                            removed = wave(info_dad, &((*root)->info1), dad_aux, source, &dad, bigger_node, remove_wave2);
                        }
                        else // Filho da esquerda
                        {
                            dad_aux = search_23_small_dad(*source, (*root)->info1.br_word);

                            Zwei_drei_tree *minor_dad;
                            minor_dad = search_23_small_dad_info2(*source, (*root)->info1.br_word);

                            Zwei_drei_tree *gradpa;
                            if(dad_aux == NULL || (dad_aux != dad && minor_dad != NULL))
                            {  
                                removed = -1;
                                *bigger_node = dad;
                            }
                            else
                            {
                                if(dad_aux->two_info && (strcmp(dad_aux->info2.br_word, (*root)->info1.br_word) < 0))
                                    info_dad = dad_aux->info2;
                                else
                                    info_dad = dad_aux->info1;

                                gradpa = search_23_dad(*source, info_dad.br_word);
                                removed = wave(info_dad, &((*root)->info1), gradpa, source, &dad_aux, bigger_node, remove_wave2);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removed = remove_internal_node2(source, *root, &((*root)->info2), (*root)->right, (*root)->mid, bigger_node);
            else if(info1)
                removed = remove_internal_node2(source, *root, &((*root)->info1), (*root)->mid, (*root)->left, bigger_node);
        }
        else
        {
            if(strcmp(info, (*root)->info1.br_word) < 0)
                removed = remove_wave2(&(*root)->left, info, *root, source, bigger_node);
            else if((*root)->two_info == false || (strcmp(info, (*root)->info2.br_word) < 0))
                removed = remove_wave2(&(*root)->mid, info, *root, source, bigger_node);
            else
                removed = remove_wave2(&(*root)->right, info, *root, source, bigger_node);
        }
    }
    return removed;
}

int remove_23(Zwei_drei_tree **root, char *info)
{   
    Zwei_drei_tree *bigger_node, *join_pos;
    int removed = remove_wave1(root, info, NULL, root, &join_pos);

    if(removed == -1)
    {
        removed = 1;
        Info join_value = bigger_info_node(join_pos);
        bigger_node = NULL;
        int removed_aux = rebalance_23(root, join_value.br_word, &bigger_node);
        
        if(removed_aux == -1)
        {
            Zwei_drei_tree *dad, *join_pos2;
            Info *input;
            dad = search_23_dad(*root, join_value.br_word);

            if(is_info1(*join_pos, join_value.br_word))
                input = &(join_pos->mid->info1);
            else
                input = &(join_pos->right->info1);

            removed_aux = wave(join_value, input, dad, root, &join_pos, &join_pos2, remove_wave2);

            if(removed_aux == -1)
            {
                join_value = join_pos2->info1;
                dad = search_23_dad(*root, join_value.br_word);
                removed_aux = wave(join_value, &(join_pos2->left->info1), dad, root, &join_pos2, &join_pos, remove_wave1);

                join_value = bigger_info_node(join_pos);
                bigger_node = NULL;
                removed_aux = rebalance_23(root, join_value.br_word, &bigger_node);
            }
        }

        if(*root == NULL)
            *root = bigger_node;
    }

    return removed;
}

static int balance_23(Zwei_drei_tree **root, Zwei_drei_tree *child1, Zwei_drei_tree **child2, Info info, Zwei_drei_tree **bigger_node)
{
    int balanced = 0;
    if(*child2 == NULL || !(*child2)->two_info)
    {
        if(*child2 != NULL)
            deallocate_tree2(child2);

        *bigger_node = join_node(child1, info, *bigger_node, root);
        balanced = 1;
    }
    return balanced;
}

int rebalance_23(Zwei_drei_tree **root, char *info, Zwei_drei_tree **bigger_node)
{
    int balanced = 0;
    if(*root != NULL)
    {
        if(!is_leaf(*root))
        {
            if(strcmp(info, (*root)->info1.br_word) < 0)
                balanced = rebalance_23(&((*root)->left), info, bigger_node);
            else if((*root)->two_info == false || (strcmp(info, (*root)->info2.br_word) < 0))
            {
                if((*root)->left->two_info && !is_removable((*root)->mid))
                    balanced = -1;
                else
                    balanced = rebalance_23(&((*root)->mid), info, bigger_node);
            }
            else
            {
                if((*root)->mid->two_info && !is_removable((*root)->right))
                    balanced = -1;
                else
                    balanced = rebalance_23(&((*root)->right), info, bigger_node);
            }

            if(balanced != -1)
            {
                if((*root)->two_info == false)
                    balanced = balance_23(root, (*root)->left, &((*root)->mid), (*root)->info1, bigger_node);
                else if((*root)->two_info)
                    balanced = balance_23(root, (*root)->mid, &((*root)->right), (*root)->info2, bigger_node);
            }
            
        }
    }

    return balanced;
}


// Função para imprimir a árvore (apenas para verificação)
void print_tree(Zwei_drei_tree *root, int level) 
{
    if (root != NULL) 
	{
		for (int i = 0; i < level; i++) 
			printf("  ");
		printf("%d - %s", level, root->info1.br_word);
		if (root->two_info) 
			printf(", %s", root->info2.br_word);
		printf("\n");

		if (root->left) 
			print_tree(root->left, level + 1);
		if (root->mid) 
			print_tree(root->mid, level + 1);
		if (root->right) 
			print_tree(root->right, level + 1);
	}
}

void print_bin_tree(Zwei_drei_tree *root, int level) 
{
    if (root != NULL) 
	{
		for (int i = 0; i < level; i++) 
			printf("  ");
		print_binary_tree(root->info1.eng_words, level);
		if (root->two_info) 
			print_binary_tree(root->info2.eng_words, level);
		printf("\n");

		if (root->left) 
			print_bin_tree(root->left, level + 1);
		if (root->mid) 
			print_bin_tree(root->mid, level + 1);
		if (root->right) 
			print_bin_tree(root->right, level + 1);
	}
}

Zwei_drei_tree *search_23_tree(Zwei_drei_tree *root, const char *br_word) 
{
	Zwei_drei_tree *result;
	result = NULL;


    if (root != NULL) 
	{
		// Verifica o primeiro item (info1)
		if (strcmp(br_word, root->info1.br_word) == 0) 
			result = root;
		// Verifica o segundo item (info2), se existir
		else if (root->two_info && strcmp(br_word, root->info2.br_word) == 0) 
			result = root;
		else
		{
			if (strcmp(br_word, root->info1.br_word) < 0) 
				result = search_23_tree(root->left, br_word);  
			else if (!root->two_info || strcmp(br_word, root->info2.br_word) < 0) 
				result = search_23_tree(root->mid, br_word);  
			else 
				result = search_23_tree(root->right, br_word); 
		}

	}
    
	return result;

}


void show_port_and_eng_words(Zwei_drei_tree *root, int unit)
{
	if(root)
	{
		if (root->info1.unit == unit)
		{
			printf("PORTUGUES: %s\n", root->info1.br_word);
			printf("  Traduções em inglês:");
            show_all_eng_words(root->info1.eng_words);
            printf("\n");
		}

		if (root->two_info && root->info2.unit == unit)
		{
			printf("PORTUGUES: %s\n", root->info2.br_word);
			printf("  Traduções em inglês:");
            show_all_eng_words(root->info2.eng_words);
            printf("\n");
		}
	
		show_port_and_eng_words(root->left, unit);
		show_port_and_eng_words(root->mid, unit);
		show_port_and_eng_words(root->right, unit);
	}
}

void show_eng_words(Zwei_drei_tree *root, const char *br_word) 
{
    if (root) 
	{
        // Normaliza as strings antes da comparação
        char normalized_br_word[256];
        strcpy(normalized_br_word, br_word);
        trim_string(normalized_br_word);

        if (strcmp(normalized_br_word, root->info1.br_word) == 0) 
		{
            show_all_eng_words(root->info1.eng_words);
            printf("\n");
        }
        if (root->two_info && strcmp(normalized_br_word, root->info2.br_word) == 0) 
		{
            show_all_eng_words(root->info2.eng_words);
            printf("\n");
        }

        show_eng_words(root->left, br_word);
        show_eng_words(root->mid, br_word);
        show_eng_words(root->right, br_word);
    }
}


void remove_eng_word(Zwei_drei_tree **root, Info_bin info_bin) 
{
    if (*root)
	{
		bool removed = false;

		removed = remove_eng_word_bin(&(*root)->info1.eng_words, info_bin);

		if (removed && is_binary_tree_empty((*root)->info1.eng_words)) 
			remove_23(root, (*root)->info1.br_word);

		if (!removed && (*root)->two_info) 
		{
			removed = remove_eng_word_bin(&(*root)->info2.eng_words, info_bin);

			if (removed && is_binary_tree_empty((*root)->info2.eng_words)) 
				remove_23(root, (*root)->info2.br_word);
		}

		remove_eng_word(&(*root)->left, info_bin);
		remove_eng_word(&(*root)->mid, info_bin);
		remove_eng_word(&(*root)->right, info_bin);
	}
}

void remove_all_eng_words(Zwei_drei_tree **root, Binary_tree *eng_words)
{
	if(eng_words)
	{
		remove_all_eng_words(root, eng_words->left);
		remove_all_eng_words(root, eng_words->right);

		remove_eng_word(root, eng_words->info);
	}
}

void remove_port_word(Zwei_drei_tree **root, Info info) 
{
    if (*root)
    {
        if (strcmp(info.br_word, (*root)->info1.br_word) < 0) 
            remove_port_word(&(*root)->left, info);
        else if ((*root)->two_info && strcmp(info.br_word, (*root)->info1.br_word) > 0 && strcmp(info.br_word, (*root)->info2.br_word) < 0) 
            remove_port_word(&(*root)->mid, info);
        else if ((*root)->two_info && strcmp(info.br_word, (*root)->info2.br_word) > 0) 
            remove_port_word(&(*root)->right, info);
        else 
        {
            if (strcmp(info.br_word, (*root)->info1.br_word) == 0) 
            {
                if (remove_eng_word_bin_unit(&(*root)->info1.eng_words, (Info_bin){.eng_word = "", .unit = info.unit}) && is_binary_tree_empty((*root)->info1.eng_words)) 
                    remove_23(root, info.br_word);
            }
            else if ((*root)->two_info && strcmp(info.br_word, (*root)->info2.br_word) == 0) 
            {
                if (remove_eng_word_bin_unit(&(*root)->info2.eng_words, (Info_bin){.eng_word = "", .unit = info.unit}) && is_binary_tree_empty((*root)->info2.eng_words)) 
                    remove_23(root, info.br_word);
            }
        }
    }
}


