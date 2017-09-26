// Norris, Joel R.
// CSCI_3240
// p2
// Dr. Butler
// Create a set of functions that function as a mini heap manager

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct freeBlock{
	char check;
	void *address;
	int size;
	int freeSpace;
	struct freeBlock *next;
};
// struct to track the start of our linked list
struct freeBlock *head;

void heap_init (int num_pages_for_heap){

	void *heap;
	num_pages_for_heap = num_pages_for_heap * getpagesize();
	heap = mmap(NULL, num_pages_for_heap, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	memset( heap,'X',num_pages_for_heap );
	head = (struct freeBlock *) malloc(sizeof(struct freeBlock));
	head->freeSpace = num_pages_for_heap;
	head->address = heap;
	head->check = 'B';
	head->size = 0;
	head->next = NULL;
	
	return;
}

void *heap_alloc(int num_bytes_to_allocate)
{
	struct freeBlock *temp,*newBlock;

	char *t;
	long int freeSpace, math;
	temp = head;

	while( temp->next != NULL){

		if ((temp->check == 'A') && (temp->size >= num_bytes_to_allocate)) 
        {
            temp->check = 'B';
            temp->size = num_bytes_to_allocate;
            return temp->address;
        }

		freeSpace = temp->freeSpace;
		if ( temp->freeSpace < num_bytes_to_allocate ) return NULL;
		temp = temp->next;
	}
		
    math = temp->size;

    while (( (long int)temp->address + math) % 16 !=0 ) 
    {	
        math += 1;
        if ( num_bytes_to_allocate + math>temp->freeSpace ) return NULL;
    }
    
    newBlock = (struct freeBlock *) malloc( sizeof(struct freeBlock) ) ;

    temp->next = newBlock;

    newBlock->check = 'B';
    newBlock->next = NULL;
    newBlock->freeSpace = temp->freeSpace-math;
    newBlock->size = num_bytes_to_allocate;
    newBlock->address = temp->address + math;

	return newBlock->address; 

}
	
	
void  heap_free(void *pointer_to_area_to_free){

    struct freeBlock *temp,*prev;
    temp = head;
    while( temp->address != pointer_to_area_to_free )
    {
        prev = temp;
        temp = temp->next;
    }
    temp->check='A';
    if ( temp->next->check == 'A' )
    {
        temp->size += temp->next->size;
        temp->freeSpace += temp->next->size;
        temp->next = temp->next->next;
    }
    if (prev->check=='A')
    {
        prev->size += temp->size;
        prev->freeSpace += prev->size;
        prev->next = temp->next;
    }
		
}
		
