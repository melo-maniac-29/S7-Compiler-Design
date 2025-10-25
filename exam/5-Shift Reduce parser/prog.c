#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int z = 0, i = 0, j = 0, c = 0;
char a[16], ac[20], stk[15], act[10];

void check()
{
    strcpy(ac, "REDUCE TO E ->");
    
    for (z = 0; z < c; z++)
    {
        if (stk[z] == 'i')
        {
            printf("%s i", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t", stk, a);
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E')
        {
            printf("%s E+E", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E')
        {
            printf("%s E*E", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t", stk, a);
            i = i - 2;
        }
    }

    for (z = 0; z < c - 2; z++)
    {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
        {
            printf("%s (E)", ac);
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t", stk, a);
            i = i - 2;
        }
    }
    return;
}

int main()
{
    printf("GRAMMAR is:\n");
    printf("E -> E+E\nE -> E*E\nE -> (E)\nE -> i\n");

    printf("Enter the string: ");
    scanf("%s", a);

    c = strlen(a);
    strcpy(act, "SHIFT");
    printf("\nstack\tinput\taction");
    printf("\n$\t%s$\t", a);

    for (i = 0, j = 0; j < c; i++, j++)
    {
        printf("%s", act);
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' ';
        printf("\n$%s\t%s$\t", stk, a);
        check();
    }

    check();

    if (stk[0] == 'E' && stk[1] == '\0')
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}
