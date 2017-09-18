#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, n, fd;
    void *p;

    p = malloc(1);
    printf("%p %ld %d \n", p, (long int)p,  (int)(long int)p % 16);
   
    p = malloc(1);
    printf("%p %ld %d \n", p, (long int)p,  (int)(long int)p % 16);
   
}
