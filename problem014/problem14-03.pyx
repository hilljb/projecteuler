%cython
 
import time
from libc.stdlib cimport malloc, free
 
cdef find_max_collatz(unsigned long int max):
    cdef int *collatz_length = <int *>malloc(max * sizeof(int))
    cdef int *TO_ADD = <int *>malloc(600 * sizeof(int))
    cdef unsigned long iter, j, m, n, s, p, ind, new_length, max_length = 0
 
    # set initial collatz lengths and TO_ADD numbers
    iter = 0
    while iter < max:
        collatz_length[iter] = 0
        iter += 1
    collatz_length[1] = 1
    iter = 0
    while iter < 600:
        TO_ADD[iter] = 0
        iter += 1
 
    # iterate to max and find collatz lengths
    iter = 1
    while iter < max:
        n,s = iter,0
        while n > max - 1 or collatz_length[n] < 1:
            TO_ADD[s] = n
            if n % 2 == 0: n = n/2
            else: n = 3*n + 1
            s += 1
        # collatz length now known from previous calculations
        p = collatz_length[n]
        j = 0
        while j < s:
            m = TO_ADD[j]
            TO_ADD[j] = 0
            if m < max:
                new_length = collatz_length[n] + s - j
                collatz_length[m] = new_length
                if new_length > max_length:
                    max_length = new_length
                    ind = m
            j += 1
        iter += 1
 
    free(collatz_length)
    free(TO_ADD)
    return ind
 
start = time.time()
max_collatz = find_max_collatz(1000000)
elapsed = (time.time() - start)
print "found %s in %s seconds" % (max_collatz,elapsed)
