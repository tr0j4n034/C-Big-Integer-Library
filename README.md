# C-Big-Integer-Library
C++ Big Integer library for programming contests and medium scale computations

What is included:

Basic integer operations:
- Addition and subtraction of two numbers in O(N + M) time
- Multiplication of two numbers in O(max(N, M)^1.58) time using Karatsuba's algorithm
- Division and modulo of two numbers in O(N * M) time
- Conversion of data types, manipulations on integers

Extra:
- Bitwise operations: and/or/xor/not/...
- Binary shifts
- Math functions:
    1) min/max operators
    2) square root calculation in O(N^(1 + 1.58)) using binary search (other faster methods can be used here)
    3) cube root calculation
    4) large factorials, checking if a number is a factorial of some nonnegative integer
- Generation of random integers in particular range and length
- Primes
    1) primality check
    2) prime generation by using Fermat witness trials
    3) prime generation by using Euler's method
    4) prime generation by using Miller-Rabin primality test
    3) generation of random numbers in particular range
    4) generation of random primes in particular range:
        1) generation of 100-bit random primes using Fermat trials in ~1.5 seconds on average
        2) generation of 200-bit random primes using Fermat trials in ~4 seconds on average
        3) generation of 100-bit random primes using Miller-Rabin test in ~0.7 seconds on average
        4) generation of 200-bit random primes using Miller-Rabin test in ~1.5 seconds on average
    



