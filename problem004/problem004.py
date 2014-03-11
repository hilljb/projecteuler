#!/usr/bin/python2

import time
 
def find_max_palindrome(min=100,max=999):
    max_palindrome = 0
    a = 999
    while a > 99:
        b = 999
        while b >= a:
            prod = a*b
            if prod > max_palindrome and str(prod)==(str(prod)[::-1]):
                max_palindrome = prod
            b -= 1
        a -= 1
    return max_palindrome
 
start = time.time()
L = find_max_palindrome()
elapsed = (time.time() - start)
 
print "%s found in %s seconds" % (L,elapsed)
