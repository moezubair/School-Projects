#include <stdio.h>
int fibonacci(int n)
{
	if (n==0) return 0;
	else if (n == 1) return 1;
	int t_1 = 1;
	int t_2 = 0;
	int t = 0;
	int i;
	for (i=1;i<n;i++)
	{
		t= t_1 + t_2;
		t_2 = t_1;
		t_1 = t;
	}
	return t;
}
int main (){
	printf("%d",fibonacci(35));
}
