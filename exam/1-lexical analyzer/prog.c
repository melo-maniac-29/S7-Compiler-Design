/*
    Program: Lexical Analyzer for C Programming Language
    Purpose: To identify and classify tokens (keywords, identifiers, operators, 
             special characters, constants) from C source code
    Input: program.txt file containing C source code
    Output: Classification of each token found in the input
*/

#include<stdio.h>   // For file operations and I/O functions
#include<stdlib.h>  // For exit() function
#include<string.h>  // For strcmp() function
#include<ctype.h>   // For isalpha() and isdigit() functions

// Function to check if a given string is a C keyword
// Input: buffer containing the string to check
// Output: 1 if keyword, 0 if not a keyword
int iskeyword(char buffer[])
{
	// Array containing all 32 C keywords
	char keywords[32][10]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed",
	"sizeof","static","struct","switch","typeof","union","unsigned","void","volatile","while"};
	
	int i,flag=0;  // flag=0 means not a keyword, flag=1 means it's a keyword
	
	// Compare input buffer with each keyword in the array
	for(i=0;i<32;++i)
	{
		if(strcmp(keywords[i],buffer)==0)  // String comparison
		{
			flag=1;  // Set flag if match found
			break;   // Exit loop early when match found
		}
	}
	return flag;  // Return 1 if keyword, 0 if not
}

// Main function - Entry point of the lexical analyzer
int main()
{
	// Variable declarations
	char ch;                    // Current character being read from file
	char buffer[15];            // Buffer to store identifiers/keywords
	char operators[]="+-*/%";   // Array of operators to recognize
	char specialch[]=",;[]{}";  // Array of special characters to recognize
	char num[]="0123456789";    // Array of digits (not actually used)
	char buf[10];               // Buffer to store numeric constants
	FILE *fp;                   // File pointer for input file
	int i,j=0,k=0;             // i: loop counter, j: buffer index, k: number buffer index
	
	// Open the input file containing C source code
	fp=fopen("program.txt","r");
	if(fp==NULL)
	{
		printf("Error while opening the file..\n");
		exit(0);  // Exit if file cannot be opened
	}
	// Main lexical analysis loop - read file character by character
	while((ch=fgetc(fp))!=EOF)
	{
		// Check if current character is an operator or special character
		for(i=0;i<6;++i)
		{
			// Check for operators: +, -, *, /, %
			if(ch==operators[i])
			{
				printf("%c is an operator\n",ch);
			}
			// Check for special characters: ,, ;, [, ], {, }
			if(ch==specialch[i])
			{
				printf("%c is a special character\n",ch);
			}
		}
		
		// If character is alphabetic, add it to identifier/keyword buffer
		if(isalpha(ch))
		{
			buffer[j++]=ch;  // Store character and increment buffer index
		}
		
		// If character is a digit, add it to number buffer
		if(isdigit(ch))
		{
			buf[k++]=ch;  // Store digit and increment number buffer index
		}
		// When whitespace or newline is encountered, process accumulated tokens
		else if(ch==' ' || ch=='\n')
		{
			// Process identifier/keyword buffer if it contains data
    		if(j != 0)
    		{
       			buffer[j] = '\0';  // Null-terminate the string
       			
       			// Check if the token is a keyword or identifier
        		if(iskeyword(buffer))
            		printf("%s is a keyword\n", buffer);
        		else
            		printf("%s is an identifier\n", buffer);
        		j = 0;  // Reset buffer index for next token
    		}

    		// Process number buffer if it contains data
    		if(k != 0)
    		{
        		buf[k] = '\0';  // Null-terminate the number string
        		printf("%s is a constant\n", buf);
        		k = 0;  // Reset number buffer index for next constant
    		}
		}
	}
	// Clean up: close the input file
	fclose(fp);
	return 0;  // Successful program termination
}

/*
    PROGRAM FLOW SUMMARY:
    1. Open input file "program.txt"
    2. Read each character from the file
    3. Classify characters as:
       - Operators: +, -, *, /, %
       - Special characters: ,, ;, [, ], {, }
       - Alphabetic: accumulate into identifier buffer
       - Numeric: accumulate into number buffer
    4. When whitespace encountered:
       - Check if identifier buffer contains keyword or identifier
       - Output any accumulated numeric constants
       - Reset buffers for next tokens
    5. Continue until end of file
    6. Close file and exit

    TOKEN TYPES RECOGNIZED:
    - Keywords: C reserved words (auto, break, case, etc.)
    - Identifiers: User-defined names (variables, functions)
    - Operators: Arithmetic operators (+, -, *, /, %)
    - Special Characters: Punctuation and delimiters
    - Constants: Numeric literals
*/
