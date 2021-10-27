#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* toLower(char* str)
{
    for(int i = 0; i <= strlen(str); i++)
    {
        str[i] = tolower(str[i]);
    }
    return str;
}

int main(int argc, char** argv)
{
    char* word = toLower(argv[1]);
    int tally[26];
    for(int i = 0; i < 26; i++)
    {
        tally[i] = 0;
    }
    for(int i = 0; i < strlen(word); i++)
    {
        char letter = argv[1][i];
        switch(letter)
        {
            case 'a': tally[0]++; break;
            case 'b': tally[1]++; break;
            case 'c': tally[2]++; break;
            case 'd': tally[3]++; break;
            case 'e': tally[4]++; break;
            case 'f': tally[5]++; break;
            case 'g': tally[6]++; break;
            case 'h': tally[7]++; break;
            case 'i': tally[8]++; break;
            case 'j': tally[9]++; break;
            case 'k': tally[10]++; break;
            case 'l': tally[11]++; break;
            case 'm': tally[12]++; break;
            case 'n': tally[13]++; break;
            case 'o': tally[14]++; break;
            case 'p': tally[15]++; break;
            case 'q': tally[16]++; break;
            case 'r': tally[17]++; break;
            case 's': tally[18]++; break;
            case 't': tally[19]++; break;
            case 'u': tally[20]++; break;
            case 'v': tally[21]++; break;
            case 'w': tally[22]++; break;
            case 'x': tally[23]++; break;
            case 'y': tally[24]++; break;
            case 'z': tally[25]++; break;
        }    
    }
    for (int i = 0; i < tally[0]; i++)
    {
        printf("%s", "a");
    }
    for (int i = 0; i < tally[1]; i++)
    {
        printf("%s", "b");
    }
    for (int i = 0; i < tally[2]; i++)
    {
        printf("%s", "c");
    }
    for (int i = 0; i < tally[3]; i++)
    {
        printf("%s", "d");
    }
    for (int i = 0; i < tally[4]; i++)
    {
        printf("%s", "e");
    }
    for (int i = 0; i < tally[5]; i++)
    {
        printf("%s", "f");
    }
    for (int i = 0; i < tally[6]; i++)
    {
        printf("%s", "g");
    }
    for (int i = 0; i < tally[7]; i++)
    {
        printf("%s", "h");
    }
    for (int i = 0; i < tally[8]; i++)
    {
        printf("%s", "i");
    }
    for (int i = 0; i < tally[9]; i++)
    {
        printf("%s", "j");
    }
    for (int i = 0; i < tally[10]; i++)
    {
        printf("%s", "k");
    }
    for (int i = 0; i < tally[11]; i++)
    {
        printf("%s", "l");
    }
    for (int i = 0; i < tally[12]; i++)
    {
        printf("%s", "m");
    }
    for (int i = 0; i < tally[13]; i++)
    {
        printf("%s", "n");
    }
    for (int i = 0; i < tally[14]; i++)
    {
        printf("%s", "o");
    }
    for (int i = 0; i < tally[15]; i++)
    {
        printf("%s", "p");
    }
    for (int i = 0; i < tally[16]; i++)
    {
        printf("%s", "q");
    }
    for (int i = 0; i < tally[17]; i++)
    {
        printf("%s", "r");
    }
    for (int i = 0; i < tally[18]; i++)
    {
        printf("%s", "s");
    }
    for (int i = 0; i < tally[19]; i++)
    {
        printf("%s", "t");
    }
    for (int i = 0; i < tally[20]; i++)
    {
        printf("%s", "u");
    }
    for (int i = 0; i < tally[21]; i++)
    {
        printf("%s", "v");
    }
    for (int i = 0; i < tally[22]; i++)
    {
        printf("%s", "w");
    }
    for (int i = 0; i < tally[23]; i++)
    {
        printf("%s", "x");
    }
    for (int i = 0; i < tally[24]; i++)
    {
        printf("%s", "y");
    }
    for (int i = 0; i < tally[25]; i++)
    {
        printf("%s", "z");
    }
    printf("\n");
}