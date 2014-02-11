/*Data structure - A linked list that stores the content of the file*/
typedef struct letters {
	char character;
	struct letters *next;
}letters;
/*Data structure for store 1 line */
typedef struct one_line {
	struct letters *_line;
	int total_words;
}one_line;
/*Data structure for storing all the lines*/
typedef struct lines {
	struct one_line line;
	struct lines *next;
}lines;
typedef struct command{
	char* args;
	struct command *next;
}command;
typedef struct commands_list{
	command *head;	/*Start of the queue*/
	int total;	/*Total commands passed*/
}commands_list;
typedef enum errors {
	SEDIT,
	NO_FILE,
	OPEN,
	PRINT_1,PRINT_2,PRINT_3,PRINT_4,PRINT_5,
	ADD_1,ADD_2,ADD_3,ADD_4,
	DELETE_1,DELETE_2,DELETE_3,DELETE_4,DELETE_5,
	REPLACE_1,REPLACE_2,REPLACE_3,REPLACE_4,
	SAVE,QUIT
}errors;
