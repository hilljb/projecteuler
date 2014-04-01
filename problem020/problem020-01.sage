import time
 
start = time.time()
 
s = sum(factorial(100).digits())
 
elapsed = time.time() - start
 
print "Solution %s found after %s seconds" % (s,elapsed)
