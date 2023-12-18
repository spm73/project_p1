#include <stdio.h>
#include <time.h>

int main() {
    clock_t begin = clock();
    for (int i = 0; i < 2000000; i++) {
        printf(" ");
    }
    clock_t end = clock();
    double time = (double) (end-begin) / CLOCKS_PER_SEC;
    printf("\n%f seconds", time);
}