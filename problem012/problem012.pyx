%cython
 
import time
 
cdef num_divisors(unsigned long int n):
    if n % 2 == 0: n = n/2
    cdef unsigned long divisors = 1
    cdef unsigned int count = 0
    while n % 2 == 0:
        count += 1
        n = n/2
    divisors = divisors * (count + 1)
    cdef unsigned int p = 3
    while n != 1:
        count = 0
        while n % p == 0:
            count += 1
            n = n/p
        divisors = divisors * (count + 1)
        p += 2
    return divisors
 
cdef find_triangular_index(unsigned int factor_limit):
    cdef unsigned long n = 1
    cdef unsigned long lnum, rnum
    lnum, rnum = num_divisors(n), num_divisors(n+1)
    while lnum * rnum < 500:
        n += 1
        lnum, rnum = rnum, num_divisors(n+1)
    return n
 
start = time.time()
index = find_triangular_index(500)
triangle = (index * (index + 1)) / 2
elapsed = (time.time() - start)
 
print "result %s returned in %s seconds." % (triangle,elapsed)
