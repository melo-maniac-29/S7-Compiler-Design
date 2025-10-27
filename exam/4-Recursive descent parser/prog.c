/*
    Program: Recursive Descent Parser for Arithmetic Expressions
    Purpose: To parse arithmetic expressions using recursive descent parsing technique
    
    Grammar Being Parsed:
    E  → T E'             (Expression = Term followed by Expression')
    E' → + T E' | ε       (Expression' = +Term Expression' or empty)
    T  → F T'             (Term = Factor followed by Term')
    T' → * F T' | ε       (Term' = *Factor Term' or empty)
    F  → ( E ) | id       (Factor = parenthesized expression or identifier)
    
    Where:
    - E represents Expression (handles addition)
    - T represents Term (handles multiplication) 
    - F represents Factor (handles parentheses and identifiers)
    - E' and T' handle left recursion elimination
    
    Operator Precedence: * (multiplication) has higher precedence than + (addition)
    Associativity: Both + and * are left-associative
    
    Input: Arithmetic expression string (e.g., "a+b*c", "(a+b)*c")
    Output: "Accepted" if expression follows grammar rules, "Rejected" otherwise
*/

#include <stdio.h>   // For input/output operations
#include <string.h>  // For strlen() function  
#include <stdlib.h>  // For standard library functions
#include <ctype.h>   // For isalpha(), isalnum() character checking functions

// Global Variables
char input[10];      // Input expression string (max 10 characters)
int i = 0;           // Current position/index in input string (global cursor)
int error = 0;       // Error flag: 0 = no error, 1 = syntax error detected

// Function Declarations (Recursive Descent Parser Functions)
void E();            // Parse Expression (E → T E')
void T();            // Parse Term (T → F T')  
void Eprime();       // Parse Expression' (E' → + T E' | ε)
void Tprime();       // Parse Term' (T' → * F T' | ε)
void F();            // Parse Factor (F → ( E ) | id)

/*
    Main Function: Entry point and controller of the parser
    Algorithm:
    1. Read input expression from user
    2. Start parsing from the top-level grammar rule (Expression)
    3. Check if entire input was consumed and no errors occurred
    4. Display result (Accepted/Rejected)
*/
int main()
{
    // Step 1: Get input expression from user
    printf("Enter an arithmetic expression: ");
    scanf("%s", input);  // Read expression as string (no spaces allowed)
    
    // Step 2: Initialize parsing from start symbol E (Expression)
    E();  // Begin recursive descent parsing
    
    // Step 3: Check parsing success conditions
    if((strlen(input) == i) && error == 0) {
        // Success conditions:
        // 1. All input consumed (i == length of input)
        // 2. No syntax errors detected (error == 0)
        printf("\nAccepted\n");
    }
    else {
        // Failure conditions:
        // 1. Input not fully consumed (extra characters remain)
        // 2. Syntax error detected during parsing
        printf("Rejected\n");
    }
    
    return 0;  // Program termination
}

/*
    Function: E() - Parse Expression
    Grammar Rule: E → T E'
    Purpose: Handles expressions with addition operations
    
    Algorithm:
    1. Parse a Term (T)
    2. Parse Expression' (E') to handle additional terms with + operator
    
    Example: For input "a+b+c"
    - T() parses "a"  
    - E'() parses "+b+c"
*/
void E()
{
    T();        // Parse first term (mandatory)
    Eprime();   // Parse remaining expression with + operators (optional)
}

/*
    Function: Eprime() - Parse Expression' (Expression Prime)
    Grammar Rule: E' → + T E' | ε (epsilon/empty)
    Purpose: Handles zero or more additions (eliminates left recursion)
    
    Algorithm:
    1. If current character is '+':
       - Consume the '+' operator
       - Parse next Term (T)
       - Recursively parse more additions (E')
    2. If not '+', do nothing (epsilon production)
    
    Left Recursion Elimination:
    Original: E → E + T | T
    Transformed: E → T E', E' → + T E' | ε
    
    Example: For "+b+c" after parsing "a"
    - Sees '+', consumes it, parses "b", recursively handles "+c"
*/
void Eprime()
{
    if(input[i] == '+')  // Check for addition operator
    {
        i++;         // Consume the '+' character
        T();         // Parse the next term after '+'
        Eprime();    // Recursively parse more additions (right recursion)
    }
    // If no '+' found, this represents epsilon (ε) production - do nothing
}

/*
    Function: T() - Parse Term
    Grammar Rule: T → F T'
    Purpose: Handles terms with multiplication operations (higher precedence than +)
    
    Algorithm:
    1. Parse a Factor (F)
    2. Parse Term' (T') to handle additional factors with * operator
    
    Precedence Handling:
    - Terms (multiplication) are parsed at a lower level than Expressions (addition)
    - This ensures * binds tighter than + (higher precedence)
    
    Example: For input "a*b" within "c+a*b"
    - F() parses "a"
    - T'() parses "*b"
*/
void T()
{
    F();        // Parse first factor (mandatory)
    Tprime();   // Parse remaining term with * operators (optional)
}

/*
    Function: Tprime() - Parse Term' (Term Prime)
    Grammar Rule: T' → * F T' | ε (epsilon/empty)
    Purpose: Handles zero or more multiplications (eliminates left recursion)
    
    Algorithm:
    1. If current character is '*':
       - Consume the '*' operator
       - Parse next Factor (F)
       - Recursively parse more multiplications (T')
    2. If not '*', do nothing (epsilon production)
    
    Precedence Implementation:
    - Multiplication is handled at Term level (lower in parse tree)
    - Addition is handled at Expression level (higher in parse tree)
    - This creates proper precedence: * before +
    
    Example: For "*b*c" after parsing "a"
    - Sees '*', consumes it, parses "b", recursively handles "*c"
*/
void Tprime()
{
    if(input[i] == '*')  // Check for multiplication operator
    {
        i++;         // Consume the '*' character
        F();         // Parse the next factor after '*'
        Tprime();    // Recursively parse more multiplications (right recursion)
    }
    // If no '*' found, this represents epsilon (ε) production - do nothing
}

/*
    Function: F() - Parse Factor
    Grammar Rule: F → ( E ) | id
    Purpose: Handles the basic building blocks of expressions
    
    Two Productions:
    1. F → ( E ): Parenthesized sub-expressions
    2. F → id: Identifiers (variable names)
    
    Algorithm:
    1. If '(' found: parse parenthesized expression
       - Consume '('
       - Recursively parse inner Expression (E)  
       - Expect and consume matching ')'
       - Set error flag if ')' missing
    
    2. If identifier found: parse identifier
       - First character must be letter or underscore
       - Subsequent characters can be letters, digits, or underscores
       - Consume entire identifier
    
    3. Otherwise: set error flag (invalid factor)
    
    Identifier Rules (C-style):
    - Must start with letter (a-z, A-Z) or underscore (_)
    - Can contain letters, digits (0-9), underscores
    - Examples: a, var1, _temp, myVariable
*/
void F()
{
    // CASE 1: Parenthesized Expression F → ( E )
    if(input[i] == '(')
    {
        i++;         // Consume opening parenthesis '('
        E();         // Recursively parse the inner expression
        
        // Check for matching closing parenthesis
        if(input[i] == ')')
            i++;     // Consume closing parenthesis ')'
        else
            error = 1;  // Set error: missing closing parenthesis
    }
    // CASE 2: Identifier F → id
    else if(isalpha(input[i]) || input[i] == '_')
    {
        i++;         // Consume first character of identifier
        
        // Continue consuming identifier characters
        while(isalnum(input[i]) || input[i] == '_')
            i++;     // Consume letters, digits, underscores
    }
    // CASE 3: Invalid Factor
    else
        error = 1;   // Set error: expected '(' or identifier
}

/*
    PARSING EXAMPLE: "a+b*c"
    
    Call Sequence:
    1. E() calls T() and Eprime()
    2. T() calls F() and Tprime()
    3. F() parses 'a' (identifier)
    4. Tprime() sees no '*', returns (epsilon)
    5. Eprime() sees '+', consumes it
    6. Eprime() calls T() for "b*c"
    7. T() calls F() and Tprime()
    8. F() parses 'b' (identifier)
    9. Tprime() sees '*', consumes it
    10. Tprime() calls F() for 'c'
    11. F() parses 'c' (identifier)
    12. All functions return, input fully consumed
    
    Parse Tree Structure:
           E
         /   \
        T     E'
        |    /|\
        F   + T  E'
        |     |   |
        a     F   ε
              |
              b*c...
    
    ALGORITHM PROPERTIES:
    - Time Complexity: O(n) where n is input length
    - Space Complexity: O(d) where d is maximum recursion depth
    - Handles operator precedence through grammar structure
    - Eliminates left recursion using right recursion
    - Predictive parsing (no backtracking needed)
*/
