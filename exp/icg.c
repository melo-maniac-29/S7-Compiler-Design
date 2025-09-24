/*
    Program: Intermediate Code Generation
    Author : (Your Name)
    Purpose: To generate intermediate code for arithmetic expressions.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Global variables
int i = 1, j = 0, n = 0, tempch = 90;   // tempch = 'Z'
char str[100], left[15], right[15];

// Structure to store operator and position
struct expf {
    int pos;
    char op;
} k[15];

// Function declarations
void findopr();
void explore();
void fleft(int);
void fright(int);

// ----------------- MAIN FUNCTION -----------------
void main()
{
    printf("INTERMEDIATE CODE GENERATION\n");
    printf("Enter the expression: ");
    scanf("%s", str);

    printf("The intermediate code:\t\tExpression\n");

    findopr();   // find operators and store them
    explore();   // generate intermediate code

    printf("\n");
}

// ----------------- FIND OPERATORS -----------------
void findopr()
{
    // Searching operators in order of precedence
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == ':') {
            k[j].pos = i;
            k[j++].op = ':';
        }
    }

    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '/') {
            k[j].pos = i;
            k[j++].op = '/';
        }
    }

    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '*') {
            k[j].pos = i;
            k[j++].op = '*';
        }
    }

    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '+') {
            k[j].pos = i;
            k[j++].op = '+';
        }
    }

    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '-') {
            k[j].pos = i;
            k[j++].op = '-';
        }
    }
}

// ----------------- EXPLORE & GENERATE CODE -----------------
void explore()
{
    i = 1;

    while(k[i].op != '\0') 
    {
        fleft(k[i].pos);   // find left operand
        fright(k[i].pos);  // find right operand

        // Replace operator position with temporary variable
        str[k[i].pos] = tempch--;

        // Print intermediate code
        printf("\t%c := %s %c %s\t\t", str[k[i].pos], left, k[i].op, right);

        // Print updated expression
        for(j=0; j < strlen(str); j++) {
            if(str[j] != '$')
                printf("%c", str[j]);
        }
        printf("\n");
        i++;
    }

    // Final step if single operand remains
    fright(-1);
    if(n == 0) {
        fleft(strlen(str));
        printf("\t%s := %s\n", right, left);
        exit(0);
    }

    printf("\t%s := %c\n", right, str[k[--i].pos]);
}

// ----------------- FIND LEFT OPERAND -----------------
void fleft(int x)
{
    int w = 0, flag = 0;
    x--;

    while(x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '-' &&
          str[x] != '/' && str[x] != '\0' && str[x] != ':' )
    {
        if(str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
}

// ----------------- FIND RIGHT OPERAND -----------------
void fright(int x)
{
    int w = 0, flag = 0;
    x++;

    while(str[x] != '+' && str[x] != '*' && str[x] != '-' &&
          str[x] != '/' && str[x] != '\0' && str[x] != ':' )
    {
        if(str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
    printf("\n");
}