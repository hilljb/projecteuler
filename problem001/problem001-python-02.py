#!/usr/bin/python

import time

start = time.time()

s = 0

# add in all multiples of 3
for i in range(3,1000,3): s += i

# Add in multiples of 5 that are no also multiples of 3.
# This includes numbers of the form 5+15n and 10+15n between 0 and 1000.
for i in range(5,1000,15): s += i
for i in range(10,1000,15): s += i

elapsed = time.time() - start

print "result %s returned in %s seconds" % (s,elapsed)
