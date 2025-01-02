#include "../src/trees/red_black_tree/red_black_tree.h"
#include "../src/parser/parser_rb.h"

int main()
{
    Red_black_tree *root = NULL;

    scan_file_line_rb(&root);

    // show_port_and_eng_words_rb(root, 2);
    // show_eng_words_rb(root, "nó");
    // show_all_eng_words((*root).info.eng_words);

    Info_rb info;
    strcpy(info.br_word, "inseto");
    Info_bin bin = {
        .unit = 2
    };
    strcpy(bin.eng_word, "Bug");


    info.eng_words = allocate_binary(bin);
    info.unit = 1;
    
    // remove_eng_word_rb(&root, (Info_bin){.eng_word="Bug", 1});
    remove_port_word_rb(&root, info);
    show_port_and_eng_words_rb(root, 1);
    // show_all_eng_words((*root).info.eng_words);

    deallocate_red_black_tree(root);

    return 0;
}