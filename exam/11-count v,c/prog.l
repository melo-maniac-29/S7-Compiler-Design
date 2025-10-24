%{
#include <stdio.h>
int vowel_count = 0;
int const_count = 0;
%}

%%

[aeiouAEIOU]                { vowel_count++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] { const_count++; }
.|\n                        ;   // Ignore others

%%

int yywrap() { return 1; }

int main() {
    yyin = fopen("input.txt", "r");
    if (!yyin) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    yylex();
    printf("\nTotal Vowels: %d\n", vowel_count);
    printf("Total Consonants: %d\n", const_count);
    fclose(yyin);
    return 0;
}


/*
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\11-lex> .\a.exe

Total Vowels: 11
Total Consonants: 15
*/