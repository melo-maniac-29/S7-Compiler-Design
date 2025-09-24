    /*
        Program: Constant Folding in Intermediate Code Optimization
        Author : (Your Name)
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
        int flag;   // used to mark optimization
    } arr[10];

    int n;   // number of expressions

    // ----------------- MAIN FUNCTION -----------------
    void main()
    {
        input();      // take expressions as input
        constant();   // perform constant folding
        output();     // display optimized code
    }

    // ----------------- INPUT FUNCTION -----------------
    void input()
    {
        int i;
        printf("\nEnter the maximum number of expressions: ");
        scanf("%d", &n);

        printf("\nEnter the input in the form (op op1 op2 res):\n");
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
            if( (isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) || 
                (strcmp(arr[i].op, "=") == 0 && isdigit(arr[i].op1[0])) ) 
            {
                op1 = atoi(arr[i].op1);  // convert operand1 to integer
                op2 = atoi(arr[i].op2);  // convert operand2 to integer
                op  = arr[i].op[0];      // operator

                // Perform operation based on operator
                switch(op) {
                    case '+': res = op1 + op2; break;
                    case '-': res = op1 - op2; break;
                    case '*': res = op1 * op2; break;
                    case '/': res = op1 / op2; break;
                    case '=': res = op1;       break;
                }

                // Convert result back to string
                sprintf(res1, "%d", res);

                // Update all references of res with folded constant
                change(i, res1);

                arr[i].flag = 1;  // mark as optimized
            }
        }
    }

    // ----------------- CHANGE FUNCTION -----------------
    // Replace occurrences of arr[i].res with constant result
    void change(int p, char *res)
    {
        int i;
        for(i = 0; i < n; i++) {
            if(strcmp(arr[p].res, arr[i].op1) == 0)
                strcpy(arr[i].op1, res);
            else if(strcmp(arr[p].res, arr[i].op2) == 0)
                strcpy(arr[i].op2, res);
        }
        strcpy(arr[p].res, res);
    }

    // ----------------- OUTPUT FUNCTION -----------------
    void output()
    {
        int i;
        printf("\nOptimized Intermediate Code:\n");

        for(i = 0; i < n; i++) {
            if(arr[i].flag == 0) {   // print only non-optimized expressions
                printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
            }
        }
    }