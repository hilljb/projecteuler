
#include <stdlib.h>
#include <stdio.h>

unsigned long long recPath(int x, int y) {
    unsigned long long  paths;
    if (x==0 && y==0) return 1;
    paths = 0;
    if (x>0) paths += recPath(x-1,y);
    if (y>0) paths += recPath(x,y-1);
    return paths;
}

int main() {
    unsigned long long  res;

    res = recPath(20,20);

    printf("There are %llu paths\n", res);

    return 0;
}

