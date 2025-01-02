
#include "red_black_tree.h"
#include "../../utils/aux.h"

Red_black_tree *allocate_red_black(Info_rb info) 
{
    Red_black_tree *node = (Red_black_tree *)malloc(sizeof(Red_black_tree));
    
    ASSERT_ALLOC(node, "allocate red_black");

    strcpy(node->info.br_word, info.br_word);
    node->info.unit = info.unit;

    node->color = RED;
    node->info.eng_words = info.eng_words;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void deallocate_red_black_tree(Red_black_tree *root) 
{
    if (root) 
    {
        deallocate_red_black_tree(root->left);  
        deallocate_red_black_tree(root->right); 

        free(root); 
    }
}


Color color(Red_black_tree *root) 
{
    Color clr;

    if(root == NULL)
        clr = BLACK;
    else
        clr = root->color;

    return clr;
}

bool is_red(Red_black_tree *node) 
{
    //////////////////////////////////////////
    bool red = false;
    if(node)
        ((*node).color == RED) ? (red = true) : red;

    return red;
    //////////////////////////////////////////
}

void rotate_left(Red_black_tree **root) 
{
    if (*root && (*root)->right) 
    {
        Red_black_tree *new_root = (*root)->right;

        (*root)->right = new_root->left; 
        new_root->left = *root;         

        new_root->color = (*root)->color;
        (*root)->color = RED;

        *root = new_root;
    }
}


void rotate_right(Red_black_tree **root) 
{
    if (*root && (*root)->left) 
    {
        Red_black_tree *new_root = (*root)->left;

        (*root)->left = new_root->right; 
        new_root->right = *root;        

        new_root->color = (*root)->color;
        (*root)->color = RED;

        *root = new_root;
    }
}


void swap_color(Red_black_tree **node) 
{
    if (*node) 
    {
        (*node)->color = !(*node)->color; 
        if ((*node)->left) 
            (*node)->left->color = !(*node)->left->color;
        if ((*node)->right) 
            (*node)->right->color = !(*node)->right->color; 
    }
}

Red_black_tree *balance(Red_black_tree *node) 
{
    if (is_red(node->right) && !is_red(node->left)) 
        rotate_left(&node);
    if (is_red(node->left) && is_red(node->left->left)) 
        rotate_right(&node);
    if (is_red(node->left) && is_red(node->right)) 
        swap_color(&node);

    return node;
}


Red_black_tree *insert_rb(Red_black_tree *root, Info_rb info) 
{
    Red_black_tree *result;

    if (root == NULL) 
        root = allocate_red_black(info);
    else
    {
        if (strcmp(info.br_word, root->info.br_word) < 0)
            root->left = insert_rb(root->left, info);
        else if (strcmp(info.br_word, root->info.br_word) > 0)
            root->right = insert_rb(root->right, info);
        else
            insert_bin(root->info.eng_words, info.eng_words);
    }
        

    return balance(root);
}

Red_black_tree *register_rb(Red_black_tree *root, Info_rb info) 
{
    root = insert_rb(root, info);
    if(root)
        root->color = BLACK;  

    return root;
}

void move_left(Red_black_tree **node) 
{
    if (*node) 
    {
        swap_color(node); 

        if ((*node)->right && is_red((*node)->right->left)) 
        {
            rotate_right(&((*node)->right)); 
            rotate_left(node);              
            swap_color(node);             
        }
    }
}


void move_right(Red_black_tree **node) 
{
    if (*node) 
    {
        swap_color(node); 

        if ((*node)->left && is_red((*node)->left->left))
        {
            rotate_right(node);  
            swap_color(node);   
        }
    }
}


Red_black_tree *search_rb(Red_black_tree *root, const char *br_word) 
{
	Red_black_tree *result;
	result = NULL;

    if (root != NULL) 
	{
        if (strcmp(br_word, root->info.br_word) == 0) 
            result = root;
        else if (strcmp(br_word, root->info.br_word) < 0) 
            result = search_rb(root->left, br_word);  
        else if (strcmp(br_word, root->info.br_word) > 0) 
            result = search_rb(root->right, br_word);  
	}
    
	return result;
}



Red_black_tree *find_min(Red_black_tree *root) 
{
    while (root && root->left) 
        root = root->left;
    
    return root;
}

void remove_min(Red_black_tree **root) 
{
    if (*root) 
    {
        if ((*root)->left == NULL) 
        {
            free(*root);  
            *root = NULL;
        } 
        else 
        {
            if ((*root)->left &&
            !is_red((*root)->left) && !is_red((*root)->left->left)) 
                move_left(root);  
            
            remove_min(&((*root)->left));  
            
            *root = balance(*root); 
        }
    }
}


bool remove_node(Red_black_tree **root, const char *word) 
{
    bool found = false;

    if (*root) 
    {
        if (strcmp(word, (*root)->info.br_word) < 0) 
        {
            if (!is_red((*root)->left) && !is_red((*root)->left->left)) 
                move_left(root);

            found = remove_node(&((*root)->left), word);
        } 
        else 
        {
            if ((*root)->left && is_red((*root)->left)) 
                rotate_right(root);

            if (strcmp(word, (*root)->info.br_word) == 0)
            {
                if((*root)->right == NULL)
                {
                    found = true;

                    free(*root);  
                    *root = NULL;
                }
                else
                {
                    Red_black_tree *small = find_min((*root)->right);
                    (*root)->info = small->info;
                    remove_min(&(*root)->right);
                }
            }
            else 
            {
                if ((*root)->right && color((*root)->right) == BLACK && color((*root)->right->left) == BLACK) 
                    move_right(root);

                found = remove_node(&((*root)->right), word);
            }
        }

        if (*root) 
            *root = balance(*root); 
    }

    return found;
}

bool remove_rb(Red_black_tree **root, const char *word) 
{
    bool result = remove_node(root, word);

    if (*root) 
        (*root)->color = BLACK;

    return result;
}


void show_port_and_eng_words_rb(Red_black_tree *root, int unit)
{
	if(root)
	{
		if (root->info.unit == unit)
		{
			printf("PORTUGUES: %s\n", root->info.br_word);
			printf("  Traduções em inglês:");
            show_all_eng_words(root->info.eng_words);
            printf("\n");
		}
	
		show_port_and_eng_words_rb(root->left, unit);
		show_port_and_eng_words_rb(root->right, unit);
	}
}

void show_eng_words_rb(Red_black_tree *root, const char *br_word) 
{
    if (root) 
	{
        // Normaliza as strings antes da comparação
        char normalized_br_word[256];
        strcpy(normalized_br_word, br_word);
        trim_string(normalized_br_word);

        if (strcmp(normalized_br_word, root->info.br_word) == 0) 
		{
            show_all_eng_words(root->info.eng_words);
            printf("\n");
        }

        show_eng_words_rb(root->left, br_word);
        show_eng_words_rb(root->right, br_word);
    }
}

void remove_eng_word_rb(Red_black_tree **root, Info_bin info_bin) 
{
    if (*root)
	{
		bool removed = false;

		remove_eng_word_rb(&(*root)->left, info_bin);
		remove_eng_word_rb(&(*root)->right, info_bin);

		char normalized_info[256];
		strcpy(normalized_info, info_bin.eng_word);
		trim_string(normalized_info);
		strcpy(info_bin.eng_word, normalized_info);

		removed = remove_eng_word_bin(&(*root)->info.eng_words, info_bin);

		if (removed && is_binary_tree_empty((*root)->info.eng_words)) 
			remove_rb(root, (*root)->info.br_word);
	}

}

void remove_all_eng_words_rb(Red_black_tree **root, Binary_tree *eng_words)
{
	if(eng_words)
	{
		remove_all_eng_words_rb(root, eng_words->left);
		remove_all_eng_words_rb(root, eng_words->right);

		remove_eng_word_rb(root, eng_words->info);
	}
}

void remove_port_word_rb(Red_black_tree **root, Info_rb info) 
{
    if (*root)
	{
		if (strcmp(info.br_word, (*root)->info.br_word) < 0) 
			remove_port_word_rb(&(*root)->left, info);
		else if (strcmp(info.br_word, (*root)->info.br_word) > 0) 
			remove_port_word_rb(&(*root)->right, info);
		else 
		{
			// Encontrou o nó correspondente para remoção
			if (strcmp(info.br_word, (*root)->info.br_word) == 0) 
				remove_all_eng_words_rb(root, (*root)->info.eng_words);
			
            remove_rb(root, (*root)->info.br_word);
		}
	} 
}