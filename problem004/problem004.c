#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int is_palindrome(unsigned int num) {
    unsigned int reversed = 0;
    unsigned int original = num;
 
    if (num < 10) return 1;
    if (num % 10 == 0) return 0;
 
    while (num >= 1) {
        reversed = (reversed * 10) + (num % 10);
        num = num/10;
    }
 
    if (original == reversed) return 1;
    else return 0;
}
 
int main(int argc, char **argv) {
    float ratio = 1./CLOCKS_PER_SEC;
    clock_t t1 = clock();
    unsigned int max_palindrome = 0;
    unsigned int a, b, prod;
 
    unsigned long int c = 10000;
 
    while (c > 0) {
    a = 999;
    while (a > 99) {
        b = 999;
        while (b >= a) {
            prod = a*b;
            if (prod > max_palindrome && is_palindrome(prod)) {
                max_palindrome = prod;
            }
            b--;
        }
        a--;
    }
    c--;
    }
 
    clock_t t2 = clock();
    printf("%d found in %f seconds for 10,000 iterations\n", max_palindrome, \
        ratio*(long)t1+ratio*(long)t2);
 
    return 0;
}
