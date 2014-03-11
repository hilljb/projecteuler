%cython
 
import time
 
cdef square_of_sum(unsigned int n):
    cdef unsigned long int sum = ((n+1)*n)/2
    cdef unsigned long int squared = sum**2
    return squared
 
cdef sum_of_squares(unsigned int n):
    cdef unsigned long int sum = 0
    cdef unsigned int iter = 1
    while iter <= n:
        sum += iter**2
        iter += 1
    return sum
 
cdef difference(unsigned int n):
    return square_of_sum(n) - sum_of_squares(n)
 
start = time.time()
diff = difference(100)
elapsed = (time.time() - start)
 
print "result %s returned in %s seconds." % (diff,elapsed)
