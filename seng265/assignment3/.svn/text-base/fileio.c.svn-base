/*Simple implementation of a linked list that stores a line by its characters*/
lines* readFile(char *filename,int *total_lines,int *error_counter){
	lines *root;							/*Head that points to the top of the list*/
	letters *conductor;
	lines *lines_conductor;
	int i=0;
	FILE *fp = fopen(filename,"r");
	char temp,last;						/*Temporary variable that holds the character read from the file*/
	/*If file not found return -1*/
	if (fp == 0){
		fprintf(stdout,"Error: No such file.\n");
		*error_counter=1;
		return NULL;
	}
	while ((temp = fgetc(fp))!=EOF){						/*read the file char by char*/
		if (i==0){
			root = malloc( sizeof(lines));
			root->next =0;
			lines_conductor = root;
			i = 1;
		}
		else {
			lines_conductor->next = malloc (sizeof (lines));
			lines_conductor = lines_conductor->next;
		}
		lines_conductor->next = 0;
		lines_conductor->line._line = malloc (sizeof (letters));		/*allocate memory for the linked list*/
		conductor = lines_conductor->line._line;	
		conductor->character = temp;
		conductor->next=0;
		last = temp;
		if (temp != ' '){
			lines_conductor->line.total_words++;
		}
		while ((temp=fgetc(fp))!='\n' && temp!=EOF){				/*While the character is not new line store it as 1 line*/
			if (last==' ' && temp !=' '){
				lines_conductor->line.total_words++;
			}
			last = temp;
			conductor->next = malloc (sizeof (letters));			/*Allocate space for next character*/
			conductor = conductor->next;					/*Move the pointer to that new character*/
			conductor->character = temp;					/*Assign the value that was just read in*/
			conductor->next = 0;						/*Assign next to Null */
		}
		*total_lines = *total_lines+1;						/*Add total_lines counter*/
	}

	fclose(fp);
	return root;
}

int word_count(lines **root,int line_number){
	lines *conductor = *root;
	int counter = 1;
	while (counter!=line_number && conductor!=NULL){
		conductor = conductor->next;
		counter++;
	}
	return conductor->line.total_words;
}
	
/*******************Traverse**********************************
Traverse the list and print out all the data in the linked list
	Parameters:
	lines **root	address of the pointer to root
	int first 	starting line number to print from
	int second	ending line number to print until
	Returns:
	0 for success 
	-1 for failure
*/
int traverse(lines **root,int first,int second){
	lines *conductor = *root;	/*Conductor points to the head element now*/
	letters *line;
	int i=1;
	do{				/*Loop to traverse entire file*/
		 if (first == 0 || (first!=0 && second ==0 && i==first) || (second!=0 && i >= first && i<=second)){
			line = conductor->line._line;
			fprintf(stdout,"%d==",i);
			do{			/*Loop to traverse each line*/
				fprintf(stdout,"%c",line->character);	/*Print the character node*/
				line = line->next;			/*Move the pointer to next node*/
			}while (line != NULL);				/*Print characters while it's not null*/
			printf("\n");
		}
		/*fprintf(stdout,"had %d words\n",conductor->line.total_words);*/
		i++;
		conductor = conductor->next;					/*Move the conductor to next line*/

	}while (conductor !=NULL);						/*Print lines while its not null*/
	return 0;
}
int Save(lines **root,char *filename){
	lines *conductor = *root;
	letters *line;
	FILE *fp = fopen(filename,"w");
	if (fp == NULL){
		printf("Error writing to the file.\n");
		return -1;
	}
	do{
		line = conductor->line._line;
		do{
			fprintf(fp,"%c",line->character);	/*write the character node to the file*/
			line = line->next;
		}while(line!=NULL);
		fprintf(fp,"\n");
		conductor = conductor->next;
	}while(conductor !=NULL);
	fclose(fp);
	return 0;
}
