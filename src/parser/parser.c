#include "parser.h"
#include "../trees/tree_23/tree_23.h"
#include "../utils/aux.h"

FILE *_open_file(const char *file_name, const char *type)
{
    FILE *file = fopen(file_name, type);
    ASSERT_ALLOC(file, "open file");

    return file;
}

// Função principal de leitura do arquivo
void scan_file_line(Zwei_drei_tree **root) 
{
    FILE *parser = _open_file(PARSER_PATH, "r");

    char line[1024];
    int unit = 0;

    while (fgets(line, sizeof(line), parser)) 
    {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == UNIT_TOKEN) 
            unit += 1;
        else 
        {
            char *english_word = strtok(line, ENG_TOKEN);
            char *translations = strtok(NULL, END_TOKEN);

            if (english_word != NULL && translations != NULL) 
            {
                char *translation = strtok(translations, BR_TOKEN);

                while (translation != NULL) 
                {
                    insert_vocabulary(root, translation, english_word, unit);
                    translation = strtok(NULL, BR_TOKEN);
                }
            }
        }
    }

    fclose(parser);
}

// Função para inserir vocabulário na árvore
void insert_vocabulary(Zwei_drei_tree **root, char *translation, char *english_word, int unit) 
{
    int info = 1;
    Zwei_drei_tree *result = search_23_tree(*root, translation, &info);
    Info_bin info_bin;

    info_bin.unit = unit;
    strcpy(info_bin.eng_word, english_word);

    if (result) 
    {
        if (info == 1)
            register_bin(&result->info1.eng_words, info_bin);
        else if(info == 2)
            register_bin(&result->info2.eng_words, info_bin);
    } 
    else 
    {
        Info new_info, rise;

        strcpy(new_info.br_word, translation);
        new_info.unit = unit;
        new_info.eng_words = NULL;

        register_bin(&new_info.eng_words, info_bin);
        insert_tree_23(NULL, root, new_info, &rise);
    }
}


