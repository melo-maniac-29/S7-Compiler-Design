/*
    Program: Compiler Backend - Target Code Generation
    Purpose: Convert intermediate code (three-address code) into target machine code
    
    Compiler Backend Phase:
    - Takes intermediate code as input
    - Generates equivalent assembly/machine code
    - Performs register allocation and instruction selection
    
    Input Format: Three-address code statements
    Example: t1=a+b (result = operand1 operator operand2)
    
    Output Format: Assembly instructions
    Example:
    MOV a,R0    ; Load first operand into register
    ADD b,R0    ; Perform operation with second operand
    MOV R0,t1   ; Store result back to memory
    
    Register Allocation Strategy:
    - Uses registers R0, R1, R2, ... for temporary storage
    - Each intermediate statement gets its own register
    - Simple linear allocation (no optimization)
    
    Supported Operations:
    + : Addition (ADD instruction)
    - : Subtraction (SUB instruction)
    * : Multiplication (MUL instruction)
    / : Division (DIV instruction)
*/

#include<stdio.h>
#include<string.h>

/*
    Function: main()
    Purpose: Control the target code generation process
    
    Algorithm:
    1. Read intermediate code statements until "exit"
    2. For each statement in format "result=op1+op2":
       - Extract operands and operator
       - Generate corresponding assembly instructions
       - Use register allocation for temporary storage
    3. Display generated target code
    
    Example Transformation:
    Intermediate: t1=a+b
    Target Code:
    MOV a,R0    ; Load 'a' into register R0
    ADD b,R0    ; Add 'b' to R0 (R0 = a + b)
    MOV R0,t1   ; Store result from R0 to 't1'
*/
void main()
{
	// Arrays to store intermediate code and working strings
	char icode[10][10],str[25],opr[10];  // icode: input statements, str: current statement, opr: operation name
	int i=0;  // Statement counter and register index
	printf("\nEnter the set of intermediate code(Terminated by exit):\n");
	do{
		scanf("%s",icode[i]);
	}while(strcmp(icode[i++],"exit")!=0);
	printf("\nTarget code generation");
	printf("\n***********************");
	i=0;
	do{
		strcpy(str,icode[i]);
		switch(str[3])
		{
			case '+':strcpy(opr,"ADD");
				break;
			case '-':strcpy(opr,"SUB");
				break;
			case '*':strcpy(opr,"MUL");
				break;
			case '/':strcpy(opr,"DIV");
				break;			
		}
		printf("\nMOV %c,R%d",str[2],i);
		printf("\n%s %c,R%d",opr,str[4],i);
		printf("\nMOV R%d,%c",i,str[0]);
	}while(strcmp(icode[++i],"exit")!=0);
	printf("\n");
}