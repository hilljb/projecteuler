%cython
 
import time
from libc.stdlib cimport malloc, free
 
# a function to sum all prime numbers below a given number
cdef fast_nth_prime(unsigned long n,unsigned long limit = 125000):
    cdef bint *primes = <bint *>malloc(limit * sizeof(bint))
    primes[0] = 0
    primes[1] = 0
    cdef unsigned long count = 0
    cdef unsigned long j, index = 0
    while index < limit:
        primes[index] = 1
        index += 1
    index = 2
    while index < limit:
        if primes[index] == 1:
            j = index ** 2
            while j < limit:
                primes[j] = 0
                j += index
            count += 1
        if count == n:
            free(primes)
            return index
        index += 1
    free(primes)
    return False
 
start = time.time()
prime = fast_nth_prime(10001)
elapsed = (time.time() - start)
 
print "found %s in %s seconds" % (prime,elapsed)
