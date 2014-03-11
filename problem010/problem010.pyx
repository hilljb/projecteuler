%cython
 
import time
from libc.stdlib cimport malloc, free
 
# a function to sum all prime numbers below a given number
cdef prime_sum(unsigned long n):
 
    if n < 2: return 0
    if n == 2: return 2
    # if n is even, use next lowest number
    if n % 2 == 0: n -= 1
 
    cdef bint *is_prime = <bint *>malloc(n * sizeof(bint))
 
    # set all to prime and then sieve
    cdef unsigned long int i,j,sum = 0
    i = 0
    while i < n:
        is_prime[i] = 1
        i += 1
    #for i in range(n): is_prime[i] = 1
    is_prime[0],is_prime[1] = 0,0
    i = 2
    while i < n ** 0.5 + 1:
        if is_prime[i] == 1:
            # add this to the sum
            sum += i
            # remove all multiples of i from prime list
            j = i ** 2
            while j <= n:
                is_prime[j] = 0
                j += i
        i += 1
    while i <= n:
        if is_prime[i]: sum += i
        i += 1
    free(is_prime)
 
    return sum
 
start = time.time()
sum = prime_sum(2000000)
elapsed = (time.time() - start)
 
print "found %s in %s seconds" % (sum,elapsed)
