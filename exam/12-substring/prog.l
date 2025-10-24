%{
#include <stdio.h>
int i;
%}

%%
[a-zA-Z]* {for(i=0;i<=yyleng;i++){
    if(yytext[i]=='a' && yytext[i+1]=='b' && yytext[i+2]=='c'){
        yytext[i]='A';
        yytext[i+1]='B';
        yytext[i+2]='C';
    }
}
{printf("%s",yytext);}}
%%

int yywrap(){
    return 1;
}

int main(){
    printf("enter the string:\n");
    yylex();
    return 0;
}


/*
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\12-substring> win_flex .\prog.l
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\12-substring> gcc .\lex.yy.c
PS C:\Users\allen\workspace\KTU-sem7-compilerdesign-programs-main\exam\12-substring> .\a.exe   
enter the string:
hi myself abc
hi myself ABC
*/