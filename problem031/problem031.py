#!/usr/bin/python

import time

# first, we need a dictionary of the coins that we're going to use
coinDict = {
    # level: value
    0: 200,
    1: 100,
    2: 50,
    3: 20,
    4: 10,
    5: 5,
    6: 2,
    7: 1
}

# now, we'll make our recursive function - this does ALL the work for us
def makeChange(total, subtotal=0, level=0, coinDict=coinDict, verbose=False):
    """
    Determines the number of ways to make change from the coins in coinDict totalling 'total'.
    
    INPUT:
        total - the total value (which value are we making change for)
        subtotal - the current value of coins in this solution
        level - the level of coinDict to consider now
        coinDict - a dictionary of coins by level:value.
    """
    # verbose output for debugging
    if verbose:
        print "level: %s subtotal: %s" % (level, subtotal)

    # get the value of the coin to be considered
    coinVal = coinDict[level]

    # if the value of the coin is 1, we're done with this path (no matter how many pennies are
    # needed or not needed)
    if coinVal == 1: return 1

    # we need to keep track of how many paths are below this node (gets summed recursively)
    valSum = 0
    
    # determine how many times to use the current coin
    for i in range(0,(total-subtotal)/coinVal+1,1):
        newSubTotal = subtotal + coinVal*i
        newLevel = level + 1
        valSum += makeChange(total, newSubTotal, newLevel, coinDict=coinDict, verbose=verbose)
        
    return valSum
    
start = time.time()
result = makeChange(200, coinDict=coinDict)
elapsed = time.time() - start

print "result %s found in %s seconds" % (result, elapsed)
