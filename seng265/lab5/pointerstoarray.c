#include <stdio.h>

int main() {
       char str1[] = "one";
       char* str2 = "two";
       char* str3 = str1;

       printf("str1: %s\n", str1);
       printf("str2: %s\n", str2);
       printf("str3: %s\n", str3);
       return 0;
}
