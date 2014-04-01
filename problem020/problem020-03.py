#!/usr/bin/python

import time


def factorial(n):
    return reduce(lambda x,y: x*y, range(1,n+1,1))

def sum_digits(n):
    return sum([int(i) for i in str(n)])
 
start = time.time()
 
sumfac = sum_digits(factorial(100))
 
elapsed = time.time() - start
 
print("%s found in %s seconds") % (sumfac,elapsed)
