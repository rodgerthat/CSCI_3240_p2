#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    int i, pgsz, *ip;
    unsigned char *cp;
    void *region;

    pgsz = getpagesize();
    printf("PGSZ %d\n",pgsz);


    // check the man page for in depth flags
    // NULL means we don't want to specify WHERE the memory is coming from
    // pgsz - number of pages you want for your project
    // file descriptor is -1, an in valid file descriptor. I'm not mapping a disk file
    // 
    region = mmap(NULL, pgsz, PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
    if (region == ((void *) -1)) // if mmap fails, returns -1
    {
        perror("mmap"); // call this now. don't wait
        return 1;
    }
    // if it works, returns pointer to region in memory we can use
    printf("region %p\n",region);   // prints out pointer to avail memory

    memset(region,'Z',pgsz);    // fill the whole region with 'Z'

    cp = (unsigned char *)region;           // 1000 bytes in 
    *(cp+1000) = 'a';           // goto this address +1000, and set that to an 'a' char

    ip = (int *)region;
    *(ip+251) = 65;  // region+1004

    cp = (unsigned char *)region;
    for (i=999; i < 1009; i++)  // Z a Z Z Z A 0 0 0 Z (all in hex)
    {
        printf("%02x ", *(cp+i));
    }
    printf("\n");

    return 0;
}
