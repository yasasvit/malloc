#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "mymalloc.h"

int main() {

}

long long test1() {
    // 1. malloc() and immediately free() a 1-byte chunk, 120 times.
    struct timeval start;
    gettimeofday(&start, NULL);
    for (int i = 0; i < 120; i++) {
        char* temp = mymalloc(1);
        free(temp);
    }
    struct timeval end;
    gettimeofday(&end, NULL);
    return (long long) (end.tv_sec - start.tv_sec); 
}

long long test2() {
    /* 2. Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to
deallocate the chunks. */ 
    char* temp[120];
    for (int i = 0; i < 120; i++) {
        temp[i] = malloc(1); // do we need to cast? 
    }
    for (int i = 0; i < 120; i++) {
        free(malloc[i]);
    }
}

// 3. Randomly choose between
// •Allocating a 1-byte chunk and storing the pointer in an array
// •Deallocating one of the chunks in the array (if any)
// Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.

long long test3() {
    int count = 0;
    struct timeval start;
    gettimeofday(&start, NULL);
    char* temp[120];
    int i = 0;
    while (count < 120) {
        int n = (rand() % 2); 
        if (n == 0) { // 
            temp[i] = malloc(1);
            i += 1; 
            count += 1
        } else { // free
            if (count > 0) {
                free(temp[i - 1]);
                i -= 1
            }
        }

    }

    struct timeval end;
    gettimeofday(&end, NULL);
    return (long long) (end.tv_sec - start.tv_sec); 
}