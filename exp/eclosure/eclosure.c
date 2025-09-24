#include <stdio.h>
#include <string.h>

char states[20][20];     // list of states
char result[20][20];     // closure set
int added[20];           // to avoid duplicates
int n, res_count;

void add_state(char s[3]) {
    for (int i = 0; i < res_count; i++) {
        if (strcmp(result[i], s) == 0) return; // avoid duplicates
    }
    strcpy(result[res_count++], s);
}

// recursive function to find closure
void epsilon_closure(char state[3], char transitions[20][3][3], int tcount) {
    add_state(state);
    for (int i = 0; i < tcount; i++) {
        if (strcmp(transitions[i][0], state) == 0 && strcmp(transitions[i][1], "e") == 0) {
            epsilon_closure(transitions[i][2], transitions, tcount);
        }
    }
}

int main() {
    int tcount;
    char transitions[20][3][3]; // [from][input][to]

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter states: ");
    for (int i = 0; i < n; i++) scanf("%s", states[i]);

    printf("Enter number of transitions: ");
    scanf("%d", &tcount);
    printf("Enter transitions (from input to):\n");
    for (int i = 0; i < tcount; i++) {
        scanf("%s %s %s", transitions[i][0], transitions[i][1], transitions[i][2]);
    }

    // compute closure for each state
    for (int i = 0; i < n; i++) {
        res_count = 0;
        epsilon_closure(states[i], transitions, tcount);
        printf("Epsilon closure of %s = { ", states[i]);
        for (int j = 0; j < res_count; j++) printf("%s ", result[j]);
        printf("}\n");
    }
    return 0;
}
