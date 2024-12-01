#include "../src/parser/parser.h"

int main()
{
    Zwei_drei_tree *root;
    root = NULL;
    scan_file_line(&root);
    // print_tree(root, 0);
    printf("\n----------------------------------------------------------------------------------------\n");
    Info_bin bin;

    setbuf(stdin, NULL);
    scanf("%[^\n]", bin.eng_word);
    remove_eng_word(&root, bin);
    print_tree(root, 0);
    printf("\n----------------------------------------------------------------------------------------\n");
    // setbuf(stdin, NULL);
    // scanf("%[^\n]", bin.eng_word);
    // remove_eng_word(&root, bin);
    // print_tree(root, 0);
    printf("\n----------------------------------------------------------------------------------------\n");
    // Info info = {.br_word = "dispositivo", .unit = 1, .eng_words = NULL};
    // remove_port_word(&root, info);
    // print_tree(root, 0);


    deallocate_tree(root);

    return 0;
}