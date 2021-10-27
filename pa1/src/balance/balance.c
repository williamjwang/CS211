#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void push(char* stack, int *count, char x)
{
    *(stack + *count) = x;
    *count = *count + 1;
}

char pop(char* stack, int* count)
{
    char letter = *(stack + (*count - 1));
    *count = *count - 1;
    return letter;
}

void printMatch(char* stack, int* count)
{
    printf("open: ");
    for(int i = *count - 1; i >= 0; i--)
    {
        if (stack[i] == '(') printf("%c", ')');
        if (stack[i] == '[') printf("%c", ']');
        if (stack[i] == '{') printf("%c", '}');
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    char* stack = (char*)malloc(sizeof(char) * strlen(argv[1]));
    int count = 0;
    int checkMismatched = 0;

    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if (argv[1][i] == ')' && count == 0)
        {
            printf("%d: %c\n", i, ')');
            checkMismatched = 1;
            free(stack);
            return EXIT_FAILURE;
        }
        if (argv[1][i] == ']' && count == 0)
        {
            printf("%d: %c\n", i, ']');
            checkMismatched = 1;
            free(stack);
            return EXIT_FAILURE;
        }
        if (argv[1][i] == '}' && count == 0)
        {
            printf("%d: %c\n", i, '}');
            checkMismatched = 1;
            return EXIT_FAILURE;
        }

        if (argv[1][i] == '(') push(stack, &count, '(');
        if (argv[1][i] == '[') push(stack, &count, '[');
        if (argv[1][i] == '{') push(stack, &count, '{');

        if(argv[1][i] == ')')
        {
            char temp = pop(stack, &count);
            if (temp != '(')
            {
                printf("%d: %c\n", i, ')');
                checkMismatched = 1;
                free(stack);
                return EXIT_FAILURE;
            }
        }
        if(argv[1][i] == ']')
        {
            char temp = pop(stack, &count);
            if (temp != '[')
            {
                printf("%d: %c\n", i, ']');
                checkMismatched = 1;
                free(stack);
                return EXIT_FAILURE;
            }
        }
        if(argv[1][i] == '}')
        {
            char temp = pop(stack, &count);
            if (temp != '{')
            {
                printf("%d: %c\n", i, '}');
                checkMismatched = 1;
                free(stack);
                return EXIT_FAILURE;
            }
        }
    }
    if (count == 0)
    {
        free(stack);
        return EXIT_SUCCESS;
    }
    else
    {
        if (checkMismatched == 0) printMatch(stack,&count);
        free(stack);
        return EXIT_FAILURE;
    }
}