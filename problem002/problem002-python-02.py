#!/usr/bin/python

import time

def fibonacci(n):
    """
    Compute the nth Fibonacci number in closed form.
    """
    p = (1+5.0**(0.5))/2.0
    return int((p**n)/(5**(0.5)) + 0.5)

i = 3
s = 0

start = time.time()

while True:
    f = fibonacci(i)
    if f > 4000000: break
    s += f
    i += 3

elapsed = time.time() - start

print s
print elapsed
