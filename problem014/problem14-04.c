#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
int find_max_collatz(unsigned long max) {
    unsigned int collatz_length[max];
    unsigned int TO_ADD[600];
    unsigned long iter, j, m, n, s, p, ind, new_length, max_length = 0;
 
    // set initial collatz lengths and TO_ADD numbers
    iter = 0;
    while(iter < max) {
        collatz_length[iter] = 0;
        iter++;
    }
    collatz_length[1] = 1;
    iter = 0;
    while(iter < 600) {
        TO_ADD[iter] = 0;
        iter++;
    }
    // iterate to max and find collatz lengths
    iter = 1;
    while(iter < max) {
        n = iter;
        s = 0;
        while(n > max - 1 || collatz_length[n] < 1) {
            TO_ADD[s] = n;
            if(n % 2 == 0) n = n/2;
            else n = 3*n + 1;
            s++;
        }
        // collatz length now known from previous calculations
        p = collatz_length[n];
        j = 0;
        while(j < s) {
            m = TO_ADD[j];
            TO_ADD[j] = 0;
            if(m < max) {
                new_length = collatz_length[n] + s - j;
                collatz_length[m] = new_length;
                if(new_length > max_length) {
                    max_length = new_length;
                    ind = m;
                }
            }
            j++;
        }
        iter++;
    } 
    return ind;
}
 
 
int main(int argc, char **argv) {
    unsigned int max, i;
    time_t start, end;
    double total_time;
 
    start = time(NULL);
 
    for(i=0;i<1000;i++) max = find_max_collatz(1000000);
 
    end = time(NULL);
    total_time = difftime(end,start);
 
    printf("%d found in %lf seconds.\n",max,total_time);
 
    return 0;
}
