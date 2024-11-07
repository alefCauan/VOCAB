#include "tree_23.h"

Zwei_drei_tree *alloc_tree(Info info, Zwei_drei_tree *left, Zwei_drei_tree *mid, Zwei_drei_tree *right)
{
	Zwei_drei_tree *node;

	node = (Zwei_drei_tree *)malloc(sizeof(Zwei_drei_tree));

	(*node).info1 = info;
	
	(*node).two_info = false;
	(*node).left = left;
	(*node).mid = mid;
	(*node).right = right;

	return node;
}

bool is_leaf(Zwei_drei_tree *root)
{
	int leaf = false; // não é folha

	if (root->left == NULL && root->mid == NULL && root->right == NULL)
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
	Zwei_drei_tree *new;

	if (strcmp(info.br_word, (*root)->info1.br_word) < 0) // TODO: verificar
	{
		*rise = (*root)->info1;
		new = alloc_tree((*root)->info2, (*root)->mid, (*root)->right, NULL);
		(*root)->info1 = info;
		(*root)->mid = b_node;
	}
	if (strcmp(info.br_word, (*root)->info1.br_word) > 0) // TODO: verificar
	{
		*rise = info;
		new = alloc_tree((*root)->info2, b_node, (*root)->right, NULL);
	}
	else
	{
		*rise = (*root)->info2;
		new = alloc_tree(info, (*root)->right, b_node, NULL);
	}
	// (*root)->info2 = 0; TODO:  eliminar info2
	(*root)->two_info = false;
	(*root)->right = NULL;

	return (new);
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
				Zwei_drei_tree *novo;
				novo = break_node(root, info, rise, b_node);
				if (Dad == NULL)
				{
					Zwei_drei_tree *no;
					no = alloc_tree(*rise, *root, novo, NULL);
					*root = no;
				}
				else
					b_node = novo;
			}
		}
		else
		{ // quando não é folha
			if (strcmp(info.br_word, (*root)->info1.br_word) < 0) // TODO: verificar
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
					Zwei_drei_tree *novo;
					novo = break_node(root, *rise, &rise1, b_node);
					if (Dad == NULL)
					{
						Zwei_drei_tree *no;
						no = alloc_tree(rise1, *root, novo, NULL);
						*root = no;
						b_node = NULL;
					}
					else
					{
						b_node = novo;
						*rise = rise1; // Ela botou isso que nao tinha
					}
				}
			}
		}
	}
	return b_node;
}

int remove_23(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Info info)
{
	int remove = 0;
	Zwei_drei_tree *no = NULL, *node1, *dad_node = NULL, *dad_node1 = NULL, **aux;
	aux = (Zwei_drei_tree **)malloc(sizeof(Zwei_drei_tree *));
	node1 = (Zwei_drei_tree *)malloc(sizeof(Zwei_drei_tree));

	if (*root != NULL)
	{
		if (is_leaf(*root) == true)
		{
			if ((*root)->two_info)
			{
				if (strcmp(info.br_word, (*root)->info2.br_word) == 0)
				{ // quando é folha, tem duas informações e o numero ta na segunda posição
					// (*root)->info2 = 0;
					(*root)->two_info = false;
					remove = 1;
				}
				else if (strcmp(info.br_word, (*root)->info1.br_word) == 0)
				{ // quando é folha, tem duas informações e o numero ta na primeira posição do nó
					(*root)->info1 = (*root)->info2;
					// (*root)->info2 = 0; TODO:
					(*root)->two_info = false;
					remove = 1;
				}
			}
			else if (strcmp(info.br_word, (*root)->info1.br_word) == 0)
			{
				if (*Dad == NULL)
				{
					free(*root);
					*root = NULL;
					remove = 1;
				}
				else if (*root == (*Dad)->left)
				{
					(*root)->info1 = (*Dad)->info1;
					dad_node = *Dad;
					lower_info_right((*Dad)->mid, &no, &dad_node);
					(*Dad)->info1 = no->info1;
					remove = 1;

					if (no->two_info)
					{
						no->info1 = no->info2;
						// no->info2 = 0; TODO: 
						no->two_info = false;
					}
					else
					{
						if (dad_node->two_info == false)
						{
							(*root)->info2 = no->info1;
							(*root)->two_info = true;
							free(no);
							*Dad = *root;
						}
						else
						{
							no->info1 = dad_node->info2;
							dad_node1 = dad_node;
							lower_info_right(dad_node->right, &node1, &dad_node1);
							dad_node->info2 = node1->info1;

							if (node1->two_info)
							{
								node1->info1 = node1->info2;
								// node1->info2 = 0; TODO: 
								node1->two_info = false;
							}
							else
							{
								no->info2 = dad_node->info2;
								no->two_info = true;
								// dad_node->info2 = 0; TODO:
								dad_node->two_info = 1;
								free(node1);
								dad_node1->right = NULL;
							}
						}
					}
				}
				else if (*root == (*Dad)->mid)
				{
					remove = 1;
					if ((*Dad)->two_info == false)
					{
						if (((*Dad)->left)->two_info)
						{
							(*root)->info1 = (*Dad)->info1;
							(*Dad)->info1 = ((*Dad)->left)->info2;
							// ((*Dad)->left)->info2 = 0; TODO: 
							((*Dad)->left)->two_info = false;
						}
						else
						{
							((*Dad)->left)->info2 = (*Dad)->info1;
							free(*root);
							((*Dad)->left)->two_info = true;
							*aux = (*Dad)->left;
							free(*Dad);
							*Dad = *aux;
						}
					}
					else
					{
						(*root)->info1 = (*Dad)->info2;
						dad_node = *Dad;
						lower_info_right((*Dad)->right, &no, &dad_node);
						(*Dad)->info2 = no->info1;

						if (no->two_info)
						{
							no->info1 = no->info2;
							// no->info2 = 0; TODO
							no->two_info = false;
						}
						else
						{
							(*root)->two_info = true;
							(*root)->info2 = (*Dad)->info2;
							// (*Dad)->info2 = 0; TODO: 
							(*Dad)->two_info = false;
							free(no);
							(*Dad)->right = NULL;
						}
					}
				}
				else
				{
					remove = 1;
					dad_node = *Dad;
					lower_info_left((*Dad)->mid, &no, &dad_node);

					if (no->two_info == false)
					{
						no->info2 = (*Dad)->info2;
						// (*Dad)->info2 = 0;TODO: 
						(*Dad)->two_info = false;
						no->two_info = true;
						free(*root);
						*root = NULL;
					}
					else
					{
						(*root)->info1 = (*Dad)->info2;
						(*Dad)->info2 = no->info2;
						// no->info2 = 0; TODO
						no->two_info = false;
					}
				}
			}
		}
		else
		{ // se nao é folha
			if (strcmp(info.br_word, (*root)->info1.br_word) < 0)
				remove = remove_23(root, &(*root)->left, info);
			else if (strcmp(info.br_word, (*root)->info1.br_word) == 0)
			{
				dad_node = *root;
				lower_info_right((*root)->mid, &no, &dad_node);
				(*root)->info1 = no->info1;
				remove_23(root, &(*root)->mid, (*root)->info1);
				remove = 1;
			}
			else if (((*root)->two_info == false) || (strcmp(info.br_word, (*root)->info2.br_word) < 0))
			{
				remove = remove_23(root, &(*root)->mid, info);
			}
			else if (strcmp(info.br_word, (*root)->info2.br_word) == 0)
			{
				dad_node = *Dad;
				lower_info_right((*Dad)->right, &no, &dad_node);
				(*root)->info2 = no->info1;
				remove_23(root, &(*root)->right, (*root)->info2);
				remove = 1;
			}
			else
			{
				remove = remove_23(root, &(*root)->right, info);
			}
		}
	}
	return remove;
}
