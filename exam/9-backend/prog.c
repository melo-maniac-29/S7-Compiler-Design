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
	// INPUT PHASE: Read intermediate code statements
	printf("\nEnter the set of intermediate code (Terminated by 'exit'):\n");
	printf("Format: result=operand1+operand2 (e.g., t1=a+b)\n");
	printf("========================================\n");
	
	// Read intermediate code statements until user enters "exit"
	do{
		scanf("%s",icode[i]);  // Read each intermediate code statement
	}while(strcmp(icode[i++],"exit")!=0);  // Continue until "exit" is encountered
	// TARGET CODE GENERATION PHASE
	printf("\nTarget Code Generation");
	printf("\n=====================");
	printf("\nAssembly Instructions Generated:\n");
	
	i=0;  // Reset counter for processing statements
	
	// Process each intermediate code statement
	do{
		strcpy(str,icode[i]);  // Copy current statement for processing
		
		/*
		    Instruction Selection: Map operators to assembly instructions
		    
		    String Format Analysis (for "t1=a+b"):
		    str[0] = 't' (result variable - first character)
		    str[1] = '1' (result variable - second character) 
		    str[2] = '=' (assignment operator)
		    str[3] = 'a' (first operand)
		    str[4] = '+' (arithmetic operator)
		    str[5] = 'b' (second operand)
		    
		    We check str[3] to determine the operation type
		*/
		switch(str[3])  // Check the operator at position 3
		{
			case '+': strcpy(opr,"ADD");  // Addition operation
				break;
			case '-': strcpy(opr,"SUB");  // Subtraction operation
				break;
			case '*': strcpy(opr,"MUL");  // Multiplication operation
				break;
			case '/': strcpy(opr,"DIV");  // Division operation
				break;			
		}
		
		/*
		    Three-Instruction Sequence Generation:
		    
		    For intermediate code "t1=a+b", generate:
		    1. MOV a,R0    ; Load first operand into register
		    2. ADD b,R0    ; Perform operation with second operand
		    3. MOV R0,t1   ; Store result back to memory
		    
		    Register Allocation:
		    - Each statement uses register Ri where i is statement number
		    - Simple linear allocation strategy
		*/
		
		// Instruction 1: Load first operand into register
		printf("\nMOV %c,R%d",str[2],i);  // MOV operand1,Ri
		
		// Instruction 2: Perform operation with second operand
		printf("\n%s %c,R%d",opr,str[4],i);  // OPERATION operand2,Ri
		
		// Instruction 3: Store result from register to memory
		printf("\nMOV R%d,%c",i,str[0]);  // MOV Ri,result
		
		printf("\n");  // Blank line between statement translations
		
	}while(strcmp(icode[++i],"exit")!=0);  // Continue until all statements processed
	
	printf("\nTarget code generation completed.\n");
	printf("Note: Registers R0, R1, R2, ... are used for temporary storage\n");
}