#include <stdio.h>


float soma_prod(int a, int b, int *s, int *p){
*s =a + b;
*p = a * b;
}
int main(void){
int s, p;
soma_prod(3, 5, &s, &p);
printf("Soma: %d Prod: %d\n", s, p);
return 0;
}