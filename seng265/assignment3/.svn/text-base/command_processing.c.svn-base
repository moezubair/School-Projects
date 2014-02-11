/*Command processing - Handles the user typed commands, separates them and puts them in a queue, the queue is then passed to the function handling methods*/
#include <ctype.h>

commands_list* process_command(char *string){
	char curr_char;					/*Keeps track of current character*/
	int start_pos;
	int i;
	int len;					/*Length of user input*/
	int quote=0;
	int empty_list;
	commands_list *commands;
	struct command *conductor;
	struct command *temp;
	
	/*Initialize the List*/
	
	commands=malloc(sizeof(commands_list));			/*Allocate memory for the linked list*/
	commands->head = malloc(sizeof(struct command));
	conductor = commands->head;
	commands->total = 0;
	empty_list = 1;
	len = strlen(string);				/*Calculate length*/	
	
	for(i=0,start_pos=0;i<len;i++){
		curr_char = string[i];
		if (curr_char == ' '){		/*If there was a space found copy the stuff before the space*/
			if ( i>0 && string[i-1]==' ') {
				start_pos++;
				continue;
			}
			if (empty_list == 0){
				temp = malloc(sizeof (struct command));
				conductor->next = temp;
				conductor = temp;
			}
			conductor->args = malloc(i-start_pos+1*(sizeof(char)));	/*Allocate memory for the word to be copied*/
			strncpy(conductor->args,string+start_pos,i-start_pos);	/*Copy the word/command to the memory allocated*/
			conductor->args[i-start_pos]='\0';	/*Add null terminator at end*/
			conductor->next=NULL;
			commands->total++;				/*Increase total # of commands*/
			start_pos =i+1;
			if (empty_list == 1){
				empty_list = 0;
			}		
		}
		else if (curr_char == '\"'){		/*If a quote was found, copy the rest of the string and exit loop*/
			if (empty_list == 0){
				temp = malloc(sizeof (struct command));
				conductor->next = temp;
				conductor = temp;
			}
				conductor->args = malloc(len-i+1*(sizeof(char)));
				strncpy(conductor->args,string+i,len-i);
				conductor->args[len-i]='\0';
				conductor->next = NULL;
				commands->total++;
				quote=1;
				if (empty_list == 1){
					empty_list = 0;
				}
				break;
			}
		
	}
	if (quote==0){					/*If there was no quote in the string, get the last element*/
		if (empty_list == 0){
			temp = malloc(sizeof (struct command));
			conductor->next = temp;
			conductor = temp;
		}
		conductor->args = malloc(len-start_pos+1*(sizeof (char)));
		strncpy(conductor->args,string+start_pos,len-start_pos);
		conductor->args[len-start_pos]='\0';
		conductor->next = NULL;
		commands->total++;
	}	/*Finish find quote*/
	return commands;	
}
/**************Free Enqueue************************
***Frees the memory allocated by commmands list****
	Parameters:
	commands_list **head	-Address of pointer to the start of commands list
	Returns:
	0 for success
****************************************************/
int free_commands(commands_list **headNode){
	struct commands_list *top = *headNode;
	struct command *conductor = top->head;
	struct command *temp;			/*Temporary variable for command*/
	char *temp_args;
	while(conductor !=NULL){
		temp = conductor;
		/*printf("[%s]->\n",temp->args);*/
		temp_args = temp->args;
		free(temp_args);
		free(temp);
		conductor = conductor->next;
	}
	return 0;
		
}
int match(char *string,char *to,char *or){
	if (strlen(string) == 0){
		return 1;
	}
	if ((strncmp(string,to,strlen(string))==0) || strncmp(string,or,strlen(string))==0){
		return 0;
	}
	else {
		return 1;
	}
}
int process_quit(int count,int *file_modified,char *filename,lines **buffer){
	char yes_or_no;
	char newline;
	if (count!=0){
		return print_errors(QUIT);
	}
	if (*file_modified==1){				/*If the file had been changed*/
		printf("Warning: Would you like to save the changes to '%s' ? [y|n]",filename);
		yes_or_no = getchar();
		newline = getchar();
		while ((yes_or_no!='y' && yes_or_no!='n') && newline=='\n'){
			printf("Warning: Would you like to save the changes to '%s' ? [y|n]",filename);
			yes_or_no = getchar();
			newline = getchar();
		}
		if (yes_or_no == 'y'){
			Save(buffer,filename);
			*file_modified = 0;
			printf("Saving %s...Done\nBye!\n",filename);
		}
	}
	return 1;
}
int process_print(int count,struct command *param,lines **buffer,int total_lines) {
	int first_number, second_number;
	first_number = 0;				/*Initialize first number*/
	second_number = 0;				/*Initialize second number*/
	if (count>2){					/*Print can only only have at most 2 parameters*/
		return print_errors(PRINT_5);
	}
	if (count>0){					/*If atleast 1 parameter was passed with print, check for valid input*/
		first_number = atoi(param->next->args);	/*convert the first parameter to int*/
		if (first_number == 0){
			return print_errors(PRINT_1);
		}
		if (count ==1 && first_number > total_lines){
			return print_errors(PRINT_2);
		}
	}
	if (count==2){					/*if two parameters were passed with print*/
		second_number = atoi(param->next->next->args);
		if (second_number == 0){			/*Second parameter is not a number*/
			return print_errors(PRINT_1);
		}
		if (first_number >= second_number){		/*first number is > than second number*/
			return print_errors(PRINT_4);
		}
		if (second_number > total_lines){		/*Line range doesnt exist, e.g second parameter is > num of lines*/
			return print_errors(PRINT_3);
		}
	}
		
	traverse(buffer,first_number,second_number);
	return 0;
}
int process_add(int count,struct command *param, lines **buffer,int *total_lines,int *file_modified){
	int first_number;
	int second_number;
	char *string;
	/*int length_of_word;*/
	first_number=0;
	second_number=0;

	if (count>3 || count<2){						/*add can only have at most 3 parameters*/
		return print_errors(ADD_4);
	}
	if (count>=2){						/*Two parameters mean only line number and text to add*/
		first_number = atoi(param->next->args);		/*Convert the first entry after the command to int*/
		if (first_number==0){
			return print_errors(ADD_1);
		}
		if (first_number>*total_lines+1){		/*Check if user wants to add at a valid line*/
			return print_errors(ADD_2);
		}
		if (count==2){					/*If only line number was provided, check for the proper quotes*/
			if(param->next->next->args[strlen(param->next->next->args)-1]!= '\"'){
				return print_errors(ADD_4);
			}
			string = param->next->next->args;
		}		
	}
	if (count==3){						/*Three parameters mean word number is also provided*/
		second_number = atoi(param->next->next->args);
		if (second_number==0){						/*If second number is valid*/
			return print_errors(ADD_1);
		}
		if (first_number>*total_lines){
			return print_errors(ADD_2);
		}								/*check if word exists*/
		if (second_number>word_count(buffer,first_number)+1){
			return print_errors(ADD_3);
		}
		if(param->next->next->next->args[strlen(param->next->next->next->args)-1]!='\"'){ 	/*Make sure last item is closing quote*/
			return print_errors(ADD_4);
		}
		string = param->next->next->next->args;
	}
	if (add(first_number,second_number,string,buffer,total_lines)==0){
		*file_modified=1;
	}
	
	return 0;
}
int process_open(int count,struct command *param,lines **buffer,char **filename,int *total_lines,int *file_modified){
	char yes_or_no;
	char newline;
	/*Unsuccessful usage 2*/
	int error_counter=0;
	if (count !=1){						/*Make sure there was only 1 parameter used with open*/
		return print_errors(OPEN);
	}
	if (*file_modified==1){				/*If the file had been changed*/
		printf("Warning: Would you like to save the changes to '%s' ? [y|n]",*filename);
		yes_or_no = getchar();
		newline = getchar();
		while ((yes_or_no!='y' && yes_or_no!='n') && newline=='\n'){
			printf("Warning: Would you like to save the changes to '%s' ? [y|n]",*filename);
			yes_or_no = getchar();
			newline = getchar();
		}
		if (yes_or_no == 'y'){
			Save(buffer,*filename);
			*file_modified = 0;
		}
	}

	*buffer = readFile(param->next->args,total_lines,&error_counter);
	if (buffer!=NULL && error_counter==0){
		*filename = copyFileName(*filename,param->next->args);
	}
	return 0;
}
int process_delete(int count,struct command *param, lines **buffer,int *total_lines,int *file_modified){
	int first_number=0;					/*Delete starting from this number*/
	int second_number=0;					/*Delete until this number*/
	if (count==1 || count==2){				/*If atleast first number is provided*/
		first_number = atoi(param->next->args);		/*Convert the first number to int*/
		if (first_number==0){
			return print_errors(DELETE_1);
		}
		if (first_number>*total_lines){			/*Line doesnt exist*/
			return print_errors(DELETE_2);
		}
		
		
	}if (count==2){					/*If two numbers are provided, convert the second number as well*/
		second_number = atoi(param->next->next->args);
		if (second_number==0){
			return print_errors(DELETE_1);
		}
		if (second_number>*total_lines){		/*If line range doesn't exist*/
			return print_errors(DELETE_3);	
		}
		if (first_number>=second_number){		/*If first number >= second number*/
			return print_errors(DELETE_4);
		}
	}if (count<1 || count>2) {							/*If delete has more than 2 or less than 1 paramter*/
		return print_errors(DELETE_5);
	}

	delete(first_number,second_number,buffer,total_lines);
	*file_modified = 1;
	return 0;
}
int process_replace(int count,struct command *param, lines **buffer,int *total_lines,int *file_modified){
	int first_number=0;
	int second_number=0;
	char *string;


	if (count>3 || count<2){						/*replace can only have at most 3 parameters*/
		return print_errors(REPLACE_4);
	}
	if (count>=2){						/*Two parameters mean only line number and text was entered*/
		first_number = atoi(param->next->args);		/*Convert the first entry after the command to int*/
		if (first_number==0){
			return print_errors(REPLACE_1);
		}
		if (first_number>*total_lines){		/*Check if user wants to REPLACE at a valid line*/
			return print_errors(REPLACE_2);
		}
		if (count==2){					/*If only line number was provided, check for the proper quotes*/
			if(param->next->next->args[strlen(param->next->next->args)-1]!= '\"'){
				return print_errors(REPLACE_4);
			}
		}
		string = param->next->next->args;		
	}

	if (count==3){						/*Three parameters mean word number is also provided*/
		second_number = atoi(param->next->next->args);
		if (second_number==0){						/*If second number is not valid*/
			return print_errors(REPLACE_1);
		}
										/*check if word exists*/
		if (second_number>word_count(buffer,first_number)){
			return print_errors(REPLACE_3);
		}
		if(param->next->next->next->args[strlen(param->next->next->next->args)-1]!='\"'){ 	/*Make sure last item is closing quote*/
			return print_errors(REPLACE_4);
		}
		string = param->next->next->next->args;
	}
	if (replace(first_number,second_number,string,buffer,total_lines)==0){
		*file_modified=1;
	}
	return 0;
}
int process_save(int count, struct command *param, lines **buffer, int *file_modified,char *filename){
	if (count>1){					/*Save can have maximum of 1 parameters*/
		return print_errors(SAVE);
	}	
	if (count==1){
		if (Save(buffer,param->next->args)==0){
			*file_modified=0;		/*Reset file modified counter*/
		}
	}
	else{
		if (Save(buffer,filename)==0){
			*file_modified=0;		/*Reset file modified counter*/
		}
	}
	return 0;
}
	
int run_command(commands_list **head,char **filename,int *file_modified, lines **buffer,int *total_lines){
	commands_list *top = *head;
	struct command *conductor = top->head;
	int count = top->total-1;				/*Number of parameters passed with the command*/
	
	if ((match(conductor->args,"open","o"))==0){		/*command was to open*/
		return process_open(count,conductor,buffer,filename,total_lines,file_modified);
	}
	else if ((match(conductor->args,"print","p"))==0){	/*Command was print*/
		return process_print(count,conductor,buffer,*total_lines);

	}
	else if ((match(conductor->args,"add","a"))==0){	/*command was to add*/
		return process_add(count,conductor,buffer,total_lines,file_modified);
	}
	else if ((match(conductor->args,"replace","r"))==0){	/*command was to replace*/
		return process_replace(count,conductor,buffer,total_lines,file_modified);
	}
	else if ((match(conductor->args,"save","s"))==0){	/*Command was to save*/
		return process_save(count,conductor,buffer,file_modified,*filename);
	}
	else if ((match(conductor->args,"delete","d"))==0){	/*Command was to delete*/
		return process_delete(count,conductor,buffer,total_lines,file_modified);
	}
	else if ((match(conductor->args,"quit","q"))==0){
		return process_quit(count,file_modified,*filename,buffer);
	}	
	
	return 0;

}

