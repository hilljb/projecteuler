%cython
 
import time
 
cdef prod_triplet_w_sum(unsigned int n):
    cdef unsigned int i,j,k
    i = 1
    while i < n:
        j = 1
        while j < n - i:
            k = n - i - j
            if i**2 + j**2 == k**2:
                return i*j*k
            j += 1
        i += 1
    return 0
 
start = time.time()
product = prod_triplet_w_sum(1000)
elapsed = (time.time() - start)
 
print "found %s in %s seconds" % (product,elapsed)
