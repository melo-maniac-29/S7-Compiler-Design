/*
    Program: Epsilon Closure Calculator for Non-deterministic Finite Automaton (NFA)
    Purpose: To compute epsilon closures for all states in an NFA
    
    Epsilon Closure Definition:
    - The epsilon closure of a state is the set of all states reachable from that state
      using only epsilon (ε) transitions (transitions that don't consume any input)
    
    Input: 
    - States of the NFA
    - Transitions in format: from_state input_symbol to_state
    - Epsilon transitions are represented as "e"
    
    Output: Epsilon closure set for each state
    
    Algorithm: Uses recursive depth-first search to find all epsilon-reachable states
*/

#include <stdio.h>
#include <string.h>

// Global Data Structures
char states[20][20];     // Array to store all state names (up to 20 states, 20 chars each)
char result[20][20];     // Temporary array to store epsilon closure result for current state
int added[20];           // Flag array to track added states (currently unused but declared)
int n;                   // Total number of states in the NFA
int res_count;           // Count of states in current epsilon closure result

/*
    Function: add_state
    Purpose: Adds a state to the epsilon closure result set, avoiding duplicates
    Parameters: s[] - state name to be added
    Algorithm:
    1. Check if state already exists in result array
    2. If duplicate found, return without adding
    3. If new state, add to result array and increment counter
    Time Complexity: O(res_count) for duplicate checking
*/
void add_state(char s[3]) {
    // Linear search through current result set to check for duplicates
    for (int i = 0; i < res_count; i++) {
        if (strcmp(result[i], s) == 0) return; // State already exists, don't add
    }
    
    // Add new state to result set
    strcpy(result[res_count++], s);  // Copy state name and increment count
}

/*
    Function: epsilon_closure (Recursive)
    Purpose: Computes epsilon closure of a given state using depth-first search
    Parameters: 
    - state[] - current state being processed
    - transitions[][] - 3D array containing all transitions [transition_index][from/input/to][characters]
    - tcount - total number of transitions
    
    Algorithm:
    1. Add current state to closure set (base case)
    2. Find all epsilon transitions FROM current state
    3. Recursively compute closure for each reachable state
    4. Duplicate states are automatically handled by add_state()
    
    Transition Format: transitions[i][0] = from_state, transitions[i][1] = input_symbol, transitions[i][2] = to_state
*/
void epsilon_closure(char state[3], char transitions[20][3][3], int tcount) {
    // Step 1: Add current state to the closure set
    add_state(state);  // Every state is in its own epsilon closure
    
    // Step 2: Search for all epsilon transitions starting from current state
    for (int i = 0; i < tcount; i++) {
        // Check if this transition starts from current state AND is an epsilon transition
        if (strcmp(transitions[i][0], state) == 0 && strcmp(transitions[i][1], "e") == 0) {
            // Step 3: Recursively find epsilon closure of the destination state
            epsilon_closure(transitions[i][2], transitions, tcount);
        }
    }
}

/*
    Main Function: Controls the overall program flow
    Steps:
    1. Input NFA definition (states and transitions)
    2. Compute epsilon closure for each state
    3. Display results in set notation
*/
int main() {
    int tcount;                    // Number of transitions in the NFA
    char transitions[20][3][3];    // 3D array to store transitions
                                  // Format: [transition_index][0=from, 1=input, 2=to][character_position]

    // PHASE 1: INPUT NFA STATES
    printf("Enter number of states: ");
    scanf("%d", &n);              // Read total number of states
    
    printf("Enter states: ");
    for (int i = 0; i < n; i++) {
        scanf("%s", states[i]);    // Read each state name (e.g., q0, q1, q2)
    }

    // PHASE 2: INPUT NFA TRANSITIONS
    printf("Enter number of transitions: ");
    scanf("%d", &tcount);         // Read total number of transitions
    
    printf("Enter transitions (from input to):\n");
    for (int i = 0; i < tcount; i++) {
        // Read each transition in format: source_state input_symbol destination_state
        // Example: q0 e q1 (epsilon transition from q0 to q1)
        // Example: q0 a q2 (transition from q0 to q2 on input 'a')
        scanf("%s %s %s", transitions[i][0], transitions[i][1], transitions[i][2]);
    }

    // PHASE 3: COMPUTE AND DISPLAY EPSILON CLOSURES
    printf("\nEpsilon Closures:\n");
    for (int i = 0; i < n; i++) {
        // Reset result array for each state
        res_count = 0;            // Clear previous results
        
        // Compute epsilon closure for current state
        epsilon_closure(states[i], transitions, tcount);
        
        // Display result in mathematical set notation
        printf("Epsilon closure of %s = { ", states[i]);
        for (int j = 0; j < res_count; j++) {
            printf("%s ", result[j]);  // Print each state in closure
        }
        printf("}\n");
    }
    
    return 0;  // Successful program termination
}

/*
    PROGRAM EXECUTION EXAMPLE:
    
    Input:
    Enter number of states: 3
    Enter states: q0 q1 q2
    Enter number of transitions: 4
    Enter transitions (from input to):
    q0 e q1
    q1 e q2
    q0 a q1
    q2 b q0
    
    Output:
    Epsilon closure of q0 = { q0 q1 q2 }
    Epsilon closure of q1 = { q1 q2 }
    Epsilon closure of q2 = { q2 }
    
    EXPLANATION:
    - q0 can reach q1 via epsilon, and q1 can reach q2 via epsilon
    - Therefore, epsilon closure of q0 includes {q0, q1, q2}
    - q1 can reach q2 via epsilon, so epsilon closure of q1 is {q1, q2}
    - q2 has no outgoing epsilon transitions, so its closure is just {q2}
    
    ALGORITHM COMPLEXITY:
    - Time: O(n * t * d) where n=states, t=transitions, d=depth of epsilon chains
    - Space: O(n) for storing closure results
    
    APPLICATIONS:
    - NFA to DFA conversion (subset construction algorithm)
    - Regular expression to automaton conversion
    - Compiler design for handling epsilon moves in lexical analysis
*/
