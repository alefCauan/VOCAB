#include "parser_rb.h"

FILE *_open_file_rb(const char *file_name, const char *type)
{
    FILE *file = fopen(file_name, type);
    ASSERT_ALLOC(file, "open file");

    return file;
}

// Função principal de leitura do arquivo 
void scan_file_line_rb(Red_black_tree **root) 
{
    FILE *parser = _open_file_rb(PARSER_PATH, "r");

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
                char normalized_eng[256];
                strcpy(normalized_eng, english_word);
                trim_string(normalized_eng);

                while (translation != NULL) 
                {
                    char normalized_pt[256];
                    strcpy(normalized_pt, translation);
                    trim_string(normalized_pt);

                    insert_vocabulary_rb(root, normalized_pt, normalized_eng, unit);
                    translation = strtok(NULL, BR_TOKEN);
                }
            }
        }
    }

    fclose(parser);
}

// Função para inserir vocabulário na árvore
void insert_vocabulary_rb(Red_black_tree **root, char *translation, char *english_word, int unit) 
{
    Info_bin info_bin = {
        .units = create_list(unit)
    };
    strcpy(info_bin.eng_word, english_word);

    Info_rb new_info = {
        .eng_words = allocate_binary(info_bin),
        .unit = unit
    };
    strcpy(new_info.br_word, translation);

    *root = insert_rb(*root, new_info);

}
