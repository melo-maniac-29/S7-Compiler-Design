#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("Enter number of 3-address instructions: ");
    scanf("%d", &n);

    char op[5], arg1[10], arg2[10], res[10];

    printf("Enter instructions in form (op arg1 arg2 result):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s %s", op, arg1, arg2, res);
        printf("\nAssembly Code:\n");
        printf("MOV R0, %s\n", arg1);

        if (strcmp(op, "+") == 0)
            printf("ADD R0, %s\n", arg2);
        else if (strcmp(op, "-") == 0)
            printf("SUB R0, %s\n", arg2);
        else if (strcmp(op, "*") == 0)
            printf("MUL R0, %s\n", arg2);
        else if (strcmp(op, "/") == 0)
            printf("DIV R0, %s\n", arg2);

        printf("MOV %s, R0\n", res);
    }

    return 0;
}