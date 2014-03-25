#!/usr/bin/python

import time
import operator

gridSize = [20,20]

# If r moves need to be made to the right and d moves need to be made down,
# then a total of r+d moves need to be made. In order, we have the choice of
# (r+d) choose d moves to decide which moves are down.

def nCr(n, r):
    """
    Old fashioned n-choose-r function.
    """
    if r > n-r:
        p = reduce(operator.mul, range(r+1,n+1,1), 1)
        q = reduce(operator.mul, range(1,n-r+1,1), 1)
    else:
        p = reduce(operator.mul, range(n-r+1,n+1,1), 1)
        q = reduce(operator.mul, range(1,r+1,1), 1)
    return p/q

start = time.time()
# if the grid is 20x20, there are 19 moves right and 19 down
result = nCr(40,20)
elapsed = time.time() - start

print "result %s found in %s seconds" % (result, elapsed)
