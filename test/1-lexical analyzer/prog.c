#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int iskeyword(char buffer[])
{

    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

    int i, flag = 0;

    for (i = 0; i < 32; ++i)
    {
        if (strcmp(keywords[i], buffer) == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

int main()
{

    int j = 0, k = 0;
    char ch;
    FILE *fp;
    char operators[] = "+-*/%";
    char specialch[] = ",;[]{}";
    char numbuf[20];
    char buffer[20];

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("file reading failed\n");
    }

    while ((ch = fgetc(fp)) != EOF)
    {

        for (int i = 0; i < 5; i++)
        {
            if (ch == operators[i])
            {
                printf("%c is an operator\n", ch);
            }
        }

        for (int i = 0; i < 6; i++)
        {
            if (ch == specialch[i])
            {
                printf("%c is a special character \n", ch);
            }
        }

        if (isalpha(ch))
        {
            buffer[j++] = ch;
        }

        if (isdigit(ch))
        {
            numbuf[k++] = ch;
        }

        else if (ch == ' ' || ch == '\n')
        {
            if (j != 0)
            {
                buffer[j] = '\0';

                if (iskeyword(buffer))
                {
                    printf("%s is a keyword\n", buffer);
                }
                else
                {
                    printf("%s is an identifier\n", buffer);
                }
                j = 0;
            }

            if (k != 0)
            {
                numbuf[k] = '\0';
                printf("%s is a constant\n", numbuf);
                k = 0;
            }
        }
    }

    if (j != 0)
    {
        buffer[j] = '\0';

        if (iskeyword(buffer))
        {
            printf("%s is a keyword\n", buffer);
        }
        else
        {
            printf("%s is an identifier\n", buffer);
        }
    }

    if (k != 0)
    {
        numbuf[k] = '\0';
        printf("%s is a constant\n", numbuf);
        k = 0;
    }

    fclose(fp);
    return 0;
}


/*
PS C:\Users\allen\OneDrive\Desktop\test\1-lexical analyzer> gcc .\prog.c
PS C:\Users\allen\OneDrive\Desktop\test\1-lexical analyzer> .\a.exe     
my is an identifier
name is an identifier
is is an identifier
allen is an identifier
i is an identifier
am is an identifier
22 is a constant
typedef is a keyword
i is an identifier
am is an identifier
currently is an identifier
pursuing is an identifier
btech is an identifier
2026 is a constant
batch is an identifier
typedef is a keyword
PS C:\Users\allen\OneDrive\Desktop\test\1-lexical analyzer> 
*/