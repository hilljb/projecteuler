%cython

import time

cdef unsigned long s,i,j

start = time.time()

for i in range(100000):
    s = 0
    for j in range(1000):
        if j%3==0 or j%5==0: s+= j

elapsed = (time.time() - start)

print "result %s returned in %s seconds for 100000 iterations." % (s,elapsed)
