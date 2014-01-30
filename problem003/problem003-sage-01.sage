import time

start = time.time()
a = max(ZZ(600851475143).prime_factors())
elapsed = (time.time() - start)
 
print "result %s returned after %s seconds." % (a, elapsed)
