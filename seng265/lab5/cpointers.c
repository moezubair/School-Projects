#include <stdio.h>

int main() {
    int a = 1;
    int* b = &a;

printf("a: %d b: %d \n", a, *b);
   

*b = 2;

printf("a: %d b: %d \n", a, *b);
    return 0;
}
