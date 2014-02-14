
/*
 * Jason B. Hill / jason@jasonbhill.com
 * pe451.c / solves Project Euler problem 451
 * build: gcc pe451.c -fopenmp -O3 -o pe451
 * execute: ./pe451
 *
 * I logged in to see that problem 451 had around 90 solutions, and decided to
 * attempt to be one of the first 100 solvers to enter the proper solution. As
 * such, I coded this a bit quickly. A "clean" solution would make use of the
 * Chinese Remainder Theorem, and the timing could probably be brought down
 * a tiny bit. But, all things considered, this runs very fast itself.
 *
 * Problem: Consider the number 15. There are eight positive integers less than
 * 15 which are coprime to 15: 1, 2, 4, 7, 8, 11, 13, 14. The modular inverses
 * of these numbers modulo 15 are: 1, 8, 4, 13, 2, 11, 7, 14 because
 * 1*1 mod 15=1
 * 2*8=16 mod 15=1
 * 4*4=16 mod 15=1
 * 7*13=91 mod 15=1
 * 11*11=121 mod 15=1
 * 14*14=196 mod 15=1
 * Let I(n) be the largest positive number m smaller than n-1 such that the
 * modular inverse of m modulo n equals m itself. So I(15)=11. Also I(100)=51
 * and I(7)=1. Find the sum of I(n) for 3<=n<=2·10**7.
 *
 * The solution is documented in the code below. The code is in C with OpenMP.
 *
 * The result is found in 28 seconds on a 20-core Xeon and and 2:48 on a 2-core
 * core i7. Here is some of the output:
 * prime sieve created - 0.110000 seconds
 * list of 1270607 primes created - 0.050000 seconds
 * list of prime factors created for integers <= 20000000 - 5.350000 seconds
 * prime factor exponents computed for all integers - 0.980000 seconds
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


/*****************************************************************************/
/* The following structs and routines are for integer factorization          */
/*****************************************************************************/

/*
 * Notes on factoring:
 *
 * We need to consider the prime factorization of positive integers less than
 * 2*10^7. How many distinct prime factors can such numbers have? That's easy.
 * Since the product of the 8 smallest primes (2*3*5*7*11*13*17*19 = 9,699,690)
 * is less than 2*10^7 and the 9 smallest primes (9,699,690*23 = 223,092,870)
 * is greater than 2*10^7, we know that each positive integer less than 2*10^7
 * can only have 8 distinct prime factors. Let's create a C-struct that can
 * keep track of this data for each factored integer.
 */

/*
 * A struct to hold factor information for an integer.
 * p holds a list of distinct prime factors. (at most 8)
 * e holds a list of exponents for the prime factors in p.
 * num_factors says how long the lists p and e are.
 */
struct factors_t {
    uint64_t    p[8]; // list of distinct primes
    uint8_t     e[8]; // list of exponents for the primes p[]
    uint64_t    pp[8]; // prime power factor (p[i]**e[i])
    uint8_t     num_factors; // how many distinct prime factors
};


/*
 * More notes on factoring:
 *
 * Every positive integer n has a prime factor <= sqrt(n). We use this fact to
 * build a prime sieve. First, we construct a function to return the square
 * root of a uint64_t. Then, we'll use that function to create a sieve (which
 * is returned as a pointer/list of uint8_ts... effectively Booleans).
 */

/*
 * Return the square root of a uint64_t
 */ 
uint64_t sqrt_uint64(uint64_t n) {
    uint8_t             shift = 1;
    uint64_t            res, s;

    while ((1<<shift) < n) shift += 1;
    res = (1<<((shift>>1) + 1));
    while (1) {
        s = (n/res + res)/2;
        if (s >= res) return res;
        res = s;
    }
}


/*
 * Return a prime sieve identifying all primes <= limit.
 * This is just a list of uint8_t's where 0 means the index is composite and
 * 1 means the index is prime.
 */ 
uint8_t * prime_sieve(uint64_t limit) {
    uint8_t            *sieve; // this will be the pointer that is returned
    uint64_t            i,j;
    uint64_t            s = sqrt_uint64(limit);

    // allocate memory for sieve
    sieve = malloc((limit + 1) * sizeof(uint8_t));

    // set initial values in the sieve
    sieve[0] = 0; sieve[1] = 0; sieve[2] = 1;

    // set other initial odd values in sieve to 1, even values to 0.
    for (i=3;i<=limit;i++) {
        if (i%2==0) sieve[i] = 0;
        else sieve[i] = 1;
    }

    // unset composite numbers (evens are already unset)
    for (i=3;i<=(s+1);i=i+2) {
        if (sieve[i]==1) {
            j = i*3; // sieve[i] prime, sieve[2*i] already 0
            while (j<=limit) {
                sieve[j] = 0;
                j += 2*i;
            }
        }
    }
    return sieve;
}


/*
 * Determine if a value is prime using a provided sieve.
 */
_Bool is_prime(uint64_t n, uint8_t * sieve) {
    if ((1 & sieve[n]) == 1) return 1;
    else return 0;
}


/*****************************************************************************/
/* The following functions are specific to Project Euler problem 451         */
/*****************************************************************************/

/*
 * Notes:
 *
 * Given a number n, we're looking for the largest m < n-1 such that m^2 is 1
 * modulo n. That's a mouthful. First, field theory tells us that we're only
 * interested in integers that are relatively prime with n (which is why the
 * problem asks for m < n-1 ... otherwise it would be a lot easier).
 *
 * Now, if n=p^k is a prime power and we have x^2 = 1 mod p^k, we consider:
 * a) 1 is a solution for x since 1*1=1 mod p^k = 1.
 * b) p^k-1 is a solution since (p^k-1)^2=p^(2k)-2p^k+1 (mod p^k) = 1. But,
 *    that's too big since we need m < n=p^k-1. :-(
 * c) Any other solutions? Well... that's sort of complicated. Ugh. Let's first
 *    consider the case when p=2. For n=p^1=2^1, we only have x=1 as a
 *    solution. When n=p^2=2^2, we only have x=1 and x=3. For n=p^k=2^k, we
 *    also find that 2^(k-1)+1 and 2^(k-1)-1 square to 1 modulo 2^k. For other
 *    primes, this doesn't happen and we only have 1 and p^k-1 as solutions.
 *
 * Thus, what we're going to do is as follows:
 * 1) Factor each integer within the given range (factoring a range of numbers
 *    is much faster than factoring each one individually). We'll store that
 *    factorization information using the struct defined above.
 * 2) Because of step 1, determining if a number is prime or a power of a prime
 *    is easy. In case of primes and prime powers, we consider if the prime is
 *    even or odd, returning the appropriate maximum square root of 1 directly.
 * 3) When the integer is composite having more than a single distinct prime
 *    factor, we use the Chinese Remainder Theorem "in spirit" and iterate
 *    over potential candidates (instead of computing the C.R.T. result
 *    directly). We're only considering possible m that are both relatively
 *    prime with n AND such that m^2 is +1 or -1 modulo the prime power
 *    factors of n. When a candidate does not satisfy these properties, we
 *    simply move to the next candidate.
 */

/*
 * Compute the next candidate (the next largest number that may satisfy the
 * given equivalence relations). This is done relative to the largest non-2
 * prime power in the factorization of n.
 *
 * n is the integer for which we're computing the largest square root.
 * m is the largest odd prime power factor of n.
 * c is the current candidate (assume uninitialized when set to 0).
 */
uint64_t next_candidate(uint64_t n, uint64_t m, uint64_t c) {
    uint64_t            r;

    // check if c is initialized
    if (c==0) c = n-1;
    // we can only consider values of \pm1 mod m
    r = c % m;
    if (r==m-1) return c-(m-2);
    else return c-2;
}


/*
 * Determine if the current candidate is (1) relatively prime to n and, if it
 * is, (2) a square root of unity modulo n. We can tweak this later for timing
 * as the test for being relatively prime may cut performance a bit. We'll see.
 *
 * n is the integer for which we're computing the largest square root.
 * cnd is the current candidate.
 * factors is a list of factors_t structs (prime, exponent info)
 */
_Bool verify_candidate(uint64_t n, uint64_t cnd, struct factors_t * factors) {
    uint8_t             i,j; 
    uint64_t            pp;

    // verify that cnd is not divisible by any prime in factors[n].p[]
    for (i=0;i<factors[n].num_factors;i++) {
        if (cnd % factors[n].p[i] == 0) return 0;
    }
    // verify cnd modulo 2 when exponent of 2 in n is > 2
    if (factors[n].p[0] == 2 && factors[n].e[0] > 2) {
        pp = factors[n].pp[0]>>1;
        if (cnd % pp != 1 && cnd % pp != pp-1) return 0;
    }
    // verify other primes
    for (i=0;i<factors[n].num_factors;i++) {
        if (factors[n].p[i] == 2) continue;
        pp = factors[n].pp[i];
        if (cnd % pp != 1 && cnd % pp != pp-1) return 0;
    }
    return 1;
}


/*
 * Given a positive integer n, find the largest positive m < n-1 such that
 * gcd(n,m)=1 and m**2 (mod n) = 1.
 */
uint64_t largest_sqrt(uint64_t n, struct factors_t * factors) {
    uint8_t             i;
    uint32_t            j;

    // if n is an odd prime, or a power of an odd prime, return 1
    if (factors[n].num_factors == 1 && factors[n].p[0] != 2) return 1;

    // if n is a power of 2
    if (factors[n].num_factors == 1) {
        // if n is 2 or 4
        if (factors[n].e[0] < 3) return 1;
        // if n is 2**e for e >= 3
        return (factors[n].pp[0]>>1)+1;
    }

    // find the maximum odd prime power factor of n
    uint64_t            pp = 1;
    uint64_t            cnd;

    for (i=0;i<factors[n].num_factors;i++) {
        if (factors[n].p[i] != 2 && factors[n].pp[i] > pp) {
            pp = factors[n].pp[i];
        }
    }

    // get the first candidate w.r.t. moppf
    cnd = next_candidate(n, pp, 0);

    while (!verify_candidate(n, cnd, factors)) cnd = next_candidate(n, pp, cnd);

    return cnd;
}


/*****************************************************************************/
/* Execute                                                                   */
/*****************************************************************************/
int main() {
    uint64_t            s = 0;              // final output value
    uint64_t            i,j,k;              // iterators
    uint64_t            limit = 20000000;   // upper bound for computations
    uint64_t            num_primes = 0;     // count for primes <= limit
    uint8_t             e;                  // exponents for prime factoring
    int                 tid;                // thread id for openmp
    double              time_count;         // timer
    clock_t             start, start_w;     // time variables

    uint8_t            *sieve;              // prime sieve
    uint64_t           *primes;             // list of primes
    struct factors_t   *factors;            // prime factors and exponents


    /* start outer timer */
    start_w = clock();


    /* make the prime sieve */
    start = clock();
    sieve = prime_sieve(limit);
    time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("prime sieve created - %f seconds\n", time_count);


    /* form list of primes from sieve */
    start = clock();
    // compute the number of primes in sieve
    for (i=2;i<=limit;i++) {
        if (is_prime(i, sieve)) {
            num_primes = num_primes + 1;
        }
    }
    primes = malloc(num_primes * sizeof(uint64_t));
    j=0;
    for (i=2;i<=limit;i++) {
        if (is_prime(i, sieve)) {
            primes[j] = i;
            j++;
        }
    }
    time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("list of %llu primes created - %f seconds\n", num_primes, time_count);


    /* fill out a factors_t struct for each integer below limit */
    start = clock();
    // allocate memory for factors_t
    factors = malloc(sizeof(struct factors_t) * (limit + 1));
    // set the initial number of factors for each number to 0
    for (i=1;i<=limit;i++) factors[i].num_factors=0;
    // for each prime, add that prime as a factor to each of its multiples
    for (i=0;i<num_primes;i++) {
        j = 1; // start at 1*p for each prime p
        while (j*primes[i]<=limit) {
            k = factors[j*primes[i]].num_factors; // get proper index for p
            factors[j*primes[i]].p[k] = primes[i]; // add prime to p
            factors[j*primes[i]].num_factors++; // increase index
            j++; // increase multiple of prime
        }
    }
    time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("list of prime factors created for integers <= %llu - %f seconds\n", limit, time_count);


    /* compute exponents for each prime in factor lists */
    start = clock();
    for (i=2;i<=limit;i++) {
        for (j=0;j<factors[i].num_factors;j++) {
            e=1; k=factors[i].p[j];
            while (i % (k*factors[i].p[j]) == 0) {
                e++;
                k*=factors[i].p[j];
            }
            factors[i].e[j] = e;
            factors[i].pp[j] = k;
        }
    }
    time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("prime factor exponents computed for all integers - %f seconds\n", time_count);


    /* find largest square root of unity for each integer under limit; add to s */
    #pragma omp parallel for reduction(+:s) shared(factors) schedule(dynamic,1000)
    for (i=3;i<=limit;i++) {
        s = s+largest_sqrt(i, factors);
    }
    time_count = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("result for 3<=i<=%llu: %llu - %f seconds\n", limit, s, time_count);


    time_count = (double)(clock() - start_w) / CLOCKS_PER_SEC;
    printf("\ntotal time: %f seconds\n\n", time_count);

    free(sieve);
    free(primes);
    free(factors);

    return 0;
}
