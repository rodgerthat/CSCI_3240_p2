/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/18/2017 11:11:32 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "p2.c"

void heap_init(int num_pages_for_heap);
void *heap_alloc(int num_bytes_to_allocate);
void heap_free(void *pointer_to_area_to_free);
void print_freeList();

int main( int argc, char * argv[] ) {

    char *p1, *p2, *p3, *p4, *p5, *p6;

    heap_init(2);

    p1 = (char *) heap_alloc(2000);
    if ((long int)p1 % 16 != 0) {
        //printf("p1 bad %p pmod16 %d\n", p1, ((long int)p1)%16);
    }
    memset(p1, 'X', 2000);

    printf("p1: %p \n", p1);

    return 0;

}

