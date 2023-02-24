#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
#include "mymalloc.h"

// 1. malloc() and immediately free() a 1-byte chunk, 120 times.
double test1() {
    clock_t cl = clock();
    for (int i = 0; i < 120; i++) {
        char* temp = malloc(1);
        free(temp);
    }

    cl = clock() - cl;
    return (((double) cl) / CLOCKS_PER_SEC);
}

// 2. Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to
//    deallocate the chunks. 
double test2() {
    clock_t cl = clock();
    char* temp[120];
    for (int i = 0; i < 10; i++) {
        temp[i] = malloc(1); // do we need to cast? 
    }
    for (int i = 0; i < 10; i++) {
        free(temp[i]);
    }

    cl = clock() - cl;
    return (((double) cl) / CLOCKS_PER_SEC);

}

// 3. Randomly choose between
// •Allocating a 1-byte chunk and storing the pointer in an array
// •Deallocating one of the chunks in the array (if any)
// Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
double test3() {
    int count = 0;
    clock_t cl = clock();
    char* temp[120];
    int i = 0;
    while (count < 120) {
        int n = (rand() % 2); 

        if (n == 0) { 
            // printf("%d ", count);
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

    for (int j = i-1; j >= 0; j--) {
        free(temp[j]);
    }

    cl = clock() - cl;
    return (((double) cl) / CLOCKS_PER_SEC); 
}

// Stress Test 1 -> Look at README.md for more info
double stressTest1() {
    clock_t cl = clock();

    char* temp[3000];
    int index = 0;
    int size = 0;
    for (int i = 0; i < 3000; i++) {
        int s = rand() % 100 + 1; // Generates random number from 1 to 100
        if (s + size > 3000) {
            break;
        }
        temp[i] = malloc(s);
        size += s;
        index += 1;
    } 
    for (int i = 0; i < index; i++) {
        free(temp[i]);
    }

    cl = clock() - cl;
    return (((double) cl) / CLOCKS_PER_SEC); 

}

// Stress Test 2 -> Look at README.md for more info
double stressTest2() {
    clock_t cl = clock();
    char * ptr;
    // long long total = 0L;
    for (int i = 0; i <= 50000; i++) {
        // printf("%d\n", i);
        if (i % 2 == 0) {
            int temp = rand() % 100 + 1;
            // total += temp;
            // printf("%d\n", temp);
            // printf("%lld\n", total);
            ptr = malloc(temp);
        } else {
            free(ptr);
        }
    }

    cl = clock() - cl;
    return (((double) cl) / CLOCKS_PER_SEC); 
}

int main(int argc, char** argv) {
    printf("Performance Test #1\n");
    double totaltime = 0.0;
    for (int i = 0; i < 50; i++) {
        double testtime = test1();
        totaltime += testtime;
        printf("Test %02d: %.6f s\n", (i+1), testtime);
    }
    printf("Average: %.6f s\n\n", totaltime/50.0);
    
    printf("Performance Test #2\n");
    totaltime = 0.0;
    for (int i = 0; i < 50; i++) {
        double testtime = test2();
        totaltime += testtime;
        printf("Test %02d: %.6f s\n", (i+1), testtime);
    }
    printf("Average: %.6f s\n\n", totaltime/50.0);
   
    printf("Performance Test #3\n");
    totaltime = 0.0;
    for (int i = 0; i < 50; i++) {
        double testtime = test3();
        totaltime += testtime;
        printf("Test %02d: %.6f s\n", (i+1), testtime);
    }
    printf("Average: %.6f s\n\n", totaltime/50.0);
    
    printf("Performance Test #4\n");
    totaltime = 0.0;    
    for (int i = 0; i < 50; i++) {
        double testtime = stressTest1();
        totaltime += testtime;
        printf("Test %02d: %.6f s\n", (i+1), testtime);
    }
    printf("Average: %.6f s\n\n", totaltime/50.0);
    
    printf("Performance Test #5\n");
    totaltime = 0.0;
    for (int i = 0; i < 50; i++) {
        double testtime = stressTest2();
        totaltime += testtime;
        printf("Test %02d: %.6f s\n", (i+1), testtime);
    }
    printf("Average: %.6f s\n", totaltime/50.0);

    return EXIT_SUCCESS;
}
