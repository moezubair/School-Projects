/***	Name: 		Muhammad Zubair
	Student number:	V00757068
	
	A text editor program that opens and manipulates the data in a file
***/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringapi.c"
#define MAX_CHAR 82
#define MAX_LINES 120

/*FUNCTION HEADERS:*/
int openfile(char *filename, char array[MAX_LINES][MAX_CHAR],int *total_lines,int *changed);
int print_file(char array[MAX_LINES][MAX_CHAR],int total_lines,int start, int end);
int replace(char array[MAX_LINES][MAX_CHAR],char *newline, int line_num, int word_num,int total_lines,int *changed);
int add(char array[MAX_LINES][MAX_CHAR],char *newline, int line_num, int word_num,int *total_lines,int *changed);
int delete (char array[MAX_LINES][MAX_CHAR],int starting_from,int ending_at,int *total_lines,int *changed);
int save(char array[MAX_LINES][MAX_CHAR],int total_lines,char *filename,int *changed);
int quit(int changed,char *filename);
int prompt(char buffer_array[MAX_LINES][MAX_CHAR],int *total_lines,int *changed,char *filename);

int main(int argc, char * argv[]){
	/*Variables*/
	int changed = 0;						/*Keeps track of whether user made changes to the file*/
	int total_lines;						/*Total lines read from the file*/
	char *filename = "";
	char buffer_array[MAX_LINES][MAX_CHAR];				/*Multidimensional array containing file data*/

	if (argc==2){
		if (openfile(argv[1],buffer_array,&total_lines,&changed) == -1){	/*If file could not be opened it prints errors*/
			fprintf(stderr,"Error: No such File.\n");
			fprintf(stdout,"Starting without an input file\n");
		}
		else{
			filename = argv[1];					/*if file was opened sucesfully it saves the filename*/
		}
	}
	else if (argc == 1){
		fprintf(stdout,"Starting without an input file\n");
	}
	else {
		fprintf(stdout,"Error: Wrong invocation format.\n");
		fprintf(stdout,"Usage 1: ./sedit\n");
		fprintf(stdout,"Usage 2: ./sedit <path-to-input-file>\n");
		fprintf(stdout,"Bye!\n");
		return 0;
	}
	fprintf(stdout,"WELCOME TO SIMPLE TEXT EDITOR\n");
	prompt(buffer_array,&total_lines,&changed,filename);		/*Call the prompt method to get userinput*/
	fprintf(stdout,"Bye!\n");
	return 0;
}


/***********************Prompt Method********************
Parameters:
	char buffer_array[MAX_LINES][MAX_CHAR]
	int *total_lines
	int *changed
	char *filename
*********************************************************/

int prompt(char buffer_array[MAX_LINES][MAX_CHAR],int *total_lines,int *changed,char *filename){
	char commands[MAX_CHAR][MAX_CHAR];
	char buf[82];							/*Buffer that reads user input*/
	int find_quote,line_number,word_number;
	int total_commands;						/*holds the size of tokenized commands*/
	char file[82];
	while(1){
		printf("sedit:%s>>",filename);
		fflush(stdout);	
		fflush(stdin);					/*flush output before reading input*/
		fgets(buf,82,stdin);
		strip(buf);						/*Strip trailing spaces from users input*/
		find_quote = find((char *)buf,'"');			/*Tries to find a quote in user input*/
		if (find_quote == -1){
			total_commands = tokenize(buf,commands);
		}else{							/*If there was a quote in users input*/
			total_commands = tokenize_quotes(buf,commands,find_quote,&line_number,&word_number);
		}

		/*-------------------QUIT---------------------------*/
		if ((strncmp(commands[0],"q",MAX_CHARS)==0) || (strncmp(commands[0],"quit",MAX_CHARS)==0)){
			if (total_commands==1){
				if (quit(*changed,filename)==1){
					save(buffer_array,*total_lines,filename,changed);
				}
				return 0;
					
			}else{
				fprintf(stdout,"Error: Wrong command format.\nUsage: quit\n");
			}
		/*-------------------PRINT---------------------------*/
		}else if ((strncmp(commands[0],"p",MAX_CHARS)==0) || (strncmp(commands[0],"print",MAX_CHARS)==0)){
			if (total_commands==1){						/*Just printing the entire array*/
				print_file(buffer_array,*total_lines,-1,-1);
			}else if (total_commands==2){
				if (atoi(commands[1])>0){				/*Make sure its a number*/
					print_file(buffer_array,*total_lines,atoi(commands[1]),-1);	/*call the method to print*/
				}else {								/*Error if not a number*/
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: print\n");
					fprintf(stderr,"Usage 2: print <line-number>\n");
					fprintf(stderr,"Usage 3: print <smaller-line-number> <greater-line-number>\n");
				}
			}else if (total_commands==3){
				if (atoi(commands[1])>0 && atoi(commands[2])>0){	/*make sure both of them are numbers*/
					if (atoi(commands[1]) > atoi(commands[2])){ 	/*check if first number is bigger then second*/
						fprintf(stderr,"Error: Wrong command format.\n");
						fprintf(stderr,"Usage: print <smaller-line-number> <greater-line-number>\n");
					}else {
						print_file(buffer_array,*total_lines,atoi(commands[1]),atoi(commands[2]));
					}
				}else {							/*Error if both of them are not numbers*/
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: print\n");
					fprintf(stderr,"Usage 2: print <line-number>\n");
					fprintf(stderr,"Usage 3: print <smaller-line-number> <greater-line-number>\n");
				}
			}else{
				fprintf(stderr,"Error: Wrong command format.\n");
				fprintf(stderr,"Usage 1: print\n");
				fprintf(stderr,"Usage 2: print <line-number>\n");
				fprintf(stderr,"Usage 3: print <smaller-line-number> <greater-line-number>\n");

			}
		/*-------------------ADD---------------------------*/
		}else if ((strncmp(commands[0],"a",MAX_CHARS)==0) || (strncmp(commands[0],"add",MAX_CHARS)==0)){
			if (find_quote == -1){
				fprintf(stderr,"Error: Wrong command format.\n");
				fprintf(stderr,"Usage 1: add <line-number> \"New Text\"\n");
				fprintf(stderr,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
			}
			else if(total_commands==3){/*Only line number is provided*/
				if (((int)strlen(commands[2]))>80){
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: add <line-number> \"New Text\"\n");
					fprintf(stderr,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
				}else				
					add(buffer_array,commands[2],line_number,-1,total_lines,changed);
				}
			}
			else if (total_commands==4){/*Word number is also provided*/
				if ((((int)strlen(commands[2]))+((int)strlen(buffer_array[line_number-1])))>80){
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: add <line-number> \"New Text\"\n");
					fprintf(stderr,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
				}else{
				
					add(buffer_array,commands[3],line_number,word_number,total_lines,changed);
				}
		/*-------------------open---------------------------*/
		}else if((strncmp(commands[0],"o",MAX_CHARS)==0)||(strncmp(commands[0],"open",MAX_CHARS)==0)){
			if (total_commands !=2){
				fprintf(stderr,"Error: Wrong command format.\n");
				fprintf(stderr,"Usage: open <path-to-input-file>\n");
			}else if (openfile(commands[1],buffer_array,total_lines,changed) == -1){
				fprintf(stderr,"Error: No such file.\n");
			}else{
				strcpy(file,commands[1]);
				filename=file;
			}/*Close else statement - total_commands is not 2*/
			
		/*-------------------Delete---------------------------*/
		}else if((strncmp(commands[0],"d",MAX_CHARS)==0)||(strncmp(commands[0],"delete",MAX_CHARS)==0)){
			if (total_commands >3 || total_commands<2){
				fprintf(stderr,"Error: Wrong command format. \n");
				fprintf(stderr,"Usage 1: delete <line-number>\n");
				fprintf(stderr,"Usage 2: delete <smaller-line-number><greater-line-number>\n");
			}
			else if (total_commands==2){
				delete(buffer_array,atoi(commands[1]),-1,total_lines,changed); /*If only 1num provided send -1 as second number*/
			}else if (total_commands==3){
				delete(buffer_array,atoi(commands[1]),atoi(commands[2]),total_lines,changed);
			}
		/*-------------------Replace---------------------------*/
		}else if((strncmp(commands[0],"r",MAX_CHARS)==0)||(strncmp(commands[0],"replace",MAX_CHARS)==0)){
			if (find_quote == -1){
				fprintf(stderr,"Error: Wrong command format.\n");
				fprintf(stderr,"Usage 1: replace <line-number> \"New Text\"\n");
				fprintf(stderr,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
			}
			else if(total_commands==3){/*Only line number is provided*/
				if (((int)strlen(commands[2]))>80){
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: replace <line-number> \"New Text\"\n");
					fprintf(stderr,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
				}else{	
					replace(buffer_array,commands[2],line_number,-1,*total_lines,changed);
				}	
			}
			else if (total_commands==4){/*Word number is also provided*/
				replace(buffer_array,commands[3],line_number,word_number,*total_lines,changed);
			}
		/*-------------------Save---------------------------*/
		}else if((strncmp(commands[0],"s",MAX_CHARS)==0)||(strncmp(commands[0],"save",MAX_CHARS)==0)){
			if(total_commands>2){
				fprintf(stderr,"Error: Wrong command format.\n");
				fprintf(stderr,"Usage 1: save\n");
				fprintf(stderr,"Usage 2: save <path-to-output-file>\n");
			}else if (total_commands==1){
				save(buffer_array,*total_lines,filename,changed);/*If user just wants to save without providing a file name*/
			}else if (total_commands==2){
				save(buffer_array,*total_lines,commands[1],changed);		/*If user provides a file name*/

			}
		}else{
			if (total_commands!=-2){	/*Make sure we havent printed an error already*/
				fprintf(stderr,"Invalid command.\n");
			}
		}
	}
	return 0;
}
/*****************Open File Method************
Opens the file and adds the content of the file into provided array
Parameters:
FILE *fp	-	A file pointer
char *filename	-	location of the input file being read
int array[MAX_SIZE][MAX_SIZE]	- A two dimensional array with file content

Returns:
0 for success
-1 for failure
*********************************************/
int openfile(char *filename, char array[MAX_LINES][MAX_CHAR],int *total_lines,int *changed){
	int count = 0;
	int length;
	FILE *fp;
	fp = fopen(filename,"r");
	if (fp != NULL){			/*Check if file exists and can be opened*/
		while((fgets(array[count],MAX_CHAR+2,fp))!=NULL){		/*Read while there is content in file*/

			length = strlen(array[count]);
			if (array[count	][length-1] == '\n'){		/*Remove the \n's from lines*/
				array[count][length-1] = '\0';
			}
			/*printf("at %d [%s] with length [%d]\n",count,array[count],length);*/
			count++;					/*Increment line count*/
		}
		*total_lines = count;
		fclose(fp);						/*Close the file*/

		return 0;
	}
	else {								/*If there was a problem opening the file, return -1 for failure*/
		return -1;
	}
}
/*Print File function - Prints the buffer array
parameters:
	Char array[MAX_LINES][MAX_CHAR]
	int total_lines 	= number of lines
	int start
	int end
*/
int print_file(char array[MAX_LINES][MAX_CHAR],int total_lines,int start, int end){
	int count;							/*The current line being printed*/
	if (start!=-1 && end!=-1){
		if(end>total_lines || start>total_lines){		/*MAke sure its in range*/
			fprintf(stderr,"Error: No such line range.\n");
			return 0;
		}else{							/*If in range, print the lines*/
			for (count=start-1;count<end;count++){
				printf("%d===%s\n",count+1,array[count]);
			}
			return 0;
		}	/*CLose printing */
	}
	else if (start==-1 && end==-1){	/*print the entire array*/
		for (count=0;count<total_lines;count++){
			printf("%d===%s\n",count+1,array[count]);		/*Print the array line by line*/
		}
		return 0;
	}
	else if (start!=-1 && end==-1) {/*printing only 1 line*/
		if (start>total_lines){	
			fprintf(stderr,"Error: No such line.\n");
			return 0;
		}
		printf("%d===%s\n",start,array[start-1]);
	}
	return 0;
}
/********************Replace method*****************
Parameters:
	char array[MAX_LINES][MAX_CHAR]
	char *newline
	int line_num
	int word_num
	int total_lines
	int *changed
*****************************************************/
int replace(char array[MAX_LINES][MAX_CHAR],char *newline, int line_num, int word_num,int total_lines,int *changed){
	int i;
	char words[MAX_CHARS][MAX_CHARS];
	char words1[MAX_CHARS];
	int total_words;
	char temp[MAX_CHARS];
	words1[0]='\0';
	temp[0]='\0';
	/*Makes room for the new line to be added, this is done by copying the data over to empty spots*/
	if (line_num-1 <total_lines && line_num>0){
		if (word_num == -1){
			strncpy(array[line_num-1],newline,MAX_CHAR);	/*Copy the new word that needs to be added*/
			*changed=1;
		}else{
			/*Tokenize the words*/
			strcpy(temp,array[line_num-1]);
			total_words=tokenize(temp,words);
			if (word_num > total_words){
				fprintf(stderr,"Error: No such word.\n");
				return 0;
			}				
			if (word_num-1 < total_words && word_num >0){
				strncpy(words[word_num-1],newline,MAX_CHAR);	/*replace the new words*/
				/*Merge the array back to 1-d*/
				for (i=0;i<total_words+1;i++){

					strcat(words1,words[i]);	/*Add the words into a string*/
					strcat(words1," ");
				}
				if (((int)strlen(words1)) > 80) {
					fprintf(stderr,"Error: Wrong command format.\n");
					fprintf(stderr,"Usage 1: replace <line-number> \"New Text\"\n");
					fprintf(stderr,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
					return 0;
				}
				strncpy(array[line_num-1],words1,MAX_CHAR);	/*Copy the new string back to array*/
				*changed=1;

			}else{/*Word number doesnt exist*/
				fprintf(stderr,"Error: No such word.\n");
			}
		}
	}else {/*Line number doesnt exist*/
		fprintf(stderr,"Error: No such line.\n");
	}
return 0;
}
/*ADD Function - Adds a line of text at a specific location 
Parameters:
char array[MAX_LINES][MAX_CHAR] - The array containing the current content of the file
int line_num 			- The line where the data should be added
int word_num			- The word number where the new text should be added
int *total_lines		- A pointer whose location specifies the total lines in array
*/
int add(char array[MAX_LINES][MAX_CHAR],char *newline, int line_num, int word_num,int *total_lines,int *changed){
	int i;
	char words[MAX_CHARS][MAX_CHARS];
	char words2[MAX_CHARS];
	char temp[MAX_CHARS];
	int total_words;
	words2[0]='\0';
	temp[0] = '\0';
	/*Makes room for the new line to be added, this is done by copying the data over to empty spots*/
	if (line_num-1 <=*total_lines && line_num>0){
		if (word_num == -1){
			if (line_num > 120 || *total_lines==120){
				/*CHeck to make sure that user is not exceeding line count*/
				fprintf(stderr,"Error: Maximum number of lines allowed are 120\n");
			}else{
				for (i=*total_lines; i>line_num-1;i--){		/*Make room for new line*/
					strncpy(array[i],array[i-1],MAX_CHAR);
				}
				strncpy(array[line_num-1],newline,MAX_CHAR);	/*Copy the new word that needs to be added*/
				*total_lines = *total_lines+1;			/*Increment total line count*/
				*changed=1;
			}
		}else{
			/*Tokenize the words*/
			strcpy(temp,array[line_num-1]);
			total_words=tokenize(temp,words);
			if (word_num-1 <=total_words && word_num >0){
				
				for (i=total_words;i>word_num-1;i--){
					strncpy(words[i],words[i-1],MAX_CHAR);
				}
	
				strncpy(words[word_num-1],newline,MAX_CHAR);	/*Add the new word into empty spot*/
				/*Merge the array back to 1-d*/

				words2[0]='\0';
				for (i=0;i<total_words+1;i++){

					strcat(words2,words[i]);	/*Add the words into a string*/
					strcat(words2," ");
				}
				strncpy(array[line_num-1],words2,MAX_CHAR);	/*Copy the new string back to array*/
				*changed=1;
			}else{/*Word number doesnt exist*/
				fprintf(stderr,"Error: No such word.\n");
			}
		}
	}else {/*Line number doesnt exist*/
		fprintf(stderr,"Error: No such line.\n");
	}
	return 0;
}
/****************************Delete method************************
	Parameters:
	char array[MAX_LINES][MAX_CHAR]
	int starting_from
	int ending_at
	int *total_lines
	int *changed
*******************************************************************/
int delete (char array[MAX_LINES][MAX_CHAR],int starting_from,int ending_at,int *total_lines,int *changed){
	int i=0;
	if (starting_from <=0){
		fprintf(stderr,"Error: Wrong command format. \n");
		fprintf(stderr,"Usage 1: delete <line-number>\n");
		fprintf(stderr,"Usage 2: delete <smaller-line-number><greater-line-number>\n");
		return 0;
	}
	if (ending_at!=-1){
		if (ending_at<=0) {	/*Check if ending_at is a number*/
			fprintf(stderr,"Error: Wrong command format. \n");
			fprintf(stderr,"Usage 1: delete <line-number>\n");
			fprintf(stderr,"Usage 2: delete <smaller-line-number><greater-line-number>\n");
			return 0;
		}

	}


	if (ending_at==-1){ /*only delete 1 line at starting_from*/
		if (starting_from>*total_lines){
			fprintf(stderr,"Error: No such line.\n");
			return 0;
		}
		for (i=starting_from-1;i<*total_lines;i++){
			strcpy(array[i],array[i+1]);
		}
		*total_lines = *total_lines-1;
		*changed = 1;
		return 1;
	}else { /*Deleting a range of numbers*/
		if (ending_at!=-1 && starting_from>=ending_at){/*Starting number is greater than ending number*/
			fprintf(stderr,"Error: Wrong command format.\n");
			fprintf(stderr,"Usage: delete <smaller-line-number> <greater-line-number>\n");
			return 0;
		}
		else if (starting_from <=*total_lines && ending_at>*total_lines){/*Starting number is okay but ending number doesnt exist*/
			fprintf(stderr,"Error: No such line range.\n");
			return 0;
		}
		while (ending_at>starting_from-1){		/*While ending at is bigger than starting from*/
			for (i=ending_at-1;i<*total_lines;i++){
				strcpy(array[i],array[i+1]);		/*COpy the element to the top space*/
			}
			ending_at = ending_at-1;
			*total_lines = *total_lines-1;		/*SUBTRACT 1 From total lines*/
		}
		*changed =1;
		return 1;
	}
	
}
/********Save method
parameters:
	char array[MAX_LINES][MAX_CHAR]
	int total_lines
	char *filename
	int *changed
*/
int save(char array[MAX_LINES][MAX_CHAR],int total_lines,char *filename,int *changed){
	FILE *file;
	int i=0;
	file = fopen(filename,"w");
	for (i=0;i<total_lines;i++){
		fprintf(file,"%s\n",array[i]);
	}
	fclose(file);
	*changed=0;
	fprintf(stdout,"Saving %s...Done\n",filename);
	return 0;
}
/*---------Quit method
Parameters:
	int changed
	char *filename
*/
int quit(int changed,char *filename){
	char c;
	char newline;
	if (changed==0){
		return 0;
	}
	else {
		fprintf(stdout,"Warning: Would you like to save the changes to '%s'?[y|n]:",filename);
		fscanf(stdin,"%1c",&c);
		fscanf(stdin,"%1c",&newline);
		while (c!='n' && c!='y'){
			fprintf(stderr,"\nPlease enter y for Yes or n for No: ");
			fscanf(stdin,"%1c",&c);
			fscanf(stdin,"%1c",&newline);
		}
		if (c=='y'){
			return 1;
		}
	}
	return 0;
}
