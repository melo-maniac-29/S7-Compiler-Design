/*
Grammar Being Parsed:
    E  → T E'             
    E' → + T E' | ε       
    T  → F T'             
    T' → * F T' | ε      
    F  → ( E ) | id       
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char input[10];
int error =0;
int i=0;

void E();
void Eprime();
void T();
void Tprime();
void F();

int main(){

    printf("enter the arithmetic expression : ");
    scanf("%s",input);

    E();

    if(strlen(input)==i && error==0){
        printf("\n Accepted\n");
    }else{
        printf("\nRejected\n");
    }

}

void E(){
    T();
    Eprime();
}

void Eprime(){
    if(input[i]=='+'){
        i++;
        T();
        Eprime();
    }
}

void T(){
    F();
    Tprime();
}

void Tprime(){
    if(input[i]=='*'){
        i++;
        F();
        Tprime();
    }
}

void F(){
    if(input[i]=='('){
        i++;
        E();
        if(input[i]==')'){
            i++;
        }else{
            error=1;
        }
    }else if(isalpha(input[i]) || input[i]=='_'){
        i++;
        while(isalnum(input[i]) || input[i]=='_'){
            i++;
        }
    }else{
        error=1;
    }
}



/*
PS C:\Users\allen\OneDrive\Desktop\test\4-Recursive descent> .\a.exe
enter the arithmetic expression : a+b*c

 Accepted
PS C:\Users\allen\OneDrive\Desktop\test\4-Recursive descent> .\a.exe     
enter the arithmetic expression : a++b

Rejected
PS C:\Users\allen\OneDrive\Desktop\test\4-Recursive descent> 
*/