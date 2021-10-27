#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*This function takes a string as input, 
replaces all uppercase letters with lowercase letters,
and replaces exclamation marks with periods. */
char *formatString(char *str)
{
    for (int i = 0; i <= strlen(str); i++)
    {
        str[i] = tolower(str[i]);
        if (str[i] == '!')
        {
            str[i] = '.';
        }
    }
    return str;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("...\n");
    }
    else
    {
        printf("(");
        for (int i = 1; i <= argc - 2; i++)
        {
            printf("%s ", formatString(argv[i]));
        }
        printf("%s", formatString(argv[argc - 1]));
        printf(")\n");
    }
}