#!/usr/bin/python

import time


# The sum of all numbers from 1 to n is (n*(n+1))/2. Using this formula, we can
# find the answer in the following way.

# Notice that all of the multiples of 3 look like this:
#   3 + 6 + 9 + ... + 996 + 999 = 3 * (1 + 2 + ... + 333) = 3 * (333*334)/2

# Similarly, the sum of all multiples of 5 looks like this:
#   5 + 10 + 15 + ... + 995 = 5 * (1 + 2 + ... + 199) = 5 * (199*200)/2

# If we were to add these two integers together, we would be counting multiples
# of 15 twice (once as multiples of 3 and once as multiples of 5). So, we take
# the two numbers above and subtract an instance of all multiples of 15:
#   15 + 30 + ... + 990 = 15 * (1 + 2 + ... + 66) = 15 * (66*67)/2

start = time.time()

s = ((3*333*334)/2) + ((5*199*200)/2) - ((15*66*67)/2)
    
elapsed = time.time() - start

print "result %s found in %s seconds" % (s, elapsed)
