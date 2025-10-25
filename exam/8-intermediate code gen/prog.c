/*
    Program: Intermediate Code Generation
    Purpose: To generate intermediate code for arithmetic expressions.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Global variables
int i = 0, j = 0, n = 0, tempch = 90;   // tempch = 'Z'
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
void reverse(char*);

// ----------------- MAIN FUNCTION -----------------
int main()
{
    printf("INTERMEDIATE CODE GENERATION\n");
    printf("Enter the expression: ");
    scanf("%s", str);

    printf("\nThe intermediate code:\t\tExpression\n");

    findopr();   // find operators and store them
    explore();   // generate intermediate code

    printf("\n");
    return 0;
}

// ----------------- FIND OPERATORS -----------------
void findopr()
{
    j = 0;
    
    // Searching operators in order of precedence (highest to lowest)
    // First: / and *
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

    // Then: + and -
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
    
    // Assignment operator (lowest precedence)
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '=') {
            k[j].pos = i;
            k[j++].op = '=';
        }
    }
}

// ----------------- EXPLORE & GENERATE CODE -----------------
void explore()
{
    i = 0;

    while(i < j && k[i].op != '\0')
    {
        fleft(k[i].pos);   // find left operand
        fright(k[i].pos);  // find right operand

        // Replace operator position with temporary variable
        str[k[i].pos] = tempch--;

        // Print intermediate code
        printf("\t%c := %s %c %s\t\t", str[k[i].pos], left, k[i].op, right);

        // Print updated expression
        for(n=0; n < strlen(str); n++) {
            if(str[n] != '$')
                printf("%c", str[n]);
        }
        printf("\n");
        i++;
    }
}

// ----------------- FIND LEFT OPERAND -----------------
void fleft(int x)
{
    int w = 0, flag = 0;
    x--;

    while(x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '-' &&
          str[x] != '/' && str[x] != '=' && str[x] != '$')
    {
        if(flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
    
    // Reverse the left operand (since we read backwards)
    reverse(left);
}

// ----------------- REVERSE STRING -----------------
void reverse(char *str)
{
    int len = strlen(str);
    int i;
    char temp;
    
    for(i = 0; i < len/2; i++) {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}

// ----------------- FIND RIGHT OPERAND -----------------
void fright(int x)
{
    int w = 0, flag = 0;
    x++;

    while(x < strlen(str) && str[x] != '+' && str[x] != '*' && 
          str[x] != '-' && str[x] != '/' && str[x] != '=' && str[x] != '$')
    {
        if(flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}