#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char a[20];
int c;
char act[20];
int i=0,j=0;
char stk[20];
char ac[20];


void check(){
    strcpy(ac,"REDUCE TO E ->");

    //E->i
    for(int z=0;z<c;z++){
        if(stk[z]=='i'){
            printf("%s i",ac);
            stk[z]='E';
            stk[z+1]='\0';
            printf("\n$%s\t%s$\t",stk,a);
        }
    }


    //E->E+E
    for(int z=0;z<c-2;z++){
        if(stk[z]=='E' && stk[z+1]=='+' && stk[z+2]=='E'){
            printf("%s E+E",ac);
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t",stk,a);
            i=i-2;
        }
    }

    //E->E*E
    for(int z=0;z<c-2;z++){
        if(stk[z]=='E' && stk[z+1]=='*' && stk[z+2]=='E'){
            printf("%s E*E",ac);
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t",stk,a);
            i=i-2;
        }
    }

    //E->(E)
    for(int z=0;z<c-2;z++){
        if(stk[z]=='(' && stk[z+1]=='E' && stk[z+2]==')'){
            printf("%s (E)",ac);
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t",stk,a);
            i=i-2;
        }
    }

    return;

}


int main(){

    printf("GRAMMAR is:\n");
    printf("E -> E+E\nE -> E*E\nE -> (E)\nE -> i\n");

    printf("Enter the string : ");
    scanf("%s",a);

    c=strlen(a);

    strcpy(act,"SHIFT");

    printf("\nstack\tinput\taction");
    printf("\n$\t%s$\t",a);

    for(i=0,j=0;j<c;i++,j++){
        printf("%s",act);
        stk[i]=a[j];
        stk[i+1]='\0';
        a[j]=' ';

        printf("\n$%s\t%s$\t",stk,a);

        check();
    }

    check();

    if(stk[0]=='E' && stk[1]=='\0'){
        printf("accepted\n");
    }else{
        printf("Rejected\n");
    }

    return 0;

}


/*
PS C:\Users\allen\OneDrive\Desktop\test\5-Shift reduce> gcc .\prog.c
PS C:\Users\allen\OneDrive\Desktop\test\5-Shift reduce> .\a.exe     
GRAMMAR is:
E -> E+E
E -> E*E
E -> (E)
E -> i
Enter the string : i+i*i

stack   input   action
$       i+i*i$  SHIFT
$i       +i*i$  REDUCE TO E -> i
$E       +i*i$  SHIFT
$E+       i*i$  SHIFT
$E+i       *i$  REDUCE TO E -> i
$E+E       *i$  REDUCE TO E -> E+E
$E         *i$  SHIFT
$E*         i$  SHIFT
$E*i         $  REDUCE TO E -> i
$E*E         $  REDUCE TO E -> E*E
$E           $  accepted
*/