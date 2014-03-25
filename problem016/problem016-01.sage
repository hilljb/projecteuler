import time
 
start = time.time()
a = 2^1000
s = sum(a.digits())
elapsed = time.time() - start
 
print "%s found in %s seconds" % (s,elapsed)
