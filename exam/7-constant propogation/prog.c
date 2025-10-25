/*
    Program: Constant Folding in Intermediate Code Optimization
    Purpose: To evaluate constant expressions at compile time
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function declarations
void input();
void output();
void change(int p, char *res);
void constant();

// Structure for storing expressions
struct exprf {
    char op[2], op1[5], op2[5], res[5];
    int flag;   // used to mark if this expression was folded
} arr[10];

int n;   // number of expressions

// ----------------- MAIN FUNCTION -----------------
int main()
{
    input();      // take expressions as input
    constant();   // perform constant folding
    output();     // display optimized code
    return 0;
}

// ----------------- INPUT FUNCTION -----------------
void input()
{
    int i;
    printf("\nEnter the maximum number of expressions: ");
    scanf("%d", &n);

    printf("\nEnter the input in the form (op op1 op2 res):\n");
    printf("Example: + 3 2 t1\n");
    for(i = 0; i < n; i++) {
        scanf("%s", arr[i].op);
        scanf("%s", arr[i].op1);
        scanf("%s", arr[i].op2);
        scanf("%s", arr[i].res);
        arr[i].flag = 0;   // initialize flag
    }
}

// ----------------- CONSTANT FOLDING FUNCTION -----------------
void constant()
{
    int i, op1, op2, res;
    char op, res1[5];

    for(i = 0; i < n; i++) {
        
        // Check if both operands are digits (constants)
        if(isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) 
        {
            op1 = atoi(arr[i].op1);  // convert operand1 to integer
            op2 = atoi(arr[i].op2);  // convert operand2 to integer
            op  = arr[i].op[0];      // operator

            // Perform operation based on operator
            switch(op) {
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': 
                    if(op2 == 0) {
                        printf("Error: Division by zero at expression %d\n", i);
                        continue;
                    }
                    res = op1 / op2; 
                    break;
                default:
                    continue;  // Skip unknown operators
            }

            // Convert result back to string
            sprintf(res1, "%d", res);

            // Update all references of res with folded constant
            change(i, res1);

            arr[i].flag = 1;  // mark as folded
        }
        // Handle assignment with constant
        else if(strcmp(arr[i].op, "=") == 0 && isdigit(arr[i].op1[0])) 
        {
            strcpy(res1, arr[i].op1);
            change(i, res1);
            arr[i].flag = 1;
        }
    }
}

// ----------------- CHANGE FUNCTION -----------------
// Replace occurrences of arr[p].res with constant result
void change(int p, char *res)
{
    int i;
    // Propagate to expressions that come AFTER the current one
    for(i = p + 1; i < n; i++) {
        if(strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, res);
        if(strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, res);
    }
}

// ----------------- OUTPUT FUNCTION -----------------
void output()
{
    int i;
    printf("\nOptimized Intermediate Code:\n");

    for(i = 0; i < n; i++) {
        // Print all expressions (folded ones now have constant operands)
        printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
}