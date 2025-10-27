#include<stdio.h>
#include<string.h>

int main(){

    int n;

    printf("enter how many number of expressions to convert");
    scanf("%d",&n);

    char op[20],op1[20],op2[20],res[20];

    for(int i=0;i<n;i++){
        printf("enter the expression in format op arg1 arg2 res\n");
        scanf("%s%s%s%s",op,op1,op2,res);

        printf("assembly code\n");

        printf("MOV R0,%s\n",op1);

        if(strcmp(op,"+")==0){
            printf("ADD R0,%s\n",op2);
        }else if(strcmp(op,"-")==0){
            printf("SUB R0,%s\n",op2);
        }else if(strcmp(op,"*")==0){
            printf("MUL R0,%s\n",op2);
        }else if(strcmp(op,"/")==0){
            printf("DIV R0,%s\n",op2);
        }

        printf("MOV %s,R0\n",res);


    }

}


/*
PS C:\Users\allen\OneDrive\Desktop\test\9-backend> gcc .\prog.c
PS C:\Users\allen\OneDrive\Desktop\test\9-backend> .\a.exe
enter how many number of expressions to convert3
enter the expression in format op arg1 arg2 res
+ 3 4 t1
assembly code
MOV R0,3
ADD R0,4
MOV t1,R0
enter the expression in format op arg1 arg2 res
* 4 5 t2
assembly code
MOV R0,4
MUL R0,5
MOV t2,R0
enter the expression in format op arg1 arg2 res
*/