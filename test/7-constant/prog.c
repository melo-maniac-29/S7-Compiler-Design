#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

void input();
void output();
void change(int p,char *res);
void constant();

struct exprf{
    char op[2];
    char op1[5];
    char op2[5];
    char res[5];
    int flag;
}arr[20];

int n;

int main(){
    input();
    constant();
    output();
    return 0;
}

void input(){
    int i;

    printf("\nEnter the max number of expressions : ");
    scanf("%d",&n);

    printf("\nEnter the input in the form of ( op op1 op2 res):\n");
    printf("Example: + 3 2 t1\n");

    for(i=0;i<n;i++){
        scanf("%s",arr[i].op);
        scanf("%s",arr[i].op1);
        scanf("%s",arr[i].op2);
        scanf("%s",arr[i].res);
        arr[i].flag=0;
    }
}

void constant(){
    int i,op1,op2,res;
    char op,res1[5];

    for(i=0;i<n;i++){
        if(isdigit(arr[i].op1[0]) && isdigit(arr[i].op2[0])){

            op1=atoi(arr[i].op1);
            op2=atoi(arr[i].op2);
            op=arr[i].op[0];

            switch(op){
                case '+':
                    res=op1+op2;
                    break;
                case '-':
                    res=op1-op2;
                    break;
                case '*':
                    res=op1*op2;
                    break;
                case '/':
                    if(op2==0){
                        printf("division by zero at expression %d\n",i);
                        continue;
                    }
                    res=op1/op2;
                    break;
                default:
                    continue;
            }

            sprintf(res1,"%d",res);

            change(i,res1);

            arr[i].flag=1;

        }else if(strcmp(arr[i].op,"=")==0 && isdigit(arr[i].op1[0])){
            strcpy(res1,arr[i].op1);
            change(i,res1);
            arr[i].flag=1;
        }

    }
}

void change(int p,char *res){
    int i;
    for(i=p+1;i<n;i++){
        if(strcmp(arr[p].res,arr[i].op1)==0){
            strcpy(arr[i].op1,res);
        }
        if(strcmp(arr[p].res,arr[i].op2)==0){
            strcpy(arr[i].op2,res);
        }
    }
}

void output(){
    int i;
    printf("\nOptimized Code:\n");
    for(i=0;i<n;i++){

            printf("%s %s %s %s\n",arr[i].op,arr[i].op1,arr[i].op2,arr[i].res);

    }
}