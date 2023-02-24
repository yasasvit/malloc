// This file contains test cases for which mymalloc/myfree should fail to allocate/free memory as requested.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mymalloc.h"

int main(int argc, char** argv) {
    int x, *p, *q;
    int test = argc > 1 ? atoi(argv[1]) : 0;
    
    switch (test) {
    // Must provide valid test number
    default:
        puts("Missing or invalid test number");
        return EXIT_FAILURE;
    
    // Cannot free an unallocated variable
    case 1:
        free(&x);
        break;

    // Cannot free an unallocated variable
    case 2:
        p = (int *) malloc(sizeof(int) * 10);
        free(p + 1);
        break;
    
    // Cannot free a variable twice
    case 3:
        p = (int *) malloc(sizeof(int) * 10);
        free(p);
        free(p);
        break;

    // Cannot allocate more than 4096 bytes
    // Cannot free a variable that was not successfully allocated
    case 4:
        p = (int *) malloc(sizeof(int) * 1500);
        free(p);
        break;

    case 5:
        p = (int *) malloc(sizeof(int) * 0);
        free (p);
        break;

    // Cannot allocate more than 4096 bytes total
    // Cannot free a variable that was not successfully allocated
    case 6:
        p = (int *) malloc(sizeof(int) * 750);
        q = (int *) malloc(sizeof(int) * 750);
        free(p);
        free(q);
    }
    
    return EXIT_SUCCESS;
}