#include <stdio.h>
#include <string.h>


int main()
{
    int result = 0;
    char palavra1[] = {"czrr0"};
    char palavra2[] = {"casa"};

    result = strcmp(palavra1, palavra2);
    
    printf("Result: %d\n", result);

    return 0;
}