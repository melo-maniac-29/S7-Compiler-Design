#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int iskeyword(char buffer[])
{
	char keywords[32][10]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","flaot","for","goto","if","int","long","register","return","short","signed",
	"sizeof","ststic","struct","switch","typeof","union","unsigned","void","volatile","while"};
	int i,flag=0;
	for(i=0;i<32;++i)
	{
		if(strcmp(keywords[i],buffer)==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}

int main()
{
	char ch,buffer[15],operators[]="+-*/%",specialch[]=",;[]{}",num[]="0123456789",buf[10];
	FILE *fp;
	int i,j=0,k=0;
	fp=fopen("program.txt","r");
	if(fp==NULL)
	{
		printf("Error while opening the file..\n");
		exit(0);
	}
	while((ch=fgetc(fp))!=EOF)
	{
		for(i=0;i<6;++i)
		{
			if(ch==operators[i])
			{
				printf("%c is an operator\n",ch);
			}
			if(ch==specialch[i])
			{
				printf("%c is a special character\n",ch);
			}
		}
		if(isalpha(ch))
		{
			buffer[j++]=ch;
		}
		if(isdigit(ch))
		{
			buf[k++]=ch;
		}
		else if((ch==' '||ch=='\n')&&(j!=0))
		{
			buffer[j]='\0';
			buf[k]='\0';
			j=0;
			if(iskeyword(buffer)==1)
				printf("%s is a keyword\n",buffer);
			else
				printf("%s is an identifier\n",buffer);
			if(k!=0)
			{
				printf("%s is a constant\n",buf);
			}		
		}
	
	}
	fclose(fp);
	return 0;
}
