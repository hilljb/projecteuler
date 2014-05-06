#!/usr/bin/python2

import time
import primes

start = time.time()

# factor all numbers from 1 to 10000
F = primes.RangeFactor(10000)

# compute the sum of all proper divisors for integers from 1 to 10000
S = [F.sumProperDivisors(i) for i in range(10000)]

# find amicable pairs and add to a set
pairs = set()
for i in range(2,10000):
    if i in pairs:
        pass
    else:
        if S[i] < 10000 and S[i]!=i and S[S[i]]==i:
            pairs.add(i)
            pairs.add(S[i])

elapsed = time.time() - start

print "Found result %s in %s seconds" % (sum(pairs), elapsed)
