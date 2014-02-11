#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "execute.h"
#include <setjmp.h>
#define MAXLENGTH 45
#define EXIT_CALL "quit"
sigjmp_buf env;
char* get_input(char *userinput, int* spaces);
int free_mem(char* array[]);
/* SIGCHLD handler. */
static void sigchld_hdl (int sig)
{
	pid_t child;
	while ((child = (waitpid(-1, NULL, WNOHANG))) > 0) {
		printf("\n%ld Terminated.\n",(long)child);
	}
	siglongjmp(env,1);
}
int main (int argc, char *argv[]) {
	char* userinput;					/*User typed input*/
	char* commands[MAXLENGTH];
	char* cwd;						/*Current working directory*/
	int numofspaces;					
	int i;						/*Loop control variables*/
	char *token;						/*Holds each token when tokenizing string*/
	int bgflag;						/* 1 if running in background, 0 if not*/
	int exitflag;
	int cstatus;
     	struct sigaction act;

	/*Initialize variables*/
	cwd = getcwd(0,0);					/*Get current working directory*/
	numofspaces=0;
	exitflag=0;
    	memset (&act, '\0', sizeof(act));
    	act.sa_handler = sigchld_hdl;

   	if (sigaction(SIGCHLD, &act, 0)) {
		perror ("sigaction");
	return 1;
    	}
    	sigsetjmp(env, 1);


	/*Process command line arguements passed as program started*/
	for(;;){
		numofspaces=0;
		bgflag=0;
	        userinput = malloc(sizeof(char));				/*Allocate enough space for 1 char*/
		while(numofspaces==0){
			fprintf(stdout,"RSI: %s >",cwd);			/*Prompt for userinput*/
			userinput = get_input(userinput,&numofspaces);		/*Read userinput and count num of words*/
		}
		if (strcmp(userinput,EXIT_CALL)==0){
			free (userinput);
			free(cwd);
			break;
		}

		i = 0;
		token = strtok(userinput," ");					/*Tokenize userinput by space*/
		while (token!=NULL){						/*While there are more words to be tokenized*/
			commands[i] = malloc(strlen(token)*sizeof(char)+1); 	/*Assign memory for the word + null character at end*/
			strcpy(commands[i++],token);				/*Copy the tokenzied string to array*/
			token = strtok(NULL, " ");				/*Tokenize next word*/
		}
		/*If the last word is & , set background process flag to be 1*/
		if (strcmp (commands[i-1],"&")==0) {
			bgflag=1;
			free(commands[i-1]);
			i--;
		}
		commands[i] = NULL;						/*Add null to the end of the array*/
		if (strcmp(commands[0],"cd")==0){
			if (cd(commands,i)==0){
				cwd = getcwd(0,0);
			}
		}else{
			execute(commands,bgflag,&cstatus);			/*Execute commands by calling the execute funtion*/
		}

		free(userinput);	/*Free user input read from keyboard*/
		userinput = NULL;
		free_mem(commands);	/*Free tokenized array of user input*/
	}
return 0;
}
/*Free's all elements of a char array*/
int free_mem(char* array[]){
	int i;
	i= 0;
	while (array[i]!=NULL)
		{ free(array[i++]);
	}
	return 0;
}
char* get_input(char *userinput,int* word){
        char current;                                           /*current character*/
        int i;                                                  /*Counter for characters read*/
	*word = 0;
        for (i=0;;i++){
                current=getchar();                              /*get character and store it in current*/
                if (current=='\n'|| current==EOF){              /*Break from the loop when user presses enter*/
                        userinput[i]='\0';
                        break;
                }
		if (current!=' ' && *word!=1){
			*word=1;
		}
                userinput[i]=current;                           /*Put the read character into the userinput array*/
                userinput=realloc(userinput,(i+2)*sizeof(int)); /*Increase the size of the array*/
                if (userinput ==NULL){                          /*if memory was not allocated*/
                        printf("Error allocating memory\n");
                        return NULL;
                }
        }
        return userinput;

}

