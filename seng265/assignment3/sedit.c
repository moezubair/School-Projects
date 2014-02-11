#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "datatype.c"
#include "Linked.c"
#include "errors.c"
#include "fileio.c"
#include "misc.c"
#include "command_processing.c"

/*************user_input*******************************************************
**Takes the user input from keyboard and stores it in dynamically allocated space
**Parameters: Array to store the input in
**Returns: pointer to the memory location where user input is at
*******************************************************************************/
char* user_input(char *userinput);
int main(int argc, char *argv[]){
	lines *buffer;			/*Data structure that holds the content read from file*/
	char *userinput;		/*Char array for user input from keyboard*/
	char *filename;			/*Filename that needs to be opened*/
	int file_modified=0;		/*0 if file has not been modified, 1 if it has*/
	int total_lines=0;		/*Total number of lines in the buffer read from file*/
	commands_list *commands;	/*Data structure that holds the tokenized user input*/
	int terminate = 0;		/*Control variable for loop*/
	
	
	filename=malloc(sizeof(char));
	buffer=process_command_line_args(argc,argv,&total_lines,&terminate);
	if (terminate==1){
		return 0;
	}
	if (buffer==NULL){
		printf("Starting without an input file.\n");
	}
	else{
		filename = copyFileName(filename,argv[1]);
	}
	
	
	printf("WELCOME TO SIMPLE TEXT EDITOR.\n");
	while (terminate==0){
		if (filename!=NULL){
			printf("sedit:%s>> ",filename);
		}else{
			printf("sedit:>> ");
		}
		userinput = malloc(sizeof(char));	/*Allocate enough memory for 1 character*/
		userinput = user_input(userinput);	/*Call method to get user input*/
		if(userinput!=NULL){
			commands=process_command(userinput);		/*Process commands and store the them in a linked list*/
			free(userinput);				/*Free what the user had typed in*/
			terminate = run_command(&commands,&filename,&file_modified,&buffer,&total_lines);		/*Run the commands*/
			free_commands(&commands);
			free(commands);

		}
	}
		freememory(&buffer);
		if (filename !=NULL){
			free(filename);
		}
	
	return 0;
}

char* user_input(char *userinput){
	char current;						/*current character*/
	int i;							/*Counter for characters read*/
	for (i=0;;i++){
		current=getchar();				/*get character and store it in current*/
		if (current=='\n'){				/*Break from the loop when user presses enter*/
			userinput[i]='\0';
			break;
		}
		userinput[i]=current;				/*Put the read character into the userinput array*/
		userinput=realloc(userinput,(i+2)*sizeof(int));	/*Increase the size of the array*/
		if (userinput ==NULL){				/*if memory was not allocated*/
			printf("Error allocating memory\n");
			return NULL;
		}
	}
	return userinput;

}
