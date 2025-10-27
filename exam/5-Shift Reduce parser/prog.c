/*
    Program: Shift Reduce Parser for Arithmetic Expressions
    Purpose: To parse arithmetic expressions using shift-reduce parsing technique
    
    Grammar Being Parsed:
    E → E + E    (Expression addition)
    E → E * E    (Expression multiplication) 
    E → ( E )    (Parenthesized expression)
    E → i        (Identifier)
    
    Parsing Algorithm: Bottom-up parsing using shift-reduce operations
    - SHIFT: Move input symbol onto stack
    - REDUCE: Replace handle (right-hand side of production) with left-hand side
    
    Handle: A substring of stack contents that matches RHS of some production
    
    Example: For input "i+i", parsing steps:
    1. SHIFT i → Stack: i
    2. REDUCE i to E → Stack: E  
    3. SHIFT + → Stack: E+
    4. SHIFT i → Stack: E+i
    5. REDUCE i to E → Stack: E+E
    6. REDUCE E+E to E → Stack: E (Accept)
    
    Input: Arithmetic expression with identifiers (i), +, *, ()
    Output: Parsing steps and Accept/Reject decision
*/

#include <stdio.h>   // For input/output operations
#include <stdlib.h>  // For standard library functions
#include <string.h>  // For string manipulation functions
#include <ctype.h>   // For character classification functions

// Global Variables
int z = 0;           // Loop counter for checking reductions
int i = 0;           // Stack index/pointer
int j = 0;           // Input index/pointer  
int c = 0;           // Length of input string

char a[16];          // Input string array
char ac[20];         // Action message string for REDUCE operations
char stk[15];        // Parser stack to store symbols
char act[10];        // Action string (SHIFT/REDUCE)

/*
    Function: check()
    Purpose: Scans the stack for handles and performs reductions
    
    Handle Detection: Searches for patterns that match grammar rule RHS
    Reduction Process: Replaces handle with corresponding LHS non-terminal
    
    Four Grammar Rules Checked (in order):
    1. E → i        (Reduce identifier to Expression)
    2. E → E + E    (Reduce addition to Expression)  
    3. E → E * E    (Reduce multiplication to Expression)
    4. E → ( E )    (Reduce parenthesized expression)
    
    Algorithm: Scan stack from left to right for each pattern
*/
void check()
{
    strcpy(ac, "REDUCE TO E ->");  // Set reduction message prefix
    
    // REDUCTION RULE 1: E → i (Identifier to Expression)
    for (z = 0; z < c; z++)
    {
        if (stk[z] == 'i')  // Found identifier on stack
        {
            printf("%s i", ac);     // Display reduction: E → i
            stk[z] = 'E';           // Replace 'i' with 'E'
            stk[z + 1] = '\0';      // Null-terminate string
            printf("\n$%s\t%s$\t", stk, a);  // Display updated stack and input
        }
    }

    // REDUCTION RULE 2: E → E + E (Addition Expression)
    for (z = 0; z < c - 2; z++)
    {
        // Check for pattern E+E on stack (3 consecutive symbols)
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E')
        {
            printf("%s E+E", ac);      // Display reduction: E → E+E
            stk[z] = 'E';              // Replace first symbol with 'E'
            stk[z + 1] = '\0';         // Clear second symbol  
            stk[z + 2] = '\0';         // Clear third symbol
            printf("\n$%s\t%s$\t", stk, a);  // Display updated stack and input
            i = i - 2;                 // Adjust stack pointer (reduced 3 to 1, so -2)
        }
    }

    // REDUCTION RULE 3: E → E * E (Multiplication Expression)
    for (z = 0; z < c - 2; z++)
    {
        // Check for pattern E*E on stack (3 consecutive symbols)
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E')
        {
            printf("%s E*E", ac);      // Display reduction: E → E*E
            stk[z] = 'E';              // Replace first symbol with 'E'
            stk[z + 1] = '\0';         // Clear second symbol
            stk[z + 2] = '\0';         // Clear third symbol  
            printf("\n$%s\t%s$\t", stk, a);  // Display updated stack and input
            i = i - 2;                 // Adjust stack pointer (reduced 3 to 1, so -2)
        }
    }

    // REDUCTION RULE 4: E → ( E ) (Parenthesized Expression)
    for (z = 0; z < c - 2; z++)
    {
        // Check for pattern (E) on stack (3 consecutive symbols)
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
        {
            printf("%s (E)", ac);      // Display reduction: E → (E)
            stk[z] = 'E';              // Replace first symbol with 'E'
            stk[z + 1] = '\0';         // Clear second symbol
            stk[z + 2] = '\0';         // Clear third symbol
            printf("\n$%s\t%s$\t", stk, a);  // Display updated stack and input
            i = i - 2;                 // Adjust stack pointer (reduced 3 to 1, so -2)
        }
    }
    return;  // End of check function
}

/*
    Main Function: Controls the shift-reduce parsing process
    
    Algorithm:
    1. Display grammar rules
    2. Read input string from user
    3. Initialize parsing table display
    4. Perform shift-reduce parsing loop
    5. Check final acceptance condition
    
    Parsing Table Format:
    stack | input | action
    Shows current state at each parsing step
*/
int main()
{
    // Step 1: Display the grammar being used
    printf("GRAMMAR is:\n");
    printf("E -> E+E\nE -> E*E\nE -> (E)\nE -> i\n");

    // Step 2: Get input string from user
    printf("Enter the string: ");
    scanf("%s", a);  // Read arithmetic expression

    // Step 3: Initialize parsing variables and display
    c = strlen(a);           // Store input length
    strcpy(act, "SHIFT");    // Initialize action to SHIFT
    
    // Display parsing table header
    printf("\nstack\tinput\taction");
    printf("\n$\t%s$\t", a);  // Initial state: empty stack, full input

    // Step 4: Main Shift-Reduce Parsing Loop
    for (i = 0, j = 0; j < c; i++, j++)
    {
        // SHIFT OPERATION: Move input symbol to stack
        printf("%s", act);           // Display current action (SHIFT)
        stk[i] = a[j];              // Move symbol from input to stack
        stk[i + 1] = '\0';          // Null-terminate stack string
        a[j] = ' ';                 // Mark input symbol as consumed (replace with space)
        
        // Display current parsing state
        printf("\n$%s\t%s$\t", stk, a);
        
        // REDUCE OPERATION: Check for handles and reduce if found
        check();  // Look for reduction opportunities after each shift
    }

    // Step 5: Final reduction check (in case no more input to shift)
    check();  // One final check for any remaining reductions

    // Step 6: Acceptance Test
    // Accept if stack contains only start symbol 'E' and nothing else
    if (stk[0] == 'E' && stk[1] == '\0')
        printf("Accepted\n");    // Successful parse: input belongs to grammar
    else
        printf("Rejected\n");    // Failed parse: input doesn't belong to grammar

    return 0;  // Program termination
}

/*
    SHIFT-REDUCE PARSING EXAMPLE: Input "i+i"
    
    Step | Stack | Input | Action
    -----|-------|-------|------------------
    0    | $     | i+i$  | Initial state
    1    | $i    | +i$   | SHIFT i
    2    | $E    | +i$   | REDUCE i to E
    3    | $E+   | i$    | SHIFT +  
    4    | $E+i  | $     | SHIFT i
    5    | $E+E  | $     | REDUCE i to E
    6    | $E    | $     | REDUCE E+E to E
    7    | Accept|       | Stack = E, Input consumed
    
    PARSING CONFLICTS:
    This implementation may have shift/reduce conflicts because:
    - Grammar is ambiguous (E → E+E, E → E*E)
    - No precedence rules defined
    - Always shifts before reducing when possible
    
    ALGORITHM PROPERTIES:
    - Bottom-up parsing (builds parse tree from leaves to root)
    - LR-style parsing without formal LR table
    - Time Complexity: O(n²) due to repeated stack scanning
    - Space Complexity: O(n) for stack storage
    
    IMPROVEMENTS NEEDED:
    - Operator precedence handling
    - Proper conflict resolution
    - More efficient handle detection
    - Error recovery mechanisms
*/
