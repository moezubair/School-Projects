/************************************************************************
********************Name: Muhammad Zubair********************************
********************Student Id: V00757068********************************
*******String API - Functions to manipulate strings and characters*******
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>
#define MAX_CHARS 82
#define MAX_LINES 120
int tokenize(char string[100],char tokenized[10][MAX_CHARS]);
void strip(char string[MAX_CHARS]){
	/*Strip Function - Removes trailing spaces from a string
	Parameters:
	char *string  - A string that needs to be modified*/
	size_t length;
	char *current;
	if (string && *string){
		length = strlen(string);	/*Get the length of the string*/
		current = string+length-1;
		while (current !=string && (isspace(*current))){
			--current;
		}
		current[isspace(*current)?0:1] = '\0';
		
	}
}
/*Find function
finds the first occurance of a letter and sends its location */
int find(char *string, char letter){
	char *pos = strchr(string,letter);
	int index;
	if (pos == NULL){
		return -1;
	}else{
		index = pos-string+1;
	}
	return index;
}
int tokenize_quotes(char string[100],char tokenized[MAX_CHARS][MAX_CHARS],int first,int *line_number, int*word_number){
	char string1[100];
	char quote[MAX_CHARS];
	int last;					/*locations of first and last quote found*/
	int count = 0;

	char *first_quote;	/*find the first occurance of a quote*/
	char *last_quote;	/*find the last occurance of a quote*/
	int string_length;				/*The length of string*/
	/*To convert the string to unsigned long int for checking if the user typed an integer*/
	unsigned short int alpha = 0;
	char *p;
	errno = 0;
	strcpy(string1,string);
	first_quote = strchr(string1,'"');
	last_quote = strrchr(string1,'"');
	memset(tokenized,0,MAX_CHARS);
	string_length = (int)strlen(string1);		/*Calculate the length of string*/
	if (first_quote !=NULL && last_quote != NULL && first_quote!=last_quote){
		first = first_quote-string1+1;
		last = last_quote-string1+1;
		/*printf("Start found at %d and finish found at %d\n",first,last);*/
		strncpy(quote,string1+first,last-first-1);	/*Copy the part in quotes into a new char array*/
		strncpy(string,string1,first-1);		/*Copy the part without the quotes into another string*/
		quote[last-first-1] = '\0';			/*Add null terminator at the end of quote*/
		string[first-1] = '\0';				/*Add null terminator at the end of rest of string*/
		count = tokenize(string,tokenized);		/*Tokenize the command part */
		
		if (count>0){
			strcpy(tokenized[count],quote);		/*Copy the quote into the token array*/
			count++;
			if (count>2 && count<5){	/*If count is 3 or 4, then grab the line_number and check it*/
				p = tokenized[1];
				*line_number=strtoul(tokenized[1],&p,10);
				if (errno != 0 || tokenized[1]==p || *p!=0){
					alpha=0;		/*NOt a number*/
				}else{
					alpha=1;		/*A number*/
				}
			}if (count==4){	/*if count is 4 get the word number as well*/
				if (alpha==1){	/*if line was found to be a number*/
					errno = 0;
					p = tokenized[2];
					*word_number = strtoul(tokenized[2],&p,10);	/*Check if word_number is numeric*/
					if (errno != 0 || tokenized[2]==p || *p!=0){
						alpha=0;	/*Not a number*/
					}
				}
			}
				
		}
	}else {
		if (string[0]=='a'){
			fprintf(stderr,"Error: Wrong command format.\n");
			fprintf(stderr,"Usage 1: add <line-number> \"New Text\"\n");
			fprintf(stderr,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
			count=-2;
			return count;
		}
		else{
			fprintf(stderr,"Error: Wrong command format.\n");
			fprintf(stderr,"Usage 1: replace <line-number> \"New Text\"\n");
			fprintf(stderr,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
			count=-2;
			return count;
		}
	}
		
	if ((strncmp(tokenized[0],"a",MAX_CHARS)==0) ||(strncmp(tokenized[0],"add",MAX_CHARS)==0)){
		if (first == last || last !=string_length || count>4 || alpha==0){
			fprintf(stderr,"Error: Wrong command format.\n");
			fprintf(stderr,"Usage 1: add <line-number> \"New Text\"\n");
			fprintf(stderr,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
			count=-1;
		}
	}else if ((strncmp(tokenized[0],"r",MAX_CHARS)==0)||(strncmp(tokenized[0],"replace",MAX_CHARS)==0)){
		if (first == last || last !=string_length || count>4 || alpha==0){
			fprintf(stderr,"Error: Wrong command format.\n");
			fprintf(stderr,"Usage 1: replace <line-number> \"New Text\"\n");
			fprintf(stderr,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
			count=-1;
		}
	}else{
		count=-1;
	}
	return count;
}

int tokenize(char string[82],char tokenized[MAX_CHARS][MAX_CHARS]){
	char delims[] = " ";		/*Delimitere is a space so tokenize when a space occurs*/
	char *result = NULL;
	int count = 0;
	result=strtok(string,delims);	/*Tokenize the string*/
	while(result!=NULL && count<10){
		strncpy(tokenized[count++], result, MAX_CHARS);
		result= strtok(NULL,delims);
	}
	return  count;
}

/*
int main(void){
	char str[MAX_CHARS] = "Hello world              ";
	char lines[MAX_LINES][MAX_CHARS] = {"John            ","Alex"};
	strip(str);
	printf("%s at %p\n",str,&str);
	strip(lines[0]);
	printf("%s %d\n",lines[0],(int)strlen(lines[0]));
	return 0;
}*/
