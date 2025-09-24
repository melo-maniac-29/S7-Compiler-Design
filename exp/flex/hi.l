%{
#include <stdio.h>
%}

%%
hello   { printf("Hello, World!\n"); }
.|\n    { /* ignore everything else */ }
%%
int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
