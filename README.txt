Names: Pratyoy Biswas, Yasasvi Tallapaneni
NetIDs: pb600, yt397

TEST PLAN:

ERROR HANDLING:
1. If the size provided to mymalloc is nonpositive or too large, the error message provided is "ERROR: Requests for invalid memory amount".
2. If there is not enough available memory for mymalloc, the error message provided is "ERROR: Not enough memory available".
3. If there is nothing to free at the given pointer in myfree, the error message provided is "ERROR: Unable to free from file".
Each error message also prints the file name and line number.
In the case of an error, the program prints the error message and then immediately terminates.

PERFORMANCE TESTING:
Stress Test 1:
1. Initialize char * array of size 3000 
2. Initialize a variable size which keeps track of total amount of memory allocated and variable 
   index that keeps track of indices we have allocated to 
3. Iterate through array from indices 0 to 99:
    - Randomly generate value between 1 and 100 to allocate. 
    - if size + value > 3000: break out of loop -> 3000 bc our implementation only does malloc for limited size  
    - Set that index of char * array equal to malloc() call
    - Increment size by value
4. Iterate through array and free from indices 0 to index - 1 inclusive

This stress test:
    - Tests functionality of mymalloc and myfree for different sizes 
    - Ensures that mymalloc works for at least a size of 500 bytes

Stress Test 2:
1. Initialize single char * ptr
2. Iterate through for loop from values of 0 to 9999 inclusive 
    - If index is even:
        - Generate random number from 1 to 1000 and allocate for that size
    - If index is odd:
        - Free ptr

This stress test:
    - Tests functionality of mymalloc and myfree for small and large sizes
    - Tests if myfree() is freeing properly, as we should always be able to allocate since we
      are freeing after every malloc based on design of our stress test 
    - Tests if mymalloc() and myfree() work for large number of calls, as each function is called 
      5000 times each
