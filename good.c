// This file contains test cases for which mymalloc/myfree should be able to successfully allocate/free memory as requested.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymalloc.h"

int main(int argc, char** argv) {
    void *p, *q;
    int test = argc > 1 ? atoi(argv[1]) : 0;;
    
    switch (test) {

    // Must provide valid test number
    default:
        puts("Missing or invalid test number");
        return EXIT_FAILURE;
    
    // Can allocate and free variable of minimum size 1 byte
    case 1:
        p = (void *) malloc(1);
        free(p);
        break;

    // Can allocate and free variable of large size (3600 bytes)
    case 2:
        p = (void *) malloc(3600);
        free(p);
        break;
    
    // Coalesce working
    case 3:
        p = (void *) malloc(2500);
        free(p);
        q = (void *) malloc(3000);
        free(q);
        break;
    }
    
    return EXIT_SUCCESS;
}