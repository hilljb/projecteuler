%cython

import time

cdef unsigned long s,i,j

start = time.time()

for i in range(100000):
    s = 0
    for j in range(3,1000,3): s += j
    for j in range(5,1000,5):
        if j % 3 != 0: s += j

elapsed = time.time() - start

print "result %s returned in %s seconds for 100000 iterations." % (s,elapsed)
