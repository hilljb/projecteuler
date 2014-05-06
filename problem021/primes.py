#!/usr/bin/python2

#   pype: Python Utilities for Project Euler
#   pype.primes - prime sieve / range factoring / sum of divisors
#   Jason B. Hill (jason@jasonbhill.com) code.jasonbhill.com
#   April 30, 2014

#   This program is free software: you can redistribute it and/or modify it
#   under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or (at your
#   option) any later version.
#
#   This program is distributed in the hope that it will be useful, but WITHOUT
#   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
#   License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

__author__ = 'Jason B. Hill (jason@jasonbhill.com)'
__copyright__ = 'Copyright (c) 2014'

import time
import math


###############################################################################
# Sieve class                                                                 #
# --------------------------------------------------------------------------- #
# Uses a sieve of Eratosthenes to form a list of all prime numbers below some #
# limit. Requires the math.sqrt function.                                     #
###############################################################################
class Sieve:
    """
    Creates a prime sieve and forms all primes less than some limit.
    """
    def __init__(self, limit):
        """
        Initialize a Sieve class member.

        INPUT:
        'limit' - an integer greater than or equal to 1.
        """
        # minimal error checking
        if not isinstance(limit, (int, long)):
            raise TypeError('Sieve limit must be an integer greater than 0.')
        if limit < 1:
            raise ValueError('Sieve limit must be an integer greater than 0.')

        # store the upper limit of the sieve
        self.limit = limit

        # form sieve
        self.sieve = [1] * self.limit

        # set values at indices 0 and 1 to 0 (0 and 1 are not prime)
        self.sieve[0] = 0
        if self.limit > 1:
            self.sieve[1] = 0

        # iterate up to square root of limit
        for j in range(4, self.limit, 2):
            self.sieve[j] = 0
        lastPrime = 1 # provides a new sieving point for each prime
        for key in range(3,int(math.sqrt(limit))+1,2):
            # determine if 'key' is prime
            if self.sieve[key]:
                # make multiples of 'key' composite
                for j in range(key*(lastPrime+2), self.limit, 2*key):
                    self.sieve[j] = 0
                lastPrime = key

        # count number of primes in sieve
        self.numPrimes = sum(self.sieve)


    def __repr__(self):
        """
        Machine representation of Sieve class object.
        """
        return "%s(limit=%s)" % (self.__class__, self.limit)


    def __str__(self):
        """
        String representation of Sieve class object.
        """
        return "%s object with %s primes below %s" % (self.__class__, self.numPrimes, self.limit)


    def isPrime(self, n):
        """
        Returns True if n is prime and False otherwise.
        """
        if self.sieve[n]: return True
        return False


    def setPrimes(self):
        """
        Creates a set from the primes in self.sieve.
        """
        S = set()
        for key,val in enumerate(self.sieve):
            if val: S.add(key)
        return S


    def listPrimes(self):
        """
        Creates a list from the primes in self.sieve.
        """
        L = []
        for key,val in enumerate(self.sieve):
            if val: L.append(key)
        return L



###############################################################################
# RangeFactor class                                                           #
# --------------------------------------------------------------------------- #
# Uses the Sieve class to factor a range of integers.                         #
###############################################################################
class RangeFactor:
    """
    Uses a prime sieve to factor a range of integers. Provides prime factor
    information plus single integer methods (sum of divisors, isPerfect) and
    multiple integer methods (lcm, gcd, coprime).
    """
    def __init__(self, start, stop=None, verbose=False):
        """
        Initialize a RangeFactor class member. The input here is somewhat like
        Python's built-in 'range' function, minus the step option. Factor info
        will be generated for all integers n satisfying start <= n < stop.

        Use the 'verbose=True' option to print progress report.

        INPUT:
        'start' - A positive integer. Defaults to zero.
        'stop' - A positive integer > 'start'.
        'verbose' - A Boolean value to trigger verbose output.
        """
        # parse input options
        if not stop:
            self.stop = start
            self.start = 0
        else:
            self.start = start
            self.stop = stop

        # minimal error checking
        if not isinstance(self.start, (int, long)):
            raise TypeError('RangeFactor start must be an integer.')
        if self.start < 0:
            raise ValueError('RangeFactor start must be greater than or equal to zero.')
        if not isinstance(self.stop, (int, long)):
            raise TypeError('RangeFactor stop must be an integer.')
        if self.stop < 0 or self.stop <= self.start:
            raise ValueError('RangeFactor stop must be greater than start.')

        # create the sieve
        if verbose:
            print __name__, ": creating sieve"
            stopwatch = time.time()
        self.sieve = Sieve(self.stop)
        if verbose:
            print __name__, ": sieve created in", time.time()-stopwatch, "seconds"

        # create factor dictionaries for each integer in given range
        if verbose:
            print __name__, ": creating factor records"
            stopwatch = time.time()
        self.factors = {}
        for i in range(self.start, self.stop, 1):
            self.factors[i] = {}
        if verbose:
            print __name__, ": factor records created in", time.time()-stopwatch, "seconds"
            stopwatch = time.time()
            print __name__, ": populating factor records"

        # insert prime factor info for each integer in range
        for p in self.sieve.listPrimes():
            n = (self.start//p)*p
            if n < self.start or n==0: n += p
            while n < self.stop:
                # include p in the factorization of n
                m = n
                e = 0
                while m % p == 0:
                    e += 1
                    m /= p
                self.factors[n][p] = e
                n += p
        if verbose:
            print __name__, ": factor records filled in", time.time()-stopwatch, "seconds"


    def sumDivisors(self, n):
        """
        Return the sum of the divisors of n, including 1 and n. To return the
        sum of the proper divisors, use self.sumProperDivisors(n).
        """
        if n < self.start or n >= self.stop:
            raise ValueError('sumDivisors argument must be in proper range')
        m = 1
        for p in self.factors[n].keys():
            m *= ((p**(self.factors[n][p]+1)-1)/(p-1))
        return m


    def sumProperDivisors(self, n):
        """
        Returns the sum of the proper divisors of n, including 1 but of course
        not including n. To return the sum of all divisors, including n, use
        self.sumDivisors(n).
        """
        return self.sumDivisors(n)-n


    def isPerfect(self, n):
        """
        Returns True if n is a perfect number.

        A perfect number is an integer n such that the sum of the proper
        divisors of n is n. For example, 28 is a perfect number.
        """
        if self.sumDivisors(n)-n == n: return True
        return False


    def gcd(self, n, m):
        """
        Returns the greatest common divisor of n and m.
        """
        if min([m,n]) < self.start or max([m,n]) >= self.stop:
            raise ValueError('greatest common divisor argument out of range')
        P = set(self.factors[m].keys()).intersection(set(self.factors[n].keys()))
        gcd = 1
        for p in P:
            gcd *= p**(min([self.factors[m][p], self.factors[n][p]]))
        return gcd


    def lcm(self, n, m):
        """
        Returns the least common multiple of n and m.
        """
        if min([m,n]) < self.start or max([m,n]) >= self.stop:
            raise ValueError('least common multiple argument out of range')
        return (n*m)/self.gcd(n,m)


    def areCoprime(self, n, m):
        """
        Returns True if n and m are coprime and returns False otherwise.
        """
        if min([m,n]) < self.start or max([m,n]) >= self.stop:
            raise ValueError('areCoprime argument out of range')
        P = set(self.factors[m].keys()).intersection(set(self.factors[n].keys()))       
        if len(P)==0: return True
        return False



