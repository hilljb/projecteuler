#!/usr/bin/python

import time

def sum_3_5(n):
    sum = 0
    for i in range(3,n,3): sum += i
    for i in range(5,n,5):
        if i % 3 != 0: sum += i
    return sum

start = time.time()
for i in range(100000):
    sum = sum_3_5(1000)
elapsed = (time.time() - start)

print "result %s returned in %s seconds for 100000 iterations." % (sum,elapsed)
