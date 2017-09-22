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

#define ARRAY_SIZE 10
//const static int ARRAY_SIZE = 10;

// data structure to track free blocks
typedef struct {
    int *location;
    int size;
} FreeBlock;

FreeBlock freeList[ARRAY_SIZE];  // using an array to track the free space
int arrayLastIndex = 0;
int *heapStart;

/*
typedef struct {
    FreeBlock fB;
    int *prev;
    int *next;
} freeListNode;
*/

void print_freeList() {

    int i=0;
    printf("-------------------------------------\n");

    printf("arrayLastIndex: %d \n", arrayLastIndex);

    printf("Heap Start: %p \n", heapStart);

    for(i; i<ARRAY_SIZE; ++i) {
        printf("freelist[%d]: ", i);
        printf("location: %p \t size: %d \t \n", freeList[i].location, freeList[i].size);
    }
    printf("-------------------------------------\n");
}


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

    heapStart = region;

    print_freeList();

    return;
}


void *heap_alloc(int num_bytes_to_allocate) {

    // implement first~fit, loop through array, and find first available space for block.
    int i=0;
    for (i; i<ARRAY_SIZE; ++i) {
            
        // if the freeList array node has enough space, 
        if (num_bytes_to_allocate < freeList[i].size) {
            // assign it to a % 16 address
            if ( (long int)freeList[i].location % 16 == 0 ) {
                // it's already at a % 16 address
                // update freeList
                freeList[i].location += num_bytes_to_allocate;
                freeList[i].size = freeList[i].size - num_bytes_to_allocate;
                return freeList[i].location;
            } else {
                // it's not on a %16 bit address
                freeList[i].location += (long int)freeList[i].location % 16;
                freeList[i].size += freeList[i].size - num_bytes_to_allocate;
                return freeList[i].location;
            }
            
        }

    }

    print_freeList();


    // if the region requested cannot fit...
    return NULL;
}


void heap_free(void *pointer_to_area_to_free) {

    // you can only free a full block, not a partial block
}


