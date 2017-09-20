/*
 * =====================================================================================
 *
 *       Filename:  p2.c
 *
 *    Description:  A collection of C functions that provide the functionality
 *                  of a heap manager
 *
 *        Version:  1.0
 *        Created:  09/14/2017 11:54:18 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Norris, Joel R. 
 *          Class:  CSCI_3240
 *      Professor:  Dr. Butler
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

// data structure to track free blocks
typedef struct {
    int *location;
    int size;
} FreeBlock;

FreeBlock freeList[100];  // using an array to track the free space

typedef struct {
    FreeBlock fB;
    int *prev;
    int *next;
} freeListNode;

void heap_init(int num_pages_for_heap) {
   
    int i, pgsz, *ip;
    unsigned char *cp;
    void *region;

    pgsz = getpagesize();
    printf("pgsz: %d\n", pgsz);

    region = mmap(NULL, pgsz, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);


    // if mmap fails, return -1
    if (region == ((void *) -1)) {
        perror("mmap"); // best to call this now, don't wait
        //return 1;
    }

    // if it works, returns pointer to region in memory we can use
    printf("region: %p\n", region); // print pointer to available memory
    // make sure it's on a 16-bit divisible address
    printf("region mod16: %d\n", (int)(long int)region % 16);
    printf("region end: %p\n", region + (pgsz*num_pages_for_heap));

    // when the heap is initialized, 
    // we'll start start the linkedlist to track the freespace
    // initially, it's all freespace. 
    
    int initialSize = (region + (pgsz*num_pages_for_heap)) - region;
    
    freeList[0].location = region;
    freeList[0].size = initialSize;

    printf("freelist[0].location: %p \n", freeList[0].location);
    printf("freelist[0].size: %d \n", freeList[0].size);

    return;
}


void *heap_alloc(int num_bytes_to_allocate) {

    return NULL;
}

void heap_free(void *pointer_to_area_to_free) {

    // you can only free a full block, not a partial block
}


