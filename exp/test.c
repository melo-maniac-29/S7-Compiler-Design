#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int n;
struct expr{
    char op[4],op1[4],op2[4],res[3];
    int flag;
}arr[10];

void main(){
    input();
}
void input(){
    printf("Enter the expression : ");
    scanf("%d",&n);

    printf("Enter the input in the form (op op1 op2 res)");
    for(int i =0;i<n;i++){
        scanf("%s",arr[i].op);
        scanf("%s",arr[i].op1);
        scanf("%s",arr[i].op2);
        scanf("%s",arr[i].res);
        arr[i].flag=0;
    }
}
void constant(){
    int i , op1,op2,res;
    char op ,res1[9];
    for(i=0;i<n;i++){
        if(isdigit(arr[i].op1[0] && arr[i].op2[0]) || 
        strcmp(arr[i].op , '=')==0 && isdigit(arr[i].op1)){
            op1 = atoi(arr[i].op1);
            op2 = atoi(arr[i].op2);
            op = arr[i].op[0];


            switch(op){
                case '+': res = op1 + op2; break;
                case '-': res = op1 - op2; break;
                case '*': res = op1 * op2; break;
                case '/': res = op1 / op2; break;
                case '=': res = op1; break;
            }

            sprintf(res1 ,"%d",res);
            change(i,res1);
            arr[i].flag = 1;
        }
    }
}
void change(int p,char *res){
    int i;
    for(i=0;i<n;i++){
        if((strcmp(arr[p].res) , arr[i].op1)==0)
            sr
    }
}