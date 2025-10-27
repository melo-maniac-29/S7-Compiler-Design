/*
    Program: Constant Folding and Propagation in Intermediate Code Optimization
    Purpose: To evaluate constant expressions at compile time and propagate results
    
    Optimization Techniques Implemented:
    1. Constant Folding: Evaluate expressions with constant operands (e.g., 3+5 → 8)
    2. Constant Propagation: Replace variables with their constant values
    3. Copy Propagation: Handle assignment statements (e.g., t1 = 5)
    
    Three-Address Code Format:
    - operator operand1 operand2 result
    - Examples: + 3 5 t1, = 10 _ t2, * t1 t2 t3
    
    Algorithm:
    1. Read intermediate code expressions
    2. Identify expressions with constant operands
    3. Evaluate constant expressions and propagate results
    4. Display optimized code with constants substituted
    
    Input: Three-address intermediate code statements
    Output: Optimized intermediate code with constant folding applied
*/

#include <stdio.h>   // For input/output operations
#include <string.h>  // For string manipulation functions
#include <ctype.h>   // For character classification (isdigit)
#include <stdlib.h>  // For atoi, sprintf functions

// Function Declarations
void input();                    // Read intermediate code expressions
void output();                   // Display optimized code
void change(int p, char *res);   // Propagate constants to subsequent expressions
void constant();                 // Perform constant folding optimization

/*
    Structure: exprf (Expression Format)
    Purpose: Represents a three-address code instruction
    
    Fields:
    - op[2]: Operator (+, -, *, /, =)
    - op1[5]: First operand (variable name or constant)
    - op2[5]: Second operand (variable name or constant)
    - res[5]: Result variable name
    - flag: Optimization flag (0 = not folded, 1 = folded)
*/
struct exprf {
    char op[2];      // Operator: +, -, *, /, =
    char op1[5];     // First operand (left operand)
    char op2[5];     // Second operand (right operand)
    char res[5];     // Result variable
    int flag;        // Folding flag: 0=original, 1=constant folded
} arr[10];           // Array to store up to 10 expressions

int n;   // Total number of expressions in intermediate code

/*
    Main Function: Controls the constant folding optimization process
    
    Algorithm Flow:
    1. Input Phase: Read intermediate code expressions
    2. Optimization Phase: Perform constant folding and propagation
    3. Output Phase: Display optimized intermediate code
    
    The optimization is performed in-place on the expression array
*/
int main()
{
    input();      // Phase 1: Read intermediate code expressions from user
    constant();   // Phase 2: Apply constant folding optimization
    output();     // Phase 3: Display optimized intermediate code
    return 0;     // Successful program termination
}

/*
    Function: input()
    Purpose: Read intermediate code expressions from user
    
    Input Format: operator operand1 operand2 result
    Examples:
    - + 3 5 t1      (t1 = 3 + 5)
    - = 10 _ t2     (t2 = 10, assignment)
    - * t1 t2 t3    (t3 = t1 * t2)
    - / 20 4 t4     (t4 = 20 / 4)
    
    Note: For assignment operations, second operand is typically "_" (dummy)
*/
void input()
{
    int i;
    
    // Get number of expressions to process
    printf("\nEnter the maximum number of expressions: ");
    scanf("%d", &n);

    // Display input format and example
    printf("\nEnter the input in the form (op op1 op2 res):\n");
    printf("Example: + 3 2 t1\n");
    
    // Read each expression in three-address code format
    for(i = 0; i < n; i++) {
        scanf("%s", arr[i].op);     // Read operator (+, -, *, /, =)
        scanf("%s", arr[i].op1);    // Read first operand
        scanf("%s", arr[i].op2);    // Read second operand
        scanf("%s", arr[i].res);    // Read result variable
        arr[i].flag = 0;            // Initialize optimization flag (not folded yet)
    }
}

/*
    Function: constant()
    Purpose: Perform constant folding optimization on intermediate code
    
    Optimization Cases:
    1. Binary Operations with Constants: Both operands are numeric constants
    2. Assignment Operations: Constant assignment to variable
    
    Algorithm:
    1. Scan each expression for constant operands
    2. If both operands are constants, evaluate the operation
    3. Propagate the result constant to subsequent expressions
    4. Mark expression as folded
    
    Example Transformations:
    - + 3 5 t1 → t1 gets value 8, propagated to other expressions
    - = 10 _ t2 → t2 gets value 10, propagated to other expressions
*/
void constant()
{
    int i, op1, op2, res;  // Working variables for computation
    char op, res1[5];      // Operator and result string

    // Process each expression for constant folding opportunities
    for(i = 0; i < n; i++) {
        
        // CASE 1: Binary Operations with Constant Operands
        // Check if both operands are numeric constants (digits)
        if(isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])) 
        {
            // Convert string operands to integers for computation
            op1 = atoi(arr[i].op1);  // First operand as integer
            op2 = atoi(arr[i].op2);  // Second operand as integer
            op  = arr[i].op[0];      // Extract operator character

            // Perform arithmetic operation based on operator
            switch(op) {
                case '+': 
                    res = op1 + op2;     // Addition
                    break;
                case '-': 
                    res = op1 - op2;     // Subtraction
                    break;
                case '*': 
                    res = op1 * op2;     // Multiplication
                    break;
                case '/': 
                    // Division with zero-check
                    if(op2 == 0) {
                        printf("Error: Division by zero at expression %d\n", i);
                        continue;  // Skip this expression
                    }
                    res = op1 / op2;     // Integer division
                    break;
                default:
                    continue;  // Skip unknown operators
            }

            // Convert computed result back to string format
            sprintf(res1, "%d", res);

            // Propagate the constant result to subsequent expressions
            change(i, res1);

            arr[i].flag = 1;  // Mark this expression as constant folded
        }
        
        // CASE 2: Assignment Operations with Constants
        // Handle constant assignments like "= 10 _ t2"
        else if(strcmp(arr[i].op, "=") == 0 && isdigit(arr[i].op1[0])) 
        {
            // Copy the constant value for propagation
            strcpy(res1, arr[i].op1);
            
            // Propagate the constant to subsequent expressions
            change(i, res1);
            
            arr[i].flag = 1;  // Mark as folded
        }
        
        // CASE 3: Other expressions remain unchanged
        // Variables, non-constant expressions are not folded
    }
}

/*
    Function: change()
    Purpose: Propagate constant values to subsequent expressions
    Parameters: 
    - p: Index of expression that was folded
    - res: Constant value to propagate
    
    Constant Propagation Algorithm:
    1. Find all subsequent expressions that use the folded variable
    2. Replace variable references with the constant value
    3. This enables further constant folding in later passes
    
    Example:
    If t1 = 8 (from folding 3+5), then:
    - Expression "* t1 2 t3" becomes "* 8 2 t3"
    - Expression "+ t1 t2 t4" becomes "+ 8 t2 t4"
    
    Note: Only propagates forward (to expressions with higher indices)
    This maintains the sequential nature of three-address code
*/
void change(int p, char *res)
{
    int i;
    
    // Scan all expressions that come AFTER the current folded expression
    // This ensures proper sequential execution order is maintained
    for(i = p + 1; i < n; i++) {
        
        // Check if first operand matches the folded variable
        if(strcmp(arr[p].res, arr[i].op1) == 0)
            strcpy(arr[i].op1, res);  // Replace with constant value
        
        // Check if second operand matches the folded variable
        if(strcmp(arr[p].res, arr[i].op2) == 0)
            strcpy(arr[i].op2, res);  // Replace with constant value
    }
}

/*
    Function: output()
    Purpose: Display the final optimized three-address code
    
    Output Format: operator operand1 operand2 result
    
    Example Output:
    Original:       After Optimization:
    + 3 5 t1        + 8 _ t1 (3+5 folded to 8)
    * t1 2 t2       * 8 2 t2 (t1 propagated to 8)
    - t2 1 t3       - 16 1 t3 (t2 propagated to 16)
    
    The output shows how constant folding and propagation
    have simplified the intermediate code by:
    1. Evaluating constant expressions at compile time
    2. Replacing variables with their constant values
    3. Reducing runtime computation overhead
*/
void output()
{
    int i;
    printf("\nOptimized Intermediate Code:\n");
    printf("============================\n");

    for(i = 0; i < n; i++) {
        // Print all expressions (folded ones now have constant operands)
        printf("%s %s %s %s\n", arr[i].op, arr[i].op1, arr[i].op2, arr[i].res);
    }
    
    printf("============================\n");
    printf("Note: Constants have been folded and propagated for optimization\n");
}