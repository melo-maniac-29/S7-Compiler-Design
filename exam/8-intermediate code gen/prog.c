/*
    Program: Intermediate Code Generation for Arithmetic Expressions
    Purpose: Convert infix arithmetic expressions into three-address code
    
    Three-Address Code Format: result := operand1 operator operand2
    
    Algorithm Overview:
    1. Parse input expression and identify operators by precedence
    2. For each operator (highest to lowest precedence):
       - Extract left and right operands
       - Generate temporary variable for result
       - Create three-address code statement
    3. Replace processed parts with temporary variables
    4. Continue until entire expression is converted
    
    Operator Precedence (highest to lowest):
    1. Division (/) and Multiplication (*)
    2. Addition (+) and Subtraction (-)
    3. Assignment (=)
    
    Example:
    Input: a+b*c-d
    Output:
    Z := b * c       (a+Z-d)
    Y := a + Z       (Y-d)
    X := Y - d       (X)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Global variables for expression processing
int i = 0, j = 0, n = 0, tempch = 90;   // tempch starts at 'Z' for temp variables
char str[100], left[15], right[15];     // Expression string and operand buffers

/*
    Structure: expf
    Purpose: Store operator information for precedence-based processing
    Members:
    - pos: Position of operator in the expression string
    - op: The operator character (+, -, *, /, =)
    
    This array maintains operators in order of their precedence
    for systematic intermediate code generation
*/
struct expf {
    int pos;    // Position index in expression
    char op;    // Operator character
} k[15];        // Array to store up to 15 operators

// Function declarations with purposes
void findopr();         // Find and sort operators by precedence
void explore();         // Generate three-address code statements
void fleft(int);        // Extract left operand of an operator
void fright(int);       // Extract right operand of an operator
void reverse(char*);    // Reverse a string (for left operand correction)

/*
    Function: main()
    Purpose: Control the intermediate code generation process
    
    Process Flow:
    1. Get arithmetic expression from user
    2. Parse operators by precedence using findopr()
    3. Generate three-address code using explore()
    4. Display results in tabular format
    
    Example Execution:
    Input: a+b*c
    Output:
    Z := b * c       a+Z
    Y := a + Z       Y
*/
int main()
{
    // Program header
    printf("INTERMEDIATE CODE GENERATION\n");
    printf("============================\n");
    printf("Enter the expression: ");
    scanf("%s", str);

    // Display output headers
    printf("\nThe intermediate code:\t\tExpression\n");
    printf("=====================\t\t==========\n");

    // Step 1: Find all operators and sort by precedence
    findopr();   
    
    // Step 2: Generate three-address code statements
    explore();   

    printf("\n");
    return 0;
}

/*
    Function: findopr()
    Purpose: Identify and store operators in precedence order
    
    Operator Precedence Strategy:
    - Higher precedence operators are processed first
    - This ensures correct mathematical evaluation order
    - Operators are stored in k[] array with their positions
    
    Precedence Levels:
    1. Division (/) - Highest precedence
    2. Multiplication (*)
    3. Addition (+)
    4. Subtraction (-)
    5. Assignment (=) - Lowest precedence
    
    Example: For "a+b*c-d"
    Stored order: *, +, - (positions and operators)
    This ensures b*c is computed before addition/subtraction
*/
void findopr()
{
    j = 0;  // Initialize operator counter
    
    // PRECEDENCE LEVEL 1: Division operator (highest)
    // Process all divisions first for correct mathematical order
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '/') {
            k[j].pos = i;      // Store position in expression
            k[j++].op = '/';   // Store operator and increment counter
        }
    }

    // PRECEDENCE LEVEL 2: Multiplication operator
    // Process after division, before addition/subtraction
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '*') {
            k[j].pos = i;
            k[j++].op = '*';
        }
    }

    // PRECEDENCE LEVEL 3: Addition operator
    // Lower precedence than multiplication/division
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '+') {
            k[j].pos = i;
            k[j++].op = '+';
        }
    }

    // PRECEDENCE LEVEL 4: Subtraction operator
    // Same precedence as addition, processed left to right
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '-') {
            k[j].pos = i;
            k[j++].op = '-';
        }
    }
    
    // PRECEDENCE LEVEL 5: Assignment operator (lowest)
    // Processed last, after all arithmetic operations
    for(i=0; str[i] != '\0'; i++) {
        if(str[i] == '=') {
            k[j].pos = i;
            k[j++].op = '=';
        }
    }
}

/*
    Function: explore()
    Purpose: Generate three-address code statements for each operator
    
    Three-Address Code Generation Process:
    1. For each operator (in precedence order):
       - Extract left operand using fleft()
       - Extract right operand using fright()
       - Create temporary variable (Z, Y, X, ...)
       - Generate statement: temp := left op right
       - Replace processed part with temporary variable
    
    Example for "a+b*c":
    Step 1: Process * (highest precedence)
           Z := b * c        Expression becomes: a+Z
    Step 2: Process +
           Y := a + Z        Expression becomes: Y
    
    Temporary Variable Generation:
    - Starts with 'Z' (ASCII 90) and decrements
    - Creates unique names: Z, Y, X, W, V, ...
*/
void explore()
{
    i = 0;  // Start with first operator in precedence order

    // Process each operator to generate three-address code
    while(i < j && k[i].op != '\0')
    {
        // Extract operands for current operator
        fleft(k[i].pos);   // Find left operand (before operator)
        fright(k[i].pos);  // Find right operand (after operator)

        // Generate new temporary variable (Z, Y, X, ...)
        str[k[i].pos] = tempch--;  // Replace operator with temp variable

        // Output three-address code statement
        printf("\t%c := %s %c %s\t\t", str[k[i].pos], left, k[i].op, right);

        // Show the simplified expression after this step
        for(n=0; n < strlen(str); n++) {
            if(str[n] != '$')  // Skip marked positions
                printf("%c", str[n]);
        }
        printf("\n");
        
        i++;  // Move to next operator
    }
}

/*
    Function: fleft()
    Purpose: Extract the left operand of an operator
    Parameter: x - position of the operator in the expression
    
    Left Operand Extraction Algorithm:
    1. Start from position just before the operator (x-1)
    2. Move backwards until hitting another operator or string boundary
    3. Collect characters that form the left operand
    4. Mark collected positions with '$' to avoid reprocessing
    5. Reverse the result (since we read backwards)
    
    Example: For "a+b*c" when processing '*' at position 3:
    - Start at position 2 ('b')
    - Read backwards: 'b' 
    - Stop at '+' (position 1)
    - Left operand = "b"
    
    Termination Conditions:
    - Reached beginning of string (x == -1)
    - Hit another operator (+, -, *, /, =)
    - Hit already processed position ($)
*/
void fleft(int x)
{
    int w = 0, flag = 0;  // w: buffer index, flag: first character marker
    x--;  // Move to position just before the operator

    // Scan backwards to find the complete left operand
    while(x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '-' &&
          str[x] != '/' && str[x] != '=' && str[x] != '$')
    {
        if(flag == 0) {
            left[w++] = str[x];    // Store character in left operand buffer
            left[w] = '\0';        // Null terminate
            str[x] = '$';          // Mark position as processed
            flag = 1;              // Mark that we found the operand
        }
        x--;  // Continue moving backwards
    }
    
    // Reverse the left operand since we read it backwards
    // Example: if we read "cba" backwards, reverse to get "abc"
    reverse(left);
}

/*
    Function: reverse()
    Purpose: Reverse a string in-place
    Parameter: str - string to be reversed
    
    Why Reversal is Needed:
    - fleft() reads characters backwards from operator position
    - This gives us operand in reverse order
    - We need to reverse it back to get correct operand
    
    Algorithm:
    1. Find string length
    2. Swap characters from both ends moving inward
    3. Stop when we reach the middle
    
    Example:
    Input: "cba" (read backwards)
    Output: "abc" (correct operand)
    
    Time Complexity: O(n/2) where n is string length
*/
void reverse(char *str)
{
    int len = strlen(str);  // Get string length
    int i;
    char temp;              // Temporary variable for swapping
    
    // Swap characters from both ends moving towards center
    for(i = 0; i < len/2; i++) {
        temp = str[i];                    // Store left character
        str[i] = str[len-i-1];           // Move right to left position
        str[len-i-1] = temp;             // Move left to right position
    }
}

/*
    Function: fright()
    Purpose: Extract the right operand of an operator
    Parameter: x - position of the operator in the expression
    
    Right Operand Extraction Algorithm:
    1. Start from position just after the operator (x+1)
    2. Move forward until hitting another operator or string end
    3. Collect characters that form the right operand
    4. Mark collected positions with '$' to avoid reprocessing
    5. No reversal needed (reading forward)
    
    Example: For "a+b*c" when processing '+' at position 1:
    - Start at position 2 ('b')
    - Read forward: 'b'
    - Stop at '*' (position 3)
    - Right operand = "b"
    
    Example: For "a+b*c" when processing '*' at position 3:
    - Start at position 4 ('c')
    - Read forward: 'c'
    - Stop at string end
    - Right operand = "c"
    
    Termination Conditions:
    - Reached end of string
    - Hit another operator (+, -, *, /, =)
    - Hit already processed position ($)
*/
void fright(int x)
{
    int w = 0, flag = 0;  // w: buffer index, flag: first character marker
    x++;  // Move to position just after the operator

    // Scan forward to find the complete right operand
    while(x < strlen(str) && str[x] != '+' && str[x] != '*' && 
          str[x] != '-' && str[x] != '/' && str[x] != '=' && str[x] != '$')
    {
        if(flag == 0) {
            right[w++] = str[x];   // Store character in right operand buffer
            right[w] = '\0';       // Null terminate
            str[x] = '$';          // Mark position as processed
            flag = 1;              // Mark that we found the operand
        }
        x++;  // Continue moving forward
    }
    
    // No reversal needed since we read forward
    // Right operand is already in correct order
}