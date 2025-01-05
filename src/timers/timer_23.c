#include "../trees/tree_23/tree_23.h"
#include <time.h>

#define INFO_SIZE 10000


Zwei_drei_tree *search_23_path(Zwei_drei_tree *root, char *info, int level)
{
    Zwei_drei_tree *node;
    node = NULL;

    if(root != NULL)
    {
        for (int i = 0; i < level; i++)
            printf(" ");
        
        level += 1;
        if(is_info1(*root, info) || is_info2(*root, info))
        {
            printf("encontrou [%s]\n", info);
            node = root;
        }
        else if(strcmp(info, root->info1.br_word) < 0)
        {
            printf("[L] -> \n");
            node = search_23_path(root->left, info, level);
        }
        else if(root->two_info == false || (strcmp(info, root->info2.br_word) < 0))
        {
            printf("[M] -> \n");
            node = search_23_path(root->mid, info, level);
        }
        else
        {
            printf("[R] -> \n");
            node = search_23_path(root->right, info, level);
        }
    }

    return node;
}

double get_time_micro(clock_t start, clock_t end)
{
    return ((double)(end - start)) / CLOCKS_PER_SEC / 30; // Convertendo para microsegundos
}

int main()
{
    Zwei_drei_tree *zd = NULL;

    srand(time(NULL));
    Info infos[INFO_SIZE];

    char letras[][2] = {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
    };

    // Gerar 30 informações aleatórias e armazená-las em infos
    for (int i = 0; i < INFO_SIZE; i++)
    {
        infos[i].unit = rand() % 10;
        snprintf(infos[i].br_word, sizeof(infos[i].br_word), "palavra%d%c", rand() % 1000, letras[rand() % 26][0]);
    }

    for (int i = 0; i < INFO_SIZE; i++)
    {
        Info rise;
        insert_tree_23(NULL, &zd, infos[i], &rise);
    }

    
    double media;

    for (int i = 0; i < 30; i++) 
    {
        clock_t start_search = clock();
        search_23(zd, infos[rand() % INFO_SIZE].br_word);
        clock_t end_search = clock();


        double search_time = get_time_micro(start_search, end_search);
        printf("%.9f\n", search_time);
        media += search_time;
    }

    media =  media / 30;
    printf("Media: %.9f\n", media);

}

// gcc -g -o main timer_23.c ../trees/tree_23/tree_23.c ../trees/binary_tree/binary.c ../utils/aux.c