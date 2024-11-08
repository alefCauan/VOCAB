#include "parser.h"
#include "../trees/tree_23/tree_23.h"
#include "../utils/aux.h"

FILE *_open_file(const char *file_name, const char *type)
{
    FILE *file = fopen(file_name, type);
    ASSERT_ALLOC(file, "open file");

    return file;
}

void scan_file_line() 
{
    FILE *parser = _open_file(PARSER_PATH, "r");

    char line[1024];

    while (fgets(line, sizeof(line), parser)) 
    {
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == UNIT_TOKEN) 
        {
            printf("----------------------------------------------------\n");
            printf("Nova unidade: %s\n", line);
            printf("----------------------------------------------------\n");
        }
        else 
        {
            char *english_word = strtok(line, ENG_TOKEN);
            char *translations = strtok(NULL, END_TOKEN);

            if (english_word != NULL && translations != NULL) 
            {
                printf("Palavra em inglês: %s\n", english_word);
                
                char *translation = strtok(translations, BR_TOKEN);
                while (translation != NULL) 
                {
                    printf("Tradução: %s\n", translation);
                    translation = strtok(NULL, BR_TOKEN);
                }
            }
        }
    }

    fclose(parser);
}


void printf_file_line()
{
    /////////////////////////////
    /////////////////////////////
    /////////////////////////////
}

