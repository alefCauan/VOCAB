#include "../src/parser/parser.h"

int main()
{
    Zwei_drei_tree *root;
    root = NULL;
    scan_file_line(&root);

    print_tree(root, 0);
    print_bin_tree(root, 0);

    deallocate_tree(root);

    return 0;
}