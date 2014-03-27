#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// compile with: gcc -lm -O3 -o problem019-02 problem019-02.c
 
// use the Gaussian algorithm to find the day of week of a given day
int day_of_week(int year, int month, int day) {
    int d = day;
 
    double m = (double) ((month - 3) % 12 + 1);
    int Y;
    if(m > 10) Y = year - 1;
    else Y = year;
    int y = Y % 100;
    int c = (Y - (Y % 100)) / 100;
 
    int w = ((d+(int)floor(2.6*m-0.2)+y+ y/4 + c/4 -2*c))%7;
 
    return w; 
}

// compute how many months start on a given day within a range of years
long months_start_range(int day, int year_start, int year_end) {
    unsigned long total = 0;
    int year, month;
    for(year = year_start; year < year_end; year++) {
        for(month = 1; month <= 12; month++) {
            if(day_of_week(year, month, 1)==day) total++;
        }
    }
    return total;
 
}
 
int main(int argc, char **argv) {
 
    long total;
    total = months_start_range(0,1901,2000);
    printf("Solution: %ld\n",total);
 
    return 0;
}
