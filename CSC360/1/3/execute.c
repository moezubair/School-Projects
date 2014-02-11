#include<stdio.h>
#include<stdlib.h>
/*Executes commands by creating a child process, and calling the appropriate system calls*/
int execute(char* args[],int background,int *cstatus){
	pid_t	child;
	pid_t	ch;							/*Pid of child returned by wait*/
	child = fork();
	if (child == (pid_t)(0)){					/*Child Process*/
		if (background==1){
			fprintf(stdout,"%ld Started.\n",(long)child);
		}	
		execvp(args[0],args);
		/*Program only gets here if execvp fails*/
		fprintf(stderr, "RSI: %s: command not found\n",args[0]); /*If execvp failes*/

		exit(1);

	}else{			/*Parent process*/
		if (child== (pid_t)(-1)) {
			fprintf(stderr,"Fork failed\n"); exit(1);
		}else{
			if (background==0){				/*If not running in background..wait for process to finish*/
				ch = wait(cstatus);
			}
		}
	}
	return 0;
}

/*Changes the working directory*/
int cd(char* args[],int size){
	int result;
	if (size>2){		/*Only allowed two parameters for cd*/
		fprintf(stdout,"Error: %s can only accept at max 1 arguements\n",args[0]);
		return -1;
	}
	else{
		if (size==2){
			if (strcmp(args[1],"~")==0){
				result = chdir(getenv("HOME"));
			}else{
				result = chdir(args[1]);
			}
		}else{	/*If no parameter passed with cd, go to HOME*/
			result = chdir(getenv("HOME"));
		}			
	}
	if (result!=0){
		fprintf(stdout,"Unable to change directory!\n");
		return 1;
	}
	return 0;
}
