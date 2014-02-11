#include <stdio.h>
#include <stdlib.h>
void bsort (int array[], int length);
void printarray(int array[], int length);

void main(void){
	int length = 0x14;
	int array[length];
	int i,j;
	/*Initialize the array*/
	printf("Assigning numbers...\n");
	for (i=0;i<length;i++){
		j = 1 + (int) (rand()%100+1);
		array[i] = j;
	}
	printf("Printing the array: \n");
	printarray(array,length);
	printf("Sorting Array...\n");
	bsort(array,length);
	printf("Printing sorted array: \n");
	printarray(array,length);
	exit(EXIT_SUCCESS);
}
void printarray(int array[], int length){
	int i;
	for (i=0; i < length; i++){
		printf("%3d ",array[i]);
	}
	printf("\n");
}
void bsort (int array[], int length){
	int i, j, temp;
	for (i = length-1;i>0;i--){
		for (j=1;j<=i;j++){
			if (array[j-1] > array[j]){
				temp = array[j-1];
				array[j-1] = array[j];
				array[j] = temp;
			}
		}
	}
}
