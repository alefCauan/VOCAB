#include "../src/trees/red_black_tree/red_black_tree.h"
#include "../src/parser/parser_rb.h"

int main()
{
    Red_black_tree *root = NULL;

    scan_file_line_rb(&root);

    // show_port_and_eng_words_rb(root, 1);
    // show_all_eng_words((*root).info.eng_words);
    Info_rb info;

    strcpy(info.br_word, "inseto");
    info.eng_words = NULL;
    info.unit = 1;
    remove_port_word_rb(&root, info);
    show_all_eng_words((*root).info.eng_words);

    return 0;
}