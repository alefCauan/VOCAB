#include "parser/parser.h"

int main() 
{
    Zwei_drei_tree *root; 
    scan_file_line(&root);


    int option;

    while (1) 
    {
        printf("\nMenu:\n");
        printf("[1] - Mostrar palavras em português e suas equivalentes em inglês por unidade\n");
        printf("[2] - Mostrar palavras em inglês equivalentes a uma palavra em português\n");
        printf("[3] - Remover uma palavra em inglês e sua árvore, se necessário\n");
        printf("[4] - Remover uma palavra em português e sua árvore, se necessário\n");
        printf("[5] - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) 
        {
            case 1: 
            {
                int unit;
                printf("Informe a unidade: ");
                scanf("%d", &unit);
                show_port_and_eng_words(root, unit);
                break;
            }
            case 2: 
            {
                char br_word[100];
                printf("Informe a palavra em português: ");
                setbuf(stdin, NULL);
                scanf("%s", br_word);
                show_eng_words(root, br_word);
                break;
            }
            case 3: 
            {
                Info_bin info_bin;
                printf("Informe a palavra em inglês: ");
                setbuf(stdin, NULL);
                scanf("%s", info_bin.eng_word);
                printf("Informe a unidade: ");
                scanf("%d", &info_bin.unit);
                remove_eng_word(&root, info_bin);
                break;
            }
            case 4: 
            {
                Info info;
                printf("Informe a palavra em português: ");
                setbuf(stdin, NULL);
                scanf("%s", info.br_word);
                printf("Informe a unidade: ");
                scanf("%d", &info.unit);
                remove_port_word(&root, info);
                break;
            }
            case 5:
            {
                printf("Encerrando o programa.\n");
                exit(0);
                break;
            }
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    deallocate_tree2(&root);

    return 0;
}
