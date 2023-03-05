#include <stdio.h>
#include "my_math.h"
 
int main()
{
   int a = 10;
   int b = 20;
 
   printf("a + b = %d\n", sum(a, b));
   printf("a * b = %d\n", multiply(a, b));
 
   return 0;
}