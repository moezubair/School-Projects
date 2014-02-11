#include <stdio.h>		 /*Input/output */
#include <stdlib.h>
#include <unistd.h>				
#include <errno.h>		/*Errors*/
#define QUIT_STRING "q"
int main(void){
	char *cwd;		/*Holds the current working directory*/
	char *input;		/*user input*/

	int nbytes;

	/*Initialize variables*/
	nbytes = 100;
	cwd = getcwd(0,0);
	
	for (;;){	/*Loop keeps running until break is reached*/
		fprintf(stdout,"RSI: %s> ",cwd);
		input = ((char*) malloc (nbytes+1));
		if (getline(&input,&nbytes,stdin)==-1){	/*Read user input, if unable to read it, break loop and exit program*/
			puts("Error reading from keyboard");
			break;
		}
		fprintf(stdout,"You typed: %s with length %d",input,strlen(input));
	}
	return 1;
}
