#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "mymalloc.h"

// Initialize array using macros
#define MEMSIZE 4096
// can make MEMSIZE double to avoid edge cases
static char memory[MEMSIZE]; // all zeros initially

void print() {
    for (int i = 0; i < 150; i++) {
        printf("%c", memory[i]);
    }
    printf("\n");
}

void printmem() {
    int index = 1;
    while (index < 200) {
        printf("%c ", memory[index]);
        short temp;
        memcpy(&temp, &memory[index+1], sizeof(short));
        index += temp+3;
    }
    printf("\n");
}

void coalesce() {
    int index = 1;
    while (index < 4000) {
        // printf("loopcoalesce\n");
        if (memory[index] == 'n') {
            short size;
            memcpy(&size, &memory[index + 1], sizeof(short));
            index = (index) + (size + 3);
        } else if (memory[index] == 'y') {
            short sumEmpties;
            short yolo = index + 1;
            memcpy(&sumEmpties, &memory[index + 1], sizeof(short));
            index += 3 + sumEmpties;
            while (index < 4000 && memory[index] == 'y' ) {
                short current;
                memcpy(&current, &memory[index + 1], sizeof(short));
                sumEmpties = (sumEmpties + 3 + current);
                index += current + 3;
            }
            memcpy(&memory[yolo], &sumEmpties, sizeof(short));
        }
    }
}

// void lazy_coalesce() {
//     char *temp = memory + 3;
//     short size;
//     memcpy(&size, temp + 1, sizeof(short));
//     char* tempNext = memory + 3 + size;
//     while (tempNext < MEMSIZE - 100 && (*tempNext == 'y' || *tempNext == 'n')) {
//         if (coalesce(temp, tempNext) == true) {
//             short t2;
//             memcpy(&t2, tempNext + 1, sizeof(short));
//             tempNext = tempNext + 3 + t2;
//         } else {
//             temp = tempNext;
//             short t2;
//             memcpy(&t2, tempNext + 1, sizeof(short));
//             tempNext = tempNext + 3 + t2;
//         }
//     }
// }

// eager coalescing





void *mymalloc(size_t size, char *file, int line) {
    // printmem();

   if (size < 1 || size > 4096) {
       printf("ERROR: Requests for invalid memory amount on this file %s from line %d\n", file, line);
       // exit(1);
       return NULL;
   }
  
   if (*(memory) != '@') {
        *(memory) = '@'; // resembles start of array
        *(memory + 1) = 'y';
        short t4 = MEMSIZE - 100;
        memcpy(memory + 2, &t4, sizeof(short));
   }

    int index = 1;
   // Assigning memory
   char* ptr = NULL;
   bool b = true;
   short temp;
//    print()
   while (index < 4000 && b) { // <- ptr > memory
        
        // printf("%d\n",temp);
        if (memory[index] == 'n') {
            memcpy(&temp, &memory[index + 1], sizeof(short));
            index += 3 + temp;
        } else if (memory[index] == 'y'){
            memcpy(&temp, &memory[index + 1], sizeof(short));
            if (size > temp) {
                index += (temp + 3);
            } else {
                ptr = &memory[index];
                b = false;
            }
        } 
   }
   if (ptr == NULL) {
        printf("ERROR: Not enough memory available to complete request on this file %s from line %d\n", file, line);
        return NULL;
   }

     *ptr = 'n';
     short *result = (short*) (ptr + 1);
    short oldSize; 
    memcpy(&oldSize, result, sizeof(short));
    if (size + 4 > oldSize) {
    } else {
        memcpy(result, &size, sizeof(short));
        char c = 'y';
        memcpy(&ptr[3 + size], &c, sizeof(char));
        oldSize = (oldSize) - (size + 3);
        memcpy(&ptr[4 + size], &oldSize, sizeof(short));
    }

    return (ptr + 3);

   // set block to free

//    lazy_coalesce();
//    end = memory + 3900;
//    while (ptr < end) { // <- ptr > memory
//         short temp;
//         memcpy(&temp, ptr + 1, sizeof(short));
//         // printf("%d\n",temp);
//         if (*ptr == 'y'){
//             printf("ffff\n");
//             printf("%hi\n", temp);
//             if (size <= temp ) {
//             // Check if it fits
//             // printf("%d\n", index);
//             *ptr = 'n'; // no longer available
//             memcpy(ptr + 1, &size, sizeof(short));
//             // initialize next node 
//             char * next = (ptr + 3 + size);
//             *next = 'y';
//             short s2 = temp - size;  // size of next chunk <- DOUBLE CHECK
//             memcpy(next + 1, &s2, sizeof(short));
//             return ptr + 3;
//             }
//         }
//         ptr += (temp + sizeof(short) + 1);
//         index += 1;
        
//    }

   printf("ERROR: Not enough memory available to complete request on this file %s from line %d\n", file, line);
   //exit(1);
   return NULL;

}

void myfree(void *ptr, char *file, int line) {
    char* start = memory;
    char* end = memory + 4095;
    // ptr points to start of data now
    if (ptr < start || ptr >= end) {
        printf("ERROR: Unable to free unallocated pointer on file %s on line %d\n", file, line);
        //exit(1);
        return;
    }
    
    int index = 1;
    while (index < 4000) {
        // printf("loopfree\n");
        if (memory[index] == 'n') {
            void * startData = &memory[index + 3];
            if (startData == ptr) {
                memory[index] = 'y';
                coalesce();
                return;
            } else {
                short size;
                memcpy(&size, &memory[index + 1], sizeof(short));
                index = (index) + (size + 3);
            }
        } else if (memory[index] == 'y') {
            short size;
            memcpy(&size, &memory[index + 1], sizeof(short));
            index = (index) + (size + 3);
        } else {
            printf("ERROR: Unable to free unallocated pointer on file %s on line %d\n", file, line);
            return;
        }

    }

    printf("ERROR: Unable to free unallocated pointer on file %s on line %d\n", file, line);
    return;
    
}   

