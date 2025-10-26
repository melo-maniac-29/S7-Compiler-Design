    /*
    Program: Deterministic Finite Automaton (DFA) Simulator
    Purpose: To simulate a DFA and test if input strings are accepted or rejected
    Input: DFA definition (states, alphabet, transitions, final states) and test strings
    Output: Acceptance or rejection of input strings based on DFA simulation
*/

#include <stdio.h>

void main()
{
    // Variable declarations
    int state[10];      // Array to store state numbers
    int str[10];        // Array to store input string symbols
    int input[10];      // Array to store input alphabet symbols
    char ch;            // Character variable (not used)
    int x[20];          // Transition table stored as 1D array
    
    // Control variables
    int s;              // Number of states
    int n;              // Number of input symbols (alphabet size)
    int k = 0;          // Index for transition table
    int j, a, i, l, t;  // Loop counters and temporary variables
    int q = 0;          // Current state index
    int fs;             // Final state number
    int b;              // Temporary variable for transitions
    int nxt;            // Next state after transition
    int z;              // Continue/exit flag
        // PHASE 1: DFA DEFINITION - Get states information
        printf("Enter the no of states\n");
        scanf("%d", &s);  // Read total number of states
        
        printf("enter the no of inputs\n");
        scanf("%d", &n);  // Read alphabet size (number of input symbols)
        
        // Input each state and identify final states
        for (i = 0; i < s; i++)
        {
            printf("Enter the state\n");
            scanf("%d", &state[i]);  // Read state number
            
            printf("is it final state?... .y..1/n..0\n");
            scanf("%d", &a);  // Check if this state is final (1=yes, 0=no)
            
            if (a == 1)
                fs = state[i];  // Store final state number (assumes only one final state)
        }
        // PHASE 2: INPUT ALPHABET - Define the input symbols
        printf("Enter the inputs\n");
        for (i = 0; i < n; i++)
            scanf("%d", &input[i]);  // Read each symbol of the alphabet
        
        // PHASE 3: TRANSITION TABLE - Define state transitions
        printf("Transition state\n");
        for (i = 0; i < s; i++)  // For each state
        {
            for (j = 0; j < n; j++)  // For each input symbol
            {
                // Display transition format: δ(current_state, input_symbol) = next_state
                printf("(q%d,%d)=q", state[i], input[j]);
                scanf("%d", &b);  // Read the next state
                
                // Store transition in 1D array using formula: x[state_index * alphabet_size + symbol_index]
                x[k] = b;
                k++;  // Move to next position in transition table
            }
        }
        // PHASE 4: STRING TESTING LOOP - Test multiple input strings
        do
        {
            // Get input string to test
            printf("Enter the length of the string\n");
            scanf("%d", &l);  // Read string length
            
            printf("Enter the input string\n");
            q = 0;  // Start from first state (index 0)
            
            // Read the input string symbols
            for (i = 0; i < l; i++)
            {
                scanf("%d", &str[i]);  // Read each symbol of the test string
            }
            
            // DFA SIMULATION: Process each symbol of the input string
            for (i = 0; i < l; i++)
            {
                t = 0;  // Start checking from first alphabet symbol
                
                // Find which alphabet symbol matches current input symbol
                do
                {
                    if (str[i] == input[t])  // If current string symbol matches alphabet symbol
                    {
                        // TRANSITION: Get next state from transition table
                        // Formula: x[current_state_index * alphabet_size + symbol_index]
                        nxt = x[n * q + t];
                        
                        // Find the index of the next state in state array
                        for (j = 0; j < s; j++)
                        {
                            if (nxt == state[j])
                                q = j;  // Update current state index
                        }
                        t++;  // Move to next alphabet symbol
                    }
                    else
                        t++;  // Try next alphabet symbol
                } while (t != n);  // Continue until all alphabet symbols checked
            }
            
            // ACCEPTANCE CHECK: Determine if string is accepted
            if (nxt == fs)
                printf("\n string is accepted\n");  // Final state reached
            else
                printf("\nstring is not accepted\n");  // Not in final state
            
            // Ask user if they want to test another string
            printf("do you want to continue..if yes press 1 else 0\n");
            scanf("%d", &z);
            
        } while (z != 0);  // Continue until user enters 0
}

/*
    DFA SIMULATION ALGORITHM:
    1. Define DFA components: Q (states), Σ (alphabet), δ (transitions), q0 (start), F (final)
    2. For each input string:
       a. Start from initial state q0
       b. For each symbol in string:
          - Find matching alphabet symbol
          - Look up transition: δ(current_state, symbol) = next_state
          - Move to next_state
       c. Check if final state reached after processing entire string
       d. Accept if in final state, reject otherwise
    
    TRANSITION TABLE STORAGE:
    - 1D array x[] stores transitions
    - Index formula: x[state_index * alphabet_size + symbol_index]
    - Example: For state 1, symbol 0 in alphabet size 2: x[1*2 + 0] = x[2]
*/
