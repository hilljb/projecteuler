#!/usr/bin/python

import time

start = time.time()

s1 = set(range(0,1000,3))
s2 = set(range(0,1000,5))
ss = s1.union(s2)
s = sum(ss)

elapsed = time.time() - start

print "result %s returned in %s seconds" % (s,elapsed)
