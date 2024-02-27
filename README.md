Names: Pratyoy Biswas, Yasasvi Tallapaneni

# Test Plan:
## Required Library Properties:
To check that our ``mymalloc`` library runs as intended, we shall test that
1. ``mymalloc()`` is able to allocate memory (so as long as the memory requested is at least 1 byte, but not too large).
2. ``mymalloc()`` allocate enough memory, as requested by the user.
3. ``myfree()`` is able to free any previously allocated memory, but cannot free unallocated memory.
4. ``myfree()`` is able to coalesce adjacent unallocated chunks of memory into a single chunk.

## Correctness Testing:
The test cases are split into two files: ``good.c`` and ``bad.c``. ``good.c`` contains test cases for which ``mymalloc()`` and ``myfree()`` should be able to successfully allocate or free memory. ``bad.c`` contains test cases for which ``mymalloc()`` and ``myfree()`` should fail to allocate or free memory.

The tests performed in ``good.c`` are:
1. Small amount of memory (1 byte) is allocated then freed correctly. (Properties #1, #2, #3)
2. Large amount of memory (3600 bytes) is allocated then freed correctly. (Properties #1, #2, #3)
3. A large amount of memory (2500 bytes) is allocated. This creates a chunk of allocated memory of size 2500 bytes, and a free chunk of memory of size 1596 bytes. Then, the allocated memory is freed and another large amount of memory (3000 bytes) is allocated and freed. This is only possible if the freed blocks of memory are being correctly coalesced. (Properties #1, #2, #3, #4)

The tests performed in ``bad.c`` are:
1. We attempt to free unallocated memory. (Property #3)
2. We attempt to free memory that is not the memory that has already been allocated. (Property #3)
3. We attempt to free the same allocated memory twice. (Property #3)
4. We attempt to allocate memory that exceeds the capacity. (Property #1)
5. We attempt to allocate less than 1 byte. (Property #1)
6. We attempt to allocate two blocks of memory with a combined size greater than the capacity. (Property #1)

When ``make`` is ran, three objects are created, two of them being ``good`` and ``bad``, corresponding to the test cases in ``good.c`` and ``bad.c``. To run each test case described above, we run ``./good [test#]`` or ``./bad [test#]``, where ``[test#]`` is the test number as ordered above.

Our tests covered all design properties, and our library passed all tests. All errors are reported as intended (described in the following section).


# Error Handling:
1. If the size provided to ``mymalloc()`` is nonpositive or too large, the error message provided is "ERROR: Requests for invalid memory amount".
2. If there is not enough available memory for ``mymalloc()``, the error message provided is "ERROR: Not enough memory available to complete request".
3. If there is the given pointer cannot be found in memory, the error message provided is "ERROR: Unable to free from file".

Each error message also prints the file name and line number. In the event of an error, the user's program continues to run.


# Performance Testing:
## Stress Test 1:
1. Initialize ``char *`` array of size 3000 
2. Initialize a variable size which keeps track of total amount of memory allocated and variable index that keeps track of indices we have allocated to 
3. Iterate through array from indices 0 to 99:
    - Randomly generate value between 1 and 100 to allocate. 
    - if ``size + value > 3000``: break out of loop (3000 because our implementation only does ``malloc()`` for limited size).
    - Set that index of char * array equal to ``malloc()`` call
    - Increment size by value
4. Iterate through array and free from indices ``0`` to ``index - 1``, inclusive.

This stress test:
- Tests functionality of ``mymalloc()`` and ``myfree()`` for different sizes 
- Ensures that ``mymalloc()`` works for at least a size of 500 bytes

## Stress Test 2:
1. Initialize single ``char * ptr``
2. Iterate through for loop from values of 0 to 9999 inclusive 
    - If ``index`` is even:
        - Generate random number from 1 to 1000 and allocate for that size
    - If ``index`` is odd:
        - Free ``ptr``

This stress test:
- Tests functionality of ``mymalloc()`` and ``myfree()`` for small and large sizes
- Tests if ``myfree()`` is freeing properly, as we should always be able to allocate since we are freeing after every ``malloc()`` based on design of our stress test 
- Tests if ``mymalloc()`` and ``myfree()`` work for large number of calls, as each function is called 5000 times each

These 2 stress tests (along with the 3 performance tests described in the assignment description) are performed in ``memgrind.c``. ``memgrind.c`` contains 5 methods: ``test1()``, ``test2()``, ``test3()``, ``stressTest1()``, and ``stressTest2()``. Each function returns a ``double``: the time (in seconds) that it took to run the test. When the ``make`` command is run, one of the object files produced is ``program``. Upon running program (with ``./program``), the 5 performance tests are ran 50 times each, and the time spent on each is printed out, as well as the average time needed (stress tests #1 and #2 are labeled "Performance Test #4" and "Performance Test #5", respectively). We see that all tests run successfully, with every test finishing in well under 1 second.
