import time
 
start = time.time()
 
i = 1
triangle = 1
while True:
    if len(triangle.divisors()) > 500: break
    i += 1
    triangle += i
 
elapsed = (time.time() - start)
print triangle
print "found %s in %s seconds" % (i,elapsed)
