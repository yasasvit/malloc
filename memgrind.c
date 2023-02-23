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

int err() {
    int x, *p, *q;
    int test = 4;
    
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

    case 4:
        p = (int *) malloc(sizeof(int) * 1000);
        q = (int *) malloc(sizeof(int) * 1000);
        free(p);
        free(q);
    }
    
    return EXIT_SUCCESS;

}

int main() {
    double totaltime = 0.0;
    for (int i = 0; i < 50; i++) {
        double testtime = test1();
        totaltime += testtime;
        // printf("Test %d: %.6f s\n", (i+1), testtime);
    }
    printf("Average Time: %.6f s\n", totaltime/50.0);
    totaltime = 0.0;

    for (int i = 0; i < 50; i++) {
        double testtime = test2();
        totaltime += testtime;
        // printf("Test %d: %.6f s\n", (i+1), testtime);
    }
    printf("Average Time: %.6f s\n", totaltime/50.0);
    totaltime = 0.0;

    for (int i = 0; i < 50; i++) {
        double testtime = test3();
        totaltime += testtime;
        // printf("Test %d: %.6f s\n", (i+1), testtime);
    }
    printf("Average Time: %.6f s\n", totaltime/50.0);
    totaltime = 0.0;

    // printf("%d\n", err());
    
    for (int i = 0; i < 50; i++) {
        double testtime = stressTest1();
        totaltime += testtime;
        // printf("Test %d: %.6f s\n", (i+1), testtime);
    }
    printf("Average Time: %.6f s\n", totaltime/50.0);
    totaltime = 0.0;
    
    for (int i = 0; i < 50; i++) {
        double testtime = stressTest2();
        totaltime += testtime;
        // printf("Test %d: %.6f s\n", (i+1), testtime);
    }
    printf("Average Time: %.6f s\n", totaltime/50.0);

    return EXIT_SUCCESS;
}
