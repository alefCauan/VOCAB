
#include "red_black_tree.h"
#include "../../utils/aux.h"

Red_black_tree *allocate_red_black(Info_rb info) 
{
    Red_black_tree *node = (Red_black_tree *)malloc(sizeof(Red_black_tree));
    
    ASSERT_ALLOC(node, "allocate red_black");

    strcpy(node->info.br_word, info.br_word);
    node->info.unit = info.unit;

    node->color = RED;
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
    if (root == NULL) 
        return allocate_red_black(info);

    if (strcmp(info.br_word, root->info.br_word) < 0)
        root->left = insert_rb(root->left, info);
    else if (strcmp(info.br_word, root->info.br_word) > 0)
        root->right = insert_rb(root->right, info);

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

bool remove_in_tree(Red_black_tree **root, const char *word) 
{
    bool result = remove_node(root, word);

    if (*root) 
        (*root)->color = BLACK;

    return result;
}

