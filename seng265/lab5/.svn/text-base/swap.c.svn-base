#include<stdio.h>
void swap (int* a, int* b);
char* instanceOf(char str[], char ch);
void strtok(char str[], char ch,char* array[80],int* count);
int main(){
	int a = 5;
	int b = 6;
	char str[] = "Hello World";
	char space = ' ';
	int count = 0;
	int i =0;
	char* array[80];
	fprintf(stdout,"Before swap: A : %d B: %d\n",a,b);
	swap(&a,&b);
	fprintf(stdout,"After swap:  A : %d B: %d\n",a,b);
	fprintf(stdout, "The first instance of %c was found at %ld\n",'o',(instanceOf(str,'o'))-str);
	strtok(str,space,array,&count);
	printf("There are %d tokenized words and they are: \n",count);
	for (i=0;i<count;i++){
		printf("[%d]: %s\n",i+1,array[i]);
	}


}
int strlength(char str[]){
	int count =0;
	int i = 0;
	while(str[i]!='\0'){
		i++;
		count++;
	}
	return count;
}
void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
char* instanceOf(char str[], char ch){
	int length = strlength(str);
	int i = 0;
	for (i=0;i<length;i++){
		if (str[i] == ch){
			
			return (str+i);
		}
	}
	return NULL;		
}
void strtok(char str[], char ch,char* array[80],int *len){
	int length = strlength(str);
	int i =0;
	array[0] = str;
	int count = 1;
	for (i=0;i<length;i++){
		if (str[i] == ch){
			str[i] = '\0';
			array[count++] = (str+i+1);
		}
	}

	/*while (str){
		fprintf(stdout,"%s ",str);
		*str = *(str+1);
	}*/
	*len = count;
}
