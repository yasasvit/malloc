#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "mymalloc.h"

double test1() {
    // 1. malloc() and immediately free() a 1-byte chunk, 120 times.
    time_t start = time(NULL);
    for (int i = 0; i < 120; i++) {
        char* temp = malloc(1);
        free(temp);
    }
    return difftime(time(NULL), start);
}

double test2() {
    /* 2. Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to
deallocate the chunks. */ 
    time_t start = time(NULL);
    char* temp[120];
    for (int i = 0; i < 120; i++) {
        temp[i] = malloc(1); // do we need to cast? 
    }
    for (int i = 0; i < 120; i++) {
        free(temp[i]);
    }
    return difftime(time(NULL), start);

}

// 3. Randomly choose between
// •Allocating a 1-byte chunk and storing the pointer in an array
// •Deallocating one of the chunks in the array (if any)
// Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.

double test3() {
    int count = 0;
    time_t start = time(NULL);
    char* temp[120];
    int i = 0;
    while (count < 120) {
        int n = (rand() % 2); 
        if (n == 0) { // 
            temp[i] = malloc(1);
            i += 1; 
            count++;
        } else { // free
            if (i > 0) {
                free(temp[i - 1]);
                i--;
            }
        }

    }
    return difftime(time(NULL), start); 
}

int err() {
    int x, *p;
    int test = 1;
    
    switch (test) {
    default:
        puts("Missing or invalid test number");
        return EXIT_FAILURE;
    
    case 1:
        free(&x);
        break;
    case 2:
        p = (int *) malloc(sizeof(int) * 10);
        free(p + 1);
        break;
    
    case 3:
        p = (int *) malloc(sizeof(int) * 10);
        free(p);
        free(p);
        break;
    }
    
    return EXIT_SUCCESS;

}

int main() {
    // printf("%f\n", test1());
    // printf("%f\n", test2());
    // printf("%f\n", test3());
    err();
}
