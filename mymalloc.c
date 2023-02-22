#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "mymalloc.h"

// Initialize array using macros
#define MEMSIZE 4096
// can make MEMSIZE double to avoid edge cases
static char memory[MEMSIZE]; // all zeros initially

// eager coalescing
void coalesce(char* ptr1, char* ptr2) {
    if (*ptr1 == 'n' || *ptr2 == 'n') {
        return;
    }

    short temp1;
    short temp2;
    memcpy(&temp1, ptr1 + 1, sizeof(short));
    memcpy(&temp2, ptr2 + 1, sizeof(short));
    short SIZE_BLOCK = temp1 + temp2 + 3; // 3 is size of metadata 
    memcpy(ptr1 + 1, &SIZE_BLOCK, sizeof(short));
}



void *mymalloc(size_t size, char *file, int line) {
   if (size < 1 || size > 4096) {
       printf("Requests for too much memory on this file %s from line %d\n", file, line);
       return NULL;
   }

   if ((memory[0])) {}
   else { // not initialized yet
        char* ptr = memory;
        *ptr = '@'; // resembles start of array
        *(ptr + 1) = 'y';
        short t4 = MEMSIZE - 4;
        memcpy(ptr + 2, &t4, sizeof(short));
        
   }

   // Assigning memory
   char* ptr = memory+1;
   int index = 0;
   while (ptr != NULL && (*ptr == 'y' || *ptr == 'n')) { // <- STILL NEED TO DO
        short temp;
        memcpy(&temp, ptr + 1, sizeof(short));
        if (*ptr == 'y' && size <= temp ){
            // Check if it fits
            *ptr = 'n'; // no longer available
            memcpy(ptr + 1, &size, sizeof(short));

            // initialize next node 
            char * next = (ptr + 3 + size);
            *next = 'y';
            short s2 = temp - size;  // size of next chunk <- DOUBLE CHECK
            memcpy(next + 1, &s2, sizeof(short));
            return ptr + 3;
        }
        ptr += (temp + sizeof(short) + 1);
        index += 1;
   }
   printf("Requests for too much memory on this file %s from line %d\n", file, line);
   return NULL;

}

void myfree(void *ptr, char *file, int line) {
    // ptr points to start of data now
    if (ptr == NULL) {
        printf("error\n");
        return;
    }
    char *temp = ptr - sizeof(short) - 1;
    if (temp == NULL) {
        printf("error\n");
        return;
    }
    printf("%c\n", *temp);
    // temp points to start of metadata now
    if (temp == NULL || *temp != 'n') {
        printf("Unable to free from file %s on line %d\n", file, line);
        return;
    }
    *temp = 'y';
    // coalesce next 2 terms
    // need to check OUT OF BOUNDS  <- STILL NEED TO DO
    short CURR_SIZE;
    memcpy(&CURR_SIZE, temp + 1, sizeof(short));
    char * next = (temp + 3 + CURR_SIZE);
    // coalesce current and next term if next term is valid
    if (next != NULL && (*next == 'y' || *next == 'n')) {
        coalesce(temp, next);
    }
    // get previous term
    char * prev = temp - 1;
    // EDGE CASES -> if temp is first chunk in array, then infinite loop <- STILL NEED TO DO
    while (true) {
        char c;
        memcpy(&c, prev, sizeof(char));
        if ((c == 'y' || c == 'n')) {
            coalesce(prev, temp); 
            break;
        } else if (c == '@') {
            break;
        }
        prev -= 1;
    }
    
}   
