/*Free memory by traversing through the linked list*/
int freememory(lines **root){
lines *conductor = *root;	/*conductor is a pointer to the first line*/
letters *temp;			/*A temporory variable that holds the letters before deleting*/
lines *current;			/*Keeps track of current line*/
	while (conductor != NULL){
		while(conductor->line._line!=NULL){
			temp = conductor->line._line;		/*Store the pointer to the start of the list as temp*/
			conductor->line._line = conductor->line._line->next;	/*Move to the next entry in the line*/
			free(temp);						/*Free the previous entry stored in temp*/
		}
		current = conductor;						/*Store the line that was just deleted as current*/
		conductor = conductor->next;					/*Move conductor to the next line*/
		free(current);							/*Free the memory of previous line*/
	}

return 0;
}
int isLineEmpty(letters **root){
	letters *conductor = *root;

	if (conductor == NULL){
		return 1;	/*Return true for empty line*/
	}else{
		return 0;	/*Return false for non-empty line*/
	}

}
int delete_one(int starting_line,lines **buffer,int *total_lines){
	lines *current = *buffer;			/*Node that needs to be deleted*/
	lines *previous = NULL;				/*Node prior to the one being deleted*/
	int counter = 1;
	letters *temp = NULL;				/*temp variable that holds info before deleting it*/
	while (counter!=starting_line){
		previous = current;
		current = current->next;
		counter++;
	}
		while(current->line._line!=NULL){
			temp=current->line._line;
			current->line._line=current->line._line->next;
			free(temp);				/*Free the character one by one*/
		}
		if (previous==NULL){			/*If deleting the first line*/
			*buffer=current->next;		/*Change the header*/
		}else{
			previous->next=current->next;	/*Otherwise make the prior's next the currents next*/
		}
		free(current);
		*total_lines = *total_lines-1;
	return 0;
}
int delete(int starting_line,int ending_line,lines **buffer,int *total_lines){
	int i = starting_line;
	if (ending_line==0){
		return delete_one(starting_line,buffer,total_lines);		/*Just deleting 1 line*/
	}else{
		for (i=starting_line;i<=ending_line;i++){
			delete_one(starting_line,buffer,total_lines);		/*Deleting multiple lines*/
		}
	}
	return 0;
}
int replace(int line_number, int word_number, char *string,lines **buffer,int *total_lines){
	lines *conductor = *buffer;
	letters *temp;

	int counter=1;
	
	/***Variables for linked list of new string***/
	letters *head;
	letters *conductor_letters;
	letters *tail;
	int i;
	int total_words=0;
	char last_char;
	char current_char;
	head = NULL;
	head = malloc(sizeof(letters));
	head->character = string[1];
	head->next = NULL;
	conductor_letters = head;
	tail = head;
	/*Turn the new string into linked list*/
	for (i=2;i<strlen(string)-1;i++){
		current_char = string[i];
		if (string[i] == ' '){
			last_char = string[i];
		}
		if (last_char==' ' && current_char !=' ' ){
			last_char = string[i];
			total_words++;
		}
		conductor_letters->next = malloc(sizeof(letters));
		conductor_letters = conductor_letters->next;
		conductor_letters->character = string[i];
		conductor_letters->next = NULL;
		tail = conductor_letters;
	}
	total_words++;
	/*
	letters *c;
	c = head;
	while (c!=NULL){
		printf("[%c]->",c->character);
		c = c->next;
	}
	printf("\n");
	*/
	/*Traverse through the list until the node where data should be replaced*/
	while (counter!=line_number){
		conductor = conductor->next;
		counter++;
	}
	if (word_number==0){	/*Replace a line*/
		while(conductor->line._line !=NULL){
			temp = conductor->line._line;
			conductor->line._line = conductor->line._line->next;
			free(temp);
		}
		conductor->line._line = head;
		conductor->line.total_words = total_words;
	}
	return 0;
}
int add(int line_number, int word_number, char *string,lines **buffer,int *total_lines){
	lines *conductor = *buffer;
	lines *previous;
	lines *temp = NULL;
	lines *tempo = NULL;

	int counter=1;
	int word_counter = 1;
	
	letters *current_letter;
	letters *prior;
	letters *temphead;
	/***Variables for linked list of new string***/
	letters *head;
	letters *conductor_letters;
	letters *tail;
	int i;
	int total_words=0;
	char last_char;
	char current_char;
	head = NULL;
	head = malloc(sizeof(letters));
	head->character = string[1];
	head->next = NULL;
	conductor_letters = head;
	tail = head;
	/*Turn the new string into linked list*/
	for (i=2;i<strlen(string)-1;i++){
		current_char = string[i];
		if (string[i] == ' '){
			last_char = string[i];
		}
		if (last_char==' ' && current_char !=' ' ){
			last_char = string[i];
			total_words++;
		}
		conductor_letters->next = malloc(sizeof(letters));
		conductor_letters = conductor_letters->next;
		conductor_letters->character = string[i];
		conductor_letters->next = NULL;
		tail = conductor_letters;
	}
	total_words++;
	/*
	letters *c;
	c = head;
	while (c!=NULL){
		printf("[%c]->",c->character);
		c = c->next;
	}
	printf("\n");
	*/
	/*Traverse through the list until the node where data should be added*/
	previous= NULL;
	if (line_number == *total_lines+1){		/*If adding to the end of list, traverse until the end*/
		while(conductor != NULL){
			previous = conductor;
			conductor = conductor->next;
		}
	}else{						/*if adding in the middle of the list*/
		while (counter!=line_number){
			previous = conductor;
			conductor = conductor->next;
			counter++;
		}
	}
	if (word_number==0){	/*Add a new line*/
	
		temp = malloc(sizeof(lines));		/*Allocate memory for new line*/
		temp->next = NULL;
		temp->line._line = head;
		temp->line.total_words = total_words;
		
		if (line_number == *total_lines+1){	/*If adding at end of list*/
			previous->next = temp;		/*add to the previous entry's next element*/
			*total_lines += 1;
		}else if (line_number==1){
			tempo = *buffer;
			*buffer = temp;
			(*buffer)->next = tempo;
			*total_lines +=1;
		}else {
			previous->next = temp;
			temp->next = conductor;
			*total_lines +=1;
			
		}
	}else{
		current_letter = conductor->line._line;
		prior = NULL;
		if (word_number == conductor->line.total_words){
			while(current_letter !=NULL){
				prior = current_letter;
				current_letter = current_letter->next;
			}
		}else{
			while(word_counter != word_number){
				prior = current_letter;
				current_letter = current_letter->next;
				if (prior->character == ' '){
					word_counter++;
				}
			}
		}

		 if (word_number == 1){
			temphead = conductor->line._line;
			conductor->line._line = head;
			tail->next = malloc(sizeof(letters));
			tail->next->character = ' ';
			tail->next->next = temphead;
		}else if (word_number == conductor->line.total_words){
			prior->next = malloc(sizeof(letters));
			prior->next->character = ' ';
			prior->next->next = head;
			tail->next = NULL;
		}else{
			prior->next = head;
			tail->next = malloc(sizeof(letters));
			tail->next->character = ' ';
			tail->next->next = current_letter;
		}

		conductor->line.total_words +=total_words;

			
				
	}
	return 0;
}
		 
