%cython
 
import time
 
cdef is_palindrome(unsigned int num):
    cdef unsigned int reversed = 0
    cdef unsigned int original = num
 
    if num < 10: return True
    if num % 10 == 0: return False
 
    while num >= 1:
        reversed = (reversed * 10) + (num % 10)
        num = num/10
 
    if original == reversed: return True
    else: return False
 
cdef find_max_palindrome():
    cdef unsigned int max_palindrome = 0
    cdef unsigned int a = 999
    cdef unsigned int b = 999
    cdef unsigned int prod
 
    while a > 99:
        b = 999
        while b >= a:
            prod = a*b
            if prod > max_palindrome and is_palindrome(prod):
                max_palindrome = prod
            b = b -1
        a = a - 1
 
    return max_palindrome
 
start = time.time()
L = find_max_palindrome()
elapsed = (time.time() - start)
 
print "%s found in %s seconds" % (L,elapsed)
