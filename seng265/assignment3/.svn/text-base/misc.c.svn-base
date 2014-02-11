/***********************process_command_line_args******************************
--Processes the command line arguements passed with the program started

Parameters:
	int argc 		- arguement counter: number of arguements passed
	char *argv[]		- Array of char pointers that hold the arguements passed
	int *total_lines	- Pointer to the total_lines variable that holds the number of lines in a file
	int *terminate		- pointer to control variable, 0 for continue 1 for stop execution
Returns:
	pointer to data read from file if file parameter was passed
	Null if it wasn't passed
*******************************************************************************/
lines* process_command_line_args(int argc, char *argv[],int *total_lines, int *terminate){
	int error_counter = 0;
	if (argc==2){						/*If a filename was passed with command line*/
		return readFile(argv[1],total_lines,&error_counter);
	}
	if (argc==1){						/*If no filename was passed*/
		return NULL;
	}
	else {
		print_errors(SEDIT);				/*More than 1 parameter was passed, print errors and quit*/
		*terminate=1;
		return NULL;
	}
}
char * copyFileName(char *filename, char *argv){
	int i;
	filename = realloc(filename,strlen(argv)+1*sizeof(char));	/*Allocate memory for the filename*/
	for (i=0;i<strlen(argv);i++){
		filename[i] = argv[i];
	}
	filename[i] = '\0';
	return filename;
}
