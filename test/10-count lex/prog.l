%{
#include<stdio.h> 
int space=0,line=1,word=0,c=0; 
%}

%%
[" "]* {space++;}
["\n"]* {line++;}
[a-zA-Z0-9]+ {word++,c=c+yyleng;} 
%%

int yywrap(){
    return 1;
}

int main(){
    yyin=fopen("input.txt","r");
    yylex();
    printf("%d spaces %d lines %d words and %d characters",space,line,word,c);
    fclose(yyin);
}


/*
PS C:\Users\allen\OneDrive\Desktop\test\10-count lex> win_flex .\prog.l
PS C:\Users\allen\OneDrive\Desktop\test\10-count lex> gcc .\lex.yy.c
PS C:\Users\allen\OneDrive\Desktop\test\10-count lex> .\a.exe
3 spaces 1 lines 4 words and 13 characters
PS C:\Users\allen\OneDrive\Desktop\test\10-count lex> 
*/