#include<stdio.h>

void main(){
    
    int s,n,a,fs,b,l,nxt,z;

    int state[20];
    int inputs[10];
    int str[20];
    int x[20];
    int k=0;

    printf("enter the no of states\n");
    scanf("%d",&s);

    printf("enter the no of inputs\n");
    scanf("%d",&n);

    for(int i=0;i<s;i++){
        
        printf("enter the state\n");
        scanf("%d",&state[i]);

        printf("is it final state 1-y n-0\n");
        scanf("%d",&a);

        if(a==1){
            fs=state[i];
        }

    }

    printf("enter the inputs\n");
    for(int i=0;i<n;i++){
        scanf("%d",&inputs[i]);
    }

    printf("transition state\n");
    for(int i=0;i<s;i++){

        for(int j=0;j<n;j++){

            printf("(q%d,%d)=q",state[i],inputs[j]);
            scanf("%d",&b);

            x[k]=b;
            k++;

        }

    }

    do{

        int q=0;//start from first state index 0 because nxt=x[n*q+t]

        printf("enter the length of the string\n");
        scanf("%d",&l);

        printf("enter the input string\n");

        for(int i=0;i<l;i++){
            scanf("%d",&str[i]);
        }

        for(int i=0;i<l;i++){
            int t=0;

            do{
                if(str[i]==inputs[t]){

                    nxt=x[n*q+t];

                    for(int j=0;j<s;j++){
                        if(nxt==state[j]){
                            q=j;
                        }
                    }
                    t++;//move to next alphabet
                    
                }else{
                        t++;//try next alphabet symbol
                }
            }while(t!=n);

        }

        if(nxt==fs){
            printf("\n string is accepted\n");
        }else{
            printf("\n string not accepted\n");
        }

        printf("do u want to continue y-1 n-0 \n");
        scanf("%d",&z);
    
    }while(z!=0);


}

/*
PS C:\Users\allen\OneDrive\Desktop\test\2-DFA> .\a.exe
enter the no of states
3
enter the no of inputs
2
enter the state
0
is it final state 1-y n-0
0
enter the state
1
is it final state 1-y n-0
0
enter the state
2
is it final state 1-y n-0
1
enter the inputs
0
1
transition state
(q0,0)=q1
(q0,1)=q0
(q1,0)=q2
(q1,1)=q1
(q2,0)=q2
(q2,1)=q2
enter the length of the string
3
enter the input string
0 0 1

 string is accepted
do u want to continue y-1 n-0
*/