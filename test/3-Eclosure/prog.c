#include<stdio.h>
#include<string.h>

char state[20][20];
int res_count;
char result[20][20];
int n;


void add_state(char s[3]){
    for(int i=0;i<res_count;i++){
        if(strcmp(result[i],s)==0){
            return;
        }
    }
    strcpy(result[res_count++],s);
}

void epsilon_closure(char state[3],char transitions[20][3][3],int tcount){
    add_state(state);

    for(int i=0;i<tcount;i++){
        if(strcmp(transitions[i][0],state)==0 && strcmp(transitions[i][1],"e")==0){
            epsilon_closure(transitions[i][2],transitions,tcount);
        }
    }
}


int main(){
    
    int tcount;
    char transitions[20][3][3];

    printf("enter the number of states\n");
    scanf("%d",&n);

    printf("\n enter states : ");
    for(int i=0;i<n;i++){
        scanf("%s",state[i]);
    }
    
    printf("\n enter the no of transitions : \n");
    scanf("%d",&tcount);

    printf("\n enter the transitions :\n");
    for(int i=0;i<tcount;i++){
        scanf("%s%s%s",transitions[i][0],transitions[i][1],transitions[i][2]);
    }

    printf("\n Epsilon closures : \n ");
    for(int i=0;i<n;i++){

        res_count=0;

        epsilon_closure(state[i],transitions,tcount);

        printf("Epsilon closure of %s = { ",state[i]);
        for(int j=0;j<res_count;j++){
            printf("%s ",result[j]);
        }
        printf(" }\n");
    }

    return 0;


}



/*
PS C:\Users\allen\OneDrive\Desktop\test\3-Eclosure> gcc .\prog.c
PS C:\Users\allen\OneDrive\Desktop\test\3-Eclosure> .\a.exe     
enter the number of states
4

 enter states : q0 q1 q2 q3

 enter the no of transitions :
6

 enter the transitions :
q0 e q1
q0 a q2
q1 e q3
q1 b q2
q2 b q3
q3 a q0

 Epsilon closures :
 Epsilon closure of q0 = { q0 q1 q3  }
Epsilon closure of q1 = { q1 q3  }
Epsilon closure of q2 = { q2  }
Epsilon closure of q3 = { q3  }
PS C:\Users\allen\OneDrive\Desktop\test\3-Eclosure> 
*/