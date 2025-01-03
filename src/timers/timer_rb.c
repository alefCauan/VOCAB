#include "../trees/red_black_tree/red_black_tree.h"

#include <time.h>

#define INFO_SIZE 100 * 100


Red_black_tree *search_rb_path(Red_black_tree *root, char *info, int level)
{
    Red_black_tree *node;
    node = NULL;

    if(root != NULL)
    {
        for (int i = 0; i < level; i++)
            printf(" ");
        
        level += 1;
        if(strcmp(info, root->info.br_word) == 0)
        {
            printf("encontrou [%s]\n", info);
            node = root;
        }
        else if(strcmp(info, root->info.br_word) < 0)
        {
            printf("[L] -> \n");
            node = search_rb_path(root->left, info, level);
        }
        else
        {
            printf("[R] -> \n");
            node = search_rb_path(root->right, info, level);
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
    Red_black_tree *rb = NULL;

    srand(time(NULL));
    Info_rb infos[INFO_SIZE];

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
        rb = insert_rb(rb, infos[i]);

    
    float media = 0.0;

    for (int i = 0; i < 30; i++) 
    {
        clock_t start_search = clock();
        search_rb(rb, infos[rand() % INFO_SIZE].br_word);
        clock_t end_search = clock();


        double search_time = get_time_micro(start_search, end_search);
        printf("%.9f\n", search_time);
        media += search_time;
    }

    media =  media / 30;
    printf("Media: %.9f\n", media);

    deallocate_red_black_tree(rb);
}

// gcc -g -o timer_rb timer_2b.c ../trees/red_black_tree/red_black_tree.c ../trees/binary_tree/binary.c ../utils/aux.c