%{
#include<stdio.h>
int vowels,consonant;
%}

%%
[aeiouAEIOU] {vowels++;}
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z] {consonant++;}
%%

int yywrap(){
    return 1;
}

int main(){
    yyin=fopen("input.txt","r");
    yylex();
    printf("%d vowels and %d consonants",vowels,consonant);
    fclose(yyin);
    return 0;
}


/*
PS C:\Users\allen\OneDrive\Desktop\test\11-count v,c> gcc .\lex.yy.c
PS C:\Users\allen\OneDrive\Desktop\test\11-count v,c> .\a.exe
1 vowels and 5 consonants
PS C:\Users\allen\OneDrive\Desktop\test\11-count v,c> 
*/