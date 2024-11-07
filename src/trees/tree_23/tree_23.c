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

int is_leaf(Zwei_drei_tree *root)
{
	int leaf = false; // não é folha

	if (root->left == NULL && root->mid == NULL && root->right == NULL)
		leaf = true;

	return leaf;
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

int remover23(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Info info)
{
	int removeu = 0;
	Zwei_drei_tree *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
	aux = (Zwei_drei_tree **)malloc(sizeof(Zwei_drei_tree *));
	no1 = (Zwei_drei_tree *)malloc(sizeof(Zwei_drei_tree));

	if (*root != NULL)
	{
		if (is_leaf(*root) == 1)
		{
			if ((*root)->two_info)
			{
				if (strcmp(info.br_word, (*root)->info2.br_word) == 0)
				{ // quando é folha, tem duas informações e o numero ta na segunda posição
					// (*root)->info2 = 0;
					(*root)->two_info = false;
					removeu = 1;
				}
				else if (info == (*root)->info1)
				{ // quando é folha, tem duas informações e o numero ta na primeira posição do nó
					(*root)->info1 = (*root)->info2;
					(*root)->info2 = 0;
					(*root)->NInfos = 1;
					removeu = 1;
				}
			}
			else if (info == (*root)->info1)
			{
				if (*Dad == NULL)
				{
					free(*root);
					*root = NULL;
					removeu = 1;
				}
				else if (*root == (*Dad)->left)
				{
					(*root)->info1 = (*Dad)->info1;
					paiNo = *Dad;
					menorInfoDir((*Dad)->mid, &no, &paiNo);
					(*Dad)->info1 = no->info1;
					removeu = 1;

					if (no->NInfos == 2)
					{
						no->info1 = no->info2;
						no->info2 = 0;
						no->NInfos = 1;
					}
					else
					{
						if (paiNo->NInfos == 1)
						{
							(*root)->info2 = no->info1;
							(*root)->NInfos = 2;
							free(no);
							*Dad = *root;
						}
						else
						{
							no->info1 = paiNo->info2;
							paiNo1 = paiNo;
							menorInfoDir(paiNo->right, &no1, &paiNo1);
							paiNo->info2 = no1->info1;

							if (no1->NInfos == 2)
							{
								no1->info1 = no1->info2;
								no1->info2 = 0;
								no1->NInfos = 1;
							}
							else
							{
								no->info2 = paiNo->info2;
								no->NInfos = 2;
								paiNo->info2 = 0;
								paiNo->NInfos = 1;
								free(no1);
								paiNo1->right = NULL;
							}
						}
					}
				}
				else if (*root == (*Dad)->mid)
				{
					removeu = 1;
					if ((*Dad)->NInfos == 1)
					{
						if (((*Dad)->left)->NInfos == 2)
						{
							(*root)->info1 = (*Dad)->info1;
							(*Dad)->info1 = ((*Dad)->left)->info2;
							((*Dad)->left)->info2 = 0;
							((*Dad)->left)->NInfos = 1;
						}
						else
						{
							((*Dad)->left)->info2 = (*Dad)->info1;
							free(*root);
							((*Dad)->left)->NInfos = 2;
							*aux = (*Dad)->left;
							free(*Dad);
							*Dad = *aux;
						}
					}
					else
					{
						(*root)->info1 = (*Dad)->info2;
						paiNo = *Dad;
						menorInfoDir((*Dad)->right, &no, &paiNo);
						(*Dad)->info2 = no->info1;

						if (no->NInfos == 2)
						{
							no->info1 = no->info2;
							no->info2 = 0;
							no->NInfos = 1;
						}
						else
						{
							(*root)->NInfos = 2;
							(*root)->info2 = (*Dad)->info2;
							(*Dad)->info2 = 0;
							(*Dad)->NInfos = 1;
							free(no);
							(*Dad)->right = NULL;
						}
					}
				}
				else
				{
					removeu = 1;
					paiNo = *Dad;
					maiorInfoEsq((*Dad)->mid, &no, &paiNo);

					if (no->NInfos == 1)
					{
						no->info2 = (*Dad)->info2;
						(*Dad)->info2 = 0;
						(*Dad)->NInfos = 1;
						no->NInfos = 2;
						free(*root);
						*root = NULL;
					}
					else
					{
						(*root)->info1 = (*Dad)->info2;
						(*Dad)->info2 = no->info2;
						no->info2 = 0;
						no->NInfos = 1;
					}
				}
			}
		}
		else
		{ // se nao é folha
			if (info < (*root)->info1)
				removeu = remover23(root, &(*root)->left, info);
			else if (info == (*root)->info1)
			{
				paiNo = *root;
				menorInfoDir((*root)->mid, &no, &paiNo);
				(*root)->info1 = no->info1;
				remover23(root, &(*root)->mid, (*root)->info1);
				removeu = 1;
			}
			else if (((*root)->NInfos == 1) || (info < (*root)->info2))
			{
				removeu = remover23(root, &(*root)->mid, info);
			}
			else if (info == (*root)->info2)
			{
				paiNo = *Dad;
				menorInfoDir((*Dad)->right, &no, &paiNo);
				(*root)->info2 = no->info1;
				remover23(root, &(*root)->right, (*root)->info2);
				removeu = 1;
			}
			else
			{
				removeu = remover23(root, &(*root)->right, info);
			}
		}
	}
	return removeu;
}
