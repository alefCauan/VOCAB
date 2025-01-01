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

void deallocate_tree2(Zwei_drei_tree **no)
{
    free(*no);
    *no = NULL;
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
        // Novo valor está no meio, `info` deve subir
        *rise = info;
        new_node = alloc_tree((*root)->info2, b_node, (*root)->right, NULL);
    } 
    else 
	{
        // Novo valor é o maior, `info2` deve subir, `info` vai para o novo nó
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
					Zwei_drei_tree *no;
					no = alloc_tree(*rise, *root, new, NULL);
					*root = no;
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

static int eh_info1(Zwei_drei_tree no, char *info)
{
    return strcmp(info, no.info1.br_word) == 0;
}

static int eh_info2(Zwei_drei_tree no, char *info)
{
    return no.two_info && (strcmp(info, no.info2.br_word) == 0);
}

static int calcular_altura(Zwei_drei_tree *no)
{
    int altura = -1;

    if(no != NULL)
        altura = 1 + calcular_altura(no->left);

    return altura;
}

static int possivel_remover(Zwei_drei_tree *raiz)
{
    int possivel = 0;

    if(raiz != NULL)
    {
        possivel = raiz->two_info;

        if(!possivel)
        {
            possivel = possivel_remover(raiz->mid);

            if(!possivel)
                possivel = possivel_remover(raiz->left);
        }
    }

    return possivel;
}


static Zwei_drei_tree *no23_juntar(Zwei_drei_tree *filho1, Info info, Zwei_drei_tree *maior, Zwei_drei_tree **raiz)
{
    add_tree_23(&filho1, info, maior);

    if((*raiz)->two_info)
        (*raiz)->two_info = false;
    else
        deallocate_tree2(raiz);

    return filho1;
}

Info no23_maior_info(Zwei_drei_tree *raiz)
{
    return raiz->two_info ? raiz->info2 : raiz->info1;
}

Zwei_drei_tree *arvore23_criar()
{
    return NULL;
}

Zwei_drei_tree *arvore23_buscar(Zwei_drei_tree *raiz, char *info)
{
    Zwei_drei_tree *no;
    no = NULL;

    if(raiz != NULL)
    {
        if(eh_info1(*raiz, info) || eh_info2(*raiz, info))
            no = raiz;
        else if(strcmp(info, raiz->info1.br_word) < 0)
            no = arvore23_buscar(raiz->left, info);
        else if(raiz->two_info == false || (strcmp(info, raiz->info2.br_word) < 0))
            no = arvore23_buscar(raiz->mid, info);
        else
            no = arvore23_buscar(raiz->right, info);
    }

    return no;
}

Zwei_drei_tree *arvore23_buscar_menor_filho(Zwei_drei_tree *raiz, Zwei_drei_tree **pai)
{
    Zwei_drei_tree *filho;
    filho = raiz;

    while(!is_leaf(filho))
    {
        *pai = filho;
        filho = filho->left;
    }

    return filho;
}

Zwei_drei_tree *arvore23_buscar_maior_filho(Zwei_drei_tree *raiz, Zwei_drei_tree **pai, Info *maior_valor)
{
    Zwei_drei_tree *filho;
    filho = raiz;

    while(!is_leaf(filho))
    {
        *pai = filho;
        if(filho->two_info == false)
            filho = filho->mid;
        else
            filho = filho->right;
    }

    if(filho != NULL)
        *maior_valor = no23_maior_info(filho);

    return filho;
}

Zwei_drei_tree *arvore23_buscar_pai(Zwei_drei_tree *raiz, char *info)
{
    Zwei_drei_tree *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(strcmp(info, raiz->info1.br_word) < 0)
                pai = arvore23_buscar_pai(raiz->left, info);
            else if(raiz->two_info == false || (strcmp(info, raiz->info2.br_word) < 0))
                pai = arvore23_buscar_pai(raiz->mid, info);
            else
                pai = arvore23_buscar_pai(raiz->right, info);

            if(pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

Zwei_drei_tree *arvore23_buscar_maior_pai(Zwei_drei_tree *raiz, char *info)
{
    Zwei_drei_tree *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(strcmp(info, raiz->info1.br_word) < 0)
                pai = arvore23_buscar_maior_pai(raiz->left, info);
            else if(raiz->two_info == false || (strcmp(info, raiz->info2.br_word) < 0))
                pai = arvore23_buscar_maior_pai(raiz->mid, info);
            else
                pai = arvore23_buscar_maior_pai(raiz->right, info);

            if(pai == NULL &&
            ((raiz->two_info == false && (strcmp(raiz->info1.br_word, info) > 0)) || (raiz->two_info && (strcmp(raiz->info2.br_word, info) > 0))))
                pai = raiz;
        }
    }

    return pai;
}

Zwei_drei_tree *arvore23_buscar_menor_pai(Zwei_drei_tree *raiz, char *info)
{
    Zwei_drei_tree *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(strcmp(info, raiz->info1.br_word) < 0)
                pai = arvore23_buscar_menor_pai(raiz->left, info);
            else if(raiz->two_info == false || (strcmp(info, raiz->info2.br_word) < 0))
                pai = arvore23_buscar_menor_pai(raiz->mid, info);
            else
                pai = arvore23_buscar_menor_pai(raiz->right, info);

            if(pai == NULL && (strcmp(raiz->info1.br_word, info) < 0))
                pai = raiz;
        }
    }

    return pai;
}

static Zwei_drei_tree *arvore23_buscar_menor_pai_2_infos(Zwei_drei_tree *raiz, char *info)
{
    Zwei_drei_tree *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(strcmp(info, raiz->info1.br_word) < 0)
                pai = arvore23_buscar_menor_pai_2_infos(raiz->left, info);
            else if(raiz->two_info == false || (strcmp(info, raiz->info2.br_word) < 0))
                pai = arvore23_buscar_menor_pai_2_infos(raiz->mid, info);
            else
                pai = arvore23_buscar_menor_pai_2_infos(raiz->right, info);

            if(pai == NULL && raiz->two_info && (strcmp(raiz->info2.br_word, info) < 0))
                pai = raiz;
        }
    }

    return pai;
}

static int movimento_onda(Info saindo, Info *entrada, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **raiz, Zwei_drei_tree **maior, int (*funcao_remover)(Zwei_drei_tree **, char *, Zwei_drei_tree *, Zwei_drei_tree **, Zwei_drei_tree **))
{
    int removeu = funcao_remover(raiz, saindo.br_word, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}


static int arvore23_remover_no_interno1(Zwei_drei_tree **origem, Zwei_drei_tree* raiz, Info *info, Zwei_drei_tree *filho1, Zwei_drei_tree *filho2, Zwei_drei_tree **maior)
{
    int removeu;
    Zwei_drei_tree *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = arvore23_buscar_maior_filho(filho1, &pai, &info_filho);

    if(filho->two_info)
    {
        *info = info_filho;
        filho->two_info = false;
    }
    else
    {
        filho = arvore23_buscar_menor_filho(filho2, &pai);
        removeu = movimento_onda(filho->info1, info, pai, origem, &filho, maior, arvore23_remover1);
    }

    return removeu;
}

static int arvore23_remover_no_interno2(Zwei_drei_tree **origem, Zwei_drei_tree* raiz, Info *info, Zwei_drei_tree *filho1, Zwei_drei_tree *filho2, Zwei_drei_tree **maior)
{
    int removeu;
    Zwei_drei_tree *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = arvore23_buscar_menor_filho(filho1, &pai);

    if(filho->two_info)
    {
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->two_info = false;
    }
    else
    {
        filho = arvore23_buscar_maior_filho(filho2, &pai, &info_filho);
        removeu = movimento_onda(info_filho, info, pai, origem, &filho, maior, arvore23_remover2);
    }

    return removeu;
}

int arvore23_remover1(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **maior)
{
    int removeu = 0;

    if(*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(is_leaf(*raiz))
            {
                if((*raiz)->two_info)
                {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->two_info = false;
                }
                else
                {
                    if(pai == NULL)
                        deallocate_tree2(raiz);
                    else
                    {
                        Zwei_drei_tree *pai_aux;
                        Info info_pai;
                        if(*raiz == pai->left || (pai->two_info && *raiz == pai->mid))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.br_word);
                            
                            if(*raiz == pai->left)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover1);
                        }
                        else // Filho do mid (com pai de 1 info) ou da direita
                        {
                            pai_aux = arvore23_buscar_maior_pai(*origem, (*raiz)->info1.br_word);

                            Zwei_drei_tree *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.br_word);


                            if(pai_aux != NULL)
                            {
                                if(strcmp(pai_aux->info1.br_word, (*raiz)->info1.br_word) > 0)
                                    info_pai = pai_aux->info1;
                                else
                                    info_pai = pai_aux->info2;
                            }

                            int altura_menor_pai = calcular_altura(menor_pai);
                            int altura_pai_aux = calcular_altura(pai_aux);

                 
                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL && altura_menor_pai <= altura_pai_aux && (strcmp(info_pai.br_word, menor_pai->info2.br_word) > 0)))
                            {
                                *maior = pai;
                                (*raiz)->two_info = false;
                                removeu = -1;
                            }
                            else
                            {

                                Zwei_drei_tree *avo;
                                avo = arvore23_buscar_pai(*origem, info_pai.br_word);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover1);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = arvore23_remover_no_interno1(origem, *raiz, &((*raiz)->info2), (*raiz)->mid, (*raiz)->right, maior);
            else if(info1)
                removeu = arvore23_remover_no_interno1(origem, *raiz, &((*raiz)->info1), (*raiz)->left, (*raiz)->mid, maior);
        }
        else
        {
            if(strcmp(info, (*raiz)->info1.br_word) < 0)
                removeu = arvore23_remover1(&(*raiz)->left, info, *raiz, origem, maior);
            else if((*raiz)->two_info == false || (strcmp(info, (*raiz)->info2.br_word) < 0))
                removeu = arvore23_remover1(&(*raiz)->mid, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover1(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int arvore23_remover2(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree *pai, Zwei_drei_tree **origem, Zwei_drei_tree **maior)
{
    int removeu = 0;

    if(*raiz != NULL)
    {
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(is_leaf(*raiz))
            {
                if((*raiz)->two_info)
                {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->two_info = false;
                }
                else
                {
                    if(pai == NULL)
                        deallocate_tree2(raiz);
                    else
                    {
                        Zwei_drei_tree *pai_aux;
                        Info info_pai;
                        if(*raiz == pai->mid || (pai->two_info && *raiz == pai->right))
                        {
                            pai_aux = arvore23_buscar_pai(*origem, pai->info1.br_word);
                            
                            if(*raiz == pai->mid)
                                info_pai = pai->info1;
                            else 
                                info_pai = pai->info2;

                            removeu = movimento_onda(info_pai, &((*raiz)->info1), pai_aux, origem, &pai, maior, arvore23_remover2);
                        }
                        else // Filho da esquerda
                        {
                            pai_aux = arvore23_buscar_menor_pai(*origem, (*raiz)->info1.br_word);

                            Zwei_drei_tree *menor_pai;
                            menor_pai = arvore23_buscar_menor_pai_2_infos(*origem, (*raiz)->info1.br_word);

                            Zwei_drei_tree *avo;
                            if(pai_aux == NULL || (pai_aux != pai && menor_pai != NULL))
                            {  
                                removeu = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if(pai_aux->two_info && (strcmp(pai_aux->info2.br_word, (*raiz)->info1.br_word) < 0))
                                    info_pai = pai_aux->info2;
                                else
                                    info_pai = pai_aux->info1;

                                avo = arvore23_buscar_pai(*origem, info_pai.br_word);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, &pai_aux, maior, arvore23_remover2);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = arvore23_remover_no_interno2(origem, *raiz, &((*raiz)->info2), (*raiz)->right, (*raiz)->mid, maior);
            else if(info1)
                removeu = arvore23_remover_no_interno2(origem, *raiz, &((*raiz)->info1), (*raiz)->mid, (*raiz)->left, maior);
        }
        else
        {
            if(strcmp(info, (*raiz)->info1.br_word) < 0)
                removeu = arvore23_remover2(&(*raiz)->left, info, *raiz, origem, maior);
            else if((*raiz)->two_info == false || (strcmp(info, (*raiz)->info2.br_word) < 0))
                removeu = arvore23_remover2(&(*raiz)->mid, info, *raiz, origem, maior);
            else
                removeu = arvore23_remover2(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return removeu;
}

int remove_23(Zwei_drei_tree **raiz, char *info)
{   
    Zwei_drei_tree *maior, *posicao_juncao;
    int removeu = arvore23_remover1(raiz, info, NULL, raiz, &posicao_juncao);

    if(removeu == -1)
    {
        removeu = 1;
        Info valor_juncao = no23_maior_info(posicao_juncao);
        maior = NULL;
        int removeu_aux = arvore23_rebalancear(raiz, valor_juncao.br_word, &maior);
        
        if(removeu_aux == -1)
        {
            Zwei_drei_tree *pai, *posicao_juncao2;
            Info *entrada;
            pai = arvore23_buscar_pai(*raiz, valor_juncao.br_word);

            if(eh_info1(*posicao_juncao, valor_juncao.br_word))
                entrada = &(posicao_juncao->mid->info1);
            else
                entrada = &(posicao_juncao->right->info1);

            removeu_aux = movimento_onda(valor_juncao, entrada, pai, raiz, &posicao_juncao, &posicao_juncao2, arvore23_remover2);

            if(removeu_aux == -1)
            {
                valor_juncao = posicao_juncao2->info1;
                pai = arvore23_buscar_pai(*raiz, valor_juncao.br_word);
                removeu_aux = movimento_onda(valor_juncao, &(posicao_juncao2->left->info1), pai, raiz, &posicao_juncao2, &posicao_juncao, arvore23_remover1);

                valor_juncao = no23_maior_info(posicao_juncao);
                maior = NULL;
                removeu_aux = arvore23_rebalancear(raiz, valor_juncao.br_word, &maior);
            }
        }

        if(*raiz == NULL)
            *raiz = maior;
    }

    return removeu;
}

static int balanceamento(Zwei_drei_tree **raiz, Zwei_drei_tree *filho1, Zwei_drei_tree **filho2, Info info, Zwei_drei_tree **maior)
{
    int balanceou = 0;
    if(*filho2 == NULL || !(*filho2)->two_info)
    {
        if(*filho2 != NULL)
            deallocate_tree2(filho2);

        *maior = no23_juntar(filho1, info, *maior, raiz);
        balanceou = 1;
    }
    return balanceou;
}

int arvore23_rebalancear(Zwei_drei_tree **raiz, char *info, Zwei_drei_tree **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!is_leaf(*raiz))
        {
            if(strcmp(info, (*raiz)->info1.br_word) < 0)
                balanceou = arvore23_rebalancear(&((*raiz)->left), info, maior);
            else if((*raiz)->two_info == false || (strcmp(info, (*raiz)->info2.br_word) < 0))
            {
                if((*raiz)->left->two_info && !possivel_remover((*raiz)->mid))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->mid), info, maior);
            }
            else
            {
                if((*raiz)->mid->two_info && !possivel_remover((*raiz)->right))
                    balanceou = -1;
                else
                    balanceou = arvore23_rebalancear(&((*raiz)->right), info, maior);
            }

            if(balanceou != -1)
            {
                if((*raiz)->two_info == false)
                    balanceou = balanceamento(raiz, (*raiz)->left, &((*raiz)->mid), (*raiz)->info1, maior);
                else if((*raiz)->two_info)
                    balanceou = balanceamento(raiz, (*raiz)->mid, &((*raiz)->right), (*raiz)->info2, maior);
            }
            
        }
    }

    return balanceou;
}


/*
void swap_info(Info *a, Info *b) 
{
    Info temp = *a;
    *a = *b;
    *b = temp;
}

// Função para encontrar o sucessor em ordem
Zwei_drei_tree* find_min(Zwei_drei_tree *node) 
{
    while (node->left != NULL) 
        node = node->left;

    return node;
}

// Função para redistribuir nós quando necessário
bool redistribute_nodes(Zwei_drei_tree **Dad, Zwei_drei_tree **root, bool is_left_sibling) 
{
	bool redis = false;
    Zwei_drei_tree *sibling;
    
    if (is_left_sibling) 
	{
        sibling = (*Dad)->left;
        if (sibling->two_info) 
		{
            // Redistribui da esquerda para a direita
            (*root)->info1 = (*Dad)->info1;
            (*Dad)->info1 = sibling->info2;
            sibling->two_info = false;
            redis = true;
        }
    } 
	else 
	{
        sibling = (*Dad)->mid;
        if (sibling->two_info) {
            // Redistribui da direita para a esquerda
            (*root)->info1 = (*Dad)->info1;
            (*Dad)->info1 = sibling->info1;
            sibling->info1 = sibling->info2;
            sibling->two_info = false;
            redis = true;
        }
    }
    return redis;
}

// Função para fundir nós
void merge_nodes(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Zwei_drei_tree *sibling) 
{
    if (*root == (*Dad)->left) 
	{
        sibling->info2 = sibling->info1;
        sibling->info1 = (*Dad)->info1;
        sibling->two_info = true;
        free(*root);
        (*Dad)->left = (*Dad)->mid;
        (*Dad)->mid = (*Dad)->right;
        (*Dad)->right = NULL;
    } 
	else 
	{
        sibling->info2 = (*Dad)->info1;
        sibling->two_info = true;
        free(*root);
        (*Dad)->mid = (*Dad)->right;
        (*Dad)->right = NULL;
    }
}

// Função principal de remoção em nó folha
bool remove_from_leaf(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Info info) 
{
	bool removed = false;
    if ((*root)->two_info) 
	{
        if (strcmp(info.br_word, (*root)->info2.br_word) == 0) 
		{
            (*root)->two_info = false;
            removed =  true;
        }
        if (strcmp(info.br_word, (*root)->info1.br_word) == 0) 
		{
            (*root)->info1 = (*root)->info2;
            (*root)->two_info = false;
            removed =  true;
        }
        removed =  false;
    }
	else
	{
		// Caso 2: Nó tem uma informação
		if (strcmp(info.br_word, (*root)->info1.br_word) == 0) 
		{

			if (*Dad == NULL) 
			{
				free(*root);
				*root = NULL;
				removed = true;
			}
			
			// Tenta redistribuição
			else if (*root == (*Dad)->left || *root == (*Dad)->mid) 
			{
				if (redistribute_nodes(Dad, root, *root == (*Dad)->mid)) 
					removed = true;
			}

			if(!removed)
			{
				// Se não foi possível redistribuir, faz a fusão
				if (*root == (*Dad)->left) 
					merge_nodes(Dad, root, (*Dad)->mid);
				else if (*root == (*Dad)->mid) 
					merge_nodes(Dad, root, (*Dad)->left);
				else 
					merge_nodes(Dad, root, (*Dad)->mid);
				
				// Se o pai ficou sem informações, precisa reorganizar a árvore
				if ((*Dad)->mid == NULL) 
				{
					Zwei_drei_tree *temp = *Dad;
					*Dad = (*Dad)->left;
					free(temp);
				}

				removed =  true;
			}

		}
	}

    
    return removed;
}

// Função principal de remoção
bool remove_23(Zwei_drei_tree **Dad, Zwei_drei_tree **root, Info info) 
{
	bool removed = false;

    if (*root != NULL) 
	{
		// Se é folha, remove diretamente
		if (is_leaf(*root)) 
		{
			////////////////////////////////////////////
			removed = remove_from_leaf(Dad, root, info);
		}
		else
		{

			// Se não é folha, navega até encontrar o nó apropriado
			if (strcmp(info.br_word, (*root)->info1.br_word) < 0) 
				removed = remove_23(root, &(*root)->left, info);
			else if (strcmp(info.br_word, (*root)->info1.br_word) == 0) 
			{
				Zwei_drei_tree *successor = find_min((*root)->mid);
				swap_info(&(*root)->info1, &successor->info1);
				removed = remove_23(root, &(*root)->mid, info);
			}
			else if (!(*root)->two_info || strcmp(info.br_word, (*root)->info2.br_word) < 0) 
				removed = remove_23(root, &(*root)->mid, info);
			else if ((*root)->two_info && strcmp(info.br_word, (*root)->info2.br_word) == 0) 
			{
				Zwei_drei_tree *successor = find_min((*root)->right);
				swap_info(&(*root)->info2, &successor->info1);
				removed = remove_23(root, &(*root)->right, info);
			}
			else if ((*root)->two_info) 
				removed = remove_23(root, &(*root)->right, info);
		}
        
    }
    
    return removed;
}
*/


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

Zwei_drei_tree *search_23_tree(Zwei_drei_tree *root, const char *br_word, int *info) 
{
	Zwei_drei_tree *result;
	result = NULL;


    if (root != NULL) 
	{
		// Verifica o primeiro item (info1)
		if (strcmp(br_word, root->info1.br_word) == 0) 
		{
			*info = 1;
			result = root;
		}
		// Verifica o segundo item (info2), se existir
		else if (root->two_info && strcmp(br_word, root->info2.br_word) == 0) 
		{
			*info = 2;
			result = root;
		}
		else
		{
			if (strcmp(br_word, root->info1.br_word) < 0) 
				result = search_23_tree(root->left, br_word, info);  
			else if (!root->two_info || strcmp(br_word, root->info2.br_word) < 0) 
				result = search_23_tree(root->mid, br_word, info);  
			else 
				result = search_23_tree(root->right, br_word, info); 
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

		char normalized_info1[256];
        strcpy(normalized_info1, root->info1.br_word);
        trim_string(normalized_info1);

		char normalized_info2[256];
		if(root->two_info)
		{
			strcpy(normalized_info2, root->info2.br_word);
			trim_string(normalized_info2);
		}

		// if (!root->two_info)
        //     printf("%s - %s - %d\n", normalized_info1, normalized_br_word, strcmp(normalized_br_word, normalized_info1));
        // else {
        //     printf("%s - %s - %d\n", normalized_info1, normalized_br_word, strcmp(normalized_info1, normalized_br_word));
        //     printf("%s - %s - %d\n", normalized_info2, normalized_br_word, strcmp(normalized_info2, normalized_br_word));
        // }

        if (strcmp(normalized_br_word, normalized_info1) == 0) 
		{
			printf("Entrou\n");
            show_all_eng_words(root->info1.eng_words);
            printf("\n");
        }
        if (root->two_info && strcmp(normalized_br_word, normalized_info2) == 0) 
		{
			printf("Entrou\n");
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
		{
			printf("Entrei 1\n");
			remove_23(root, (*root)->info1.br_word);
		}

		if (!removed && (*root)->two_info) 
		{
			removed = remove_eng_word_bin(&(*root)->info2.eng_words, info_bin);

			if (removed && is_binary_tree_empty((*root)->info2.eng_words)) 
			{
				printf("Entrei 2\n");
				remove_23(root, (*root)->info2.br_word);
			}
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
		else if (!(*root)->two_info || strcmp(info.br_word, (*root)->info1.br_word) > 0) 
			remove_port_word(&(*root)->mid, info);
		else if ((*root)->two_info) 
			remove_port_word(&(*root)->right, info);
		else 
		{
			// Encontrou o nó correspondente para remoção
			if (strcmp(info.br_word, (*root)->info1.br_word) == 0) 
				remove_all_eng_words(root, (*root)->info1.eng_words);
			else if ((*root)->two_info && strcmp(info.br_word, (*root)->info2.br_word) == 0) 
				remove_all_eng_words(root, (*root)->info2.eng_words);
			
			remove_23(root, info.br_word);
		}
	} 
}