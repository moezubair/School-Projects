int print_errors(errors error){
		/*Sedit:*/
	if (error==SEDIT){
		fprintf(stdout,"Error: Wrong invocation format.\n");
		fprintf(stdout,"Usage 1: ./sedit\n");
		fprintf(stdout,"Usage 2: ./sedit <path-to-input-file>\n");
		fprintf(stdout,"Bye!\n");
	}else if (error==OPEN){
		/*open:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage: open <path-to-input-file>\n");
	}else if (error==PRINT_1 || error==PRINT_5){
		/*print_1,print_5:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage 1: print\n");
		fprintf(stdout,"Usage 2: print <line-number>\n");
		fprintf(stdout,"Usage 3: print <smaller-line-number> <greater-line-number>\n");
	}else if (error==PRINT_2){
		/*print_2:*/
		fprintf(stdout,"Error: No such line.\n");
	}else if (error==PRINT_3){
		/*print_3:*/
		fprintf(stdout,"Error: No such line range.\n");
	}else if (error==PRINT_4){
		/*print_4:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage: print <smaller-line-number> <greater-line-number>\n");
	}else if (error==ADD_1 || error==ADD_4){
		/*Add_1,ADD_4:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage 1: add <line-number> \"New Text\"\n");
		fprintf(stdout,"Usage 2: add <line-number> <word-number> \"New Text\"\n");
	}else if (error==ADD_2){
		/*ADD_2:*/
		fprintf(stdout,"Error: No such line.\n");
	}else if (error==ADD_3){
		/*ADD_3:*/
		fprintf(stdout,"Error: No such word.\n");
	}else if (error==DELETE_1 || error==DELETE_5){
		/*DELETE_1.Delete_5:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage 1: delete <line-number>\n");
		fprintf(stdout,"Usage 2: delete <smaller-line-number> <greater-line-number>\n");
	}else if (error==DELETE_2){
		/*Delete_2:*/
		fprintf(stdout,"Error: No such line.\n");
	}else if (error==DELETE_3){
		/*Delete_3:*/
		fprintf(stdout,"Error: No such line range.\n");
	}else if (error==DELETE_4){
		/*Delete_4:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage: delete <smaller-line-number> <greater-line-number>\n");
	}else if (error==REPLACE_1 || error==REPLACE_4){
		/*REPLACE_1,REPLACE_4:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage 1: replace <line-number> \"New Text\"\n");
		fprintf(stdout,"Usage 2: replace <line-number> <word-number> \"New Text\"\n");
	}else if (error==REPLACE_2){
		/*REPLACE_2:*/
		fprintf(stdout,"Error: No such line.\n");
	}else if (error==REPLACE_3){
		/*REPLACE_3:*/
		fprintf(stdout,"Error: No such word.\n");
	}else if (error==SAVE){
		/*SAVE:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage 1: save\n");
		fprintf(stdout,"Usage 2: save <path-to-output-file>\n");
	}else if (error==QUIT){
		/*QUIT:*/
		fprintf(stdout,"Error: Wrong command format.\n");
		fprintf(stdout,"Usage: quit\n");
	}else if (error==NO_FILE){
		/*File not found error:*/
		fprintf(stdout,"Error: No such file.\n");
	}
	return 0;
}

