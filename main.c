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
#include <stdlib.h>
#include <string.h>
#include "p2.c"

void heap_init(int num_pages_for_heap);
void *heap_alloc(int num_bytes_to_allocate);
void heap_free(void *pointer_to_area_to_free);
void print_freeList();

int main( int argc, char * argv[] ) {

    char *p1, *p2, *p3, *p4, *p5, *p6;

    heap_init(2);

    print_freeList();

    p1 = (char *) heap_alloc(2000);
    if ((long int)p1 % 16 != 0) {
        printf("p1 bad %p pmod16 %ld\n", p1, ((long int)p1)%16);
        exit(-1);
    }
    memset(p1, 'X', 2000);
    print_freeList();
    printf("p1: %p \n", p1);

    //////////////////////////////////
    
    p2 = (char *) heap_alloc(2000);
    if ((long int)p2 % 16 != 0) {
        printf("p2 bad %p pmod16 %ld\n", p2, ((long int)p1)%16);
        exit(-1);
    }
    memset(p2, 'X', 2000);
    print_freeList();
    printf("p2: %p \n", p2);

    //////////////////////////////////
    
    p3 = (char *) heap_alloc(2000);
    if ((long int)p3 % 16 != 0) {
        printf("p3 bad %p pmod16 %ld\n", p3, ((long int)p1)%16);
        exit(-1);
    }
    memset(p3, 'X', 2000);
    printf("p3: %p \n", p3);

    //////////////////////////////////
    
    p4 = (char *) heap_alloc(2000);
    if ((long int)p4 % 16 != 0) {
        printf("p4 bad %p pmod16 %ld\n", p4, ((long int)p1)%16);
        exit(-1);
    }
    memset(p4, 'X', 2000);
    printf("p4: %p \n", p4);

    //////////////////////////////////
    
    p5 = (char *) heap_alloc(2000);
    if ((long int)p5 % 16 != 0) {
        printf("p5 bad %p pmod16 %ld\n", p5, ((long int)p1)%16);
        exit(-1);
    }
    memset(p5, 'X', 2000);
    printf("p5: %p \n", p5);

    //////////////////////////////////
    // this should fail
    
    p6 = (char *) heap_alloc(1500);  // try 1500 first
    if ((long int)p6 % 16 != 0) {
        printf("p6 bad %p pmod16 %ld\n", p6, ((long int)p1)%16);
        exit(-1);
    }
    memset(p6, 'X', 2000);
    printf("p6: %p \n", p6);

    //////////////////////////////////
    // then just get 50
    
    p6 = (char *) heap_alloc(50);
    if ((long int)p6 % 16 != 0) {
        printf("p6 bad %p pmod16 %ld\n", p6, ((long int)p1)%16);
        exit(-1);
    }
    memset(p6, 'X', 50);
    printf("p6: %p \n", p6);

    printf("DONE\n");

    return 0;   // happy returns

}

