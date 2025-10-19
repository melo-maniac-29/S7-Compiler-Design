%{
#include <stdio.h>
int c=0,w=0,line=1,space=0;
%}
%%
[" "]* {space++;}
["\n"]* {line++;}
[a-zA-Z0-9]+ {w++,c=c+yyleng;}
%%
int yywrap(){
    return 1;
}
int main(){
    yyin=fopen("input.txt","r");
    yylex();
    printf("Total Characters: %d\n", c);
    printf("Total Words: %d\n", w);
    printf("Total Lines: %d\n", line);
    printf("Total Spaces: %d\n", space);
    fclose(yyin);
    return 0;
}


/*
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\11-lex> win_flex .\11-lex.l
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\11-lex> gcc .\lex.yy.c
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\11-lex> .\a.exe
Total Characters: 20
Total Words: 6
Total Lines: 2
Total Spaces: 4
*/