#include "binary.h"

Binary_tree *allocate_binary()
{
    Binary_tree *new = (Binary_tree *)malloc(sizeof(Binary_tree));
    // TODO: ASSERT ALLOC
    return new;
}

Binary_tree *search_bin(Binary_tree *root, Info_bin info) 
{
    Binary_tree *result = NULL;  

    if (root != NULL) 
    {
        if(strcmp(root->info.eng_word, info.eng_word) == 0)
            result = root;
        else if (strcmp(info.eng_word, root->info.eng_word) < 0) 
            result = search_bin(root->left, info);
        else 
            result = search_bin(root->right, info);
    }

    return result;  
}

bool insert_bin(Binary_tree **root, Binary_tree *new)
{
    bool result = true;

    if ((*root) == NULL)
        (*root) = new;  
    else if (strcmp(new->info.eng_word,(*root)->info.eng_word) < 0)
        result = insert_bin(&(*root)->left, new);  
    else if (strcmp(new->info.eng_word, (*root)->info.eng_word) > 0) 
        result = insert_bin(&(*root)->right, new);  
    else 
        result = false;

    return root;  
}

void register_bin(Binary_tree **root, Info_bin info)
{
    Binary_tree *new = allocate_binary();
    new->info = info;

    if (!insert_bin(root, new))
    {
        // TODO: ERROR
        // RAISE_ERROR("insert enrol, code already inserted");  
        // deallocate_enrollment(new);
    }
}