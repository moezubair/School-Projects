#include<stdio.h>
int fibonacci(int n,int * array)
{
   if(n == 0) return 0;
   else if(n == 1) return 1;
   int v1,v2;
   
   if(array[n-1] !=-1) v1 = array[n-1];
   else v1 = fibonacci(n-1,array);
   
   if(array[n-2] !=-1) v2 = array[n-2];
   else v2 = fibonacci(n-2,array);
   
   array[n] = v1+v2;
   return v1+v2;
}
int main(){
	int array[35];
	int i;
	for (i=0;i<35;i++){
		array[i]=-1;
	}
	printf("%d\n",fibonacci(35,array));
}
