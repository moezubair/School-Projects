#include<stdio.h>
int main(){
	int array[] = {1,2,3};
	int * array_ptr = array;

	int i = 0;
	for (i=0;i<3;i++){
		printf("Array[%d] %d\n",i,*(array_ptr+i));
	}
	return 0;
}
