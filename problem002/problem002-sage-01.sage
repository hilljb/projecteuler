import time

start = time.time()

s = sum([i for i in fibonacci_xrange(4000000) if is_even(i)])

elapsed = time.time() - start

print "result %s returned after %s seconds" % (s, elapsed)
