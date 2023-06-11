#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void compAndSwap(int *a, int i, int j, int dir) {
    if(dir == (a[i] > a[j])) swap(&a[i], &a[j]);
}

void bitonicMerge(int *a, int low, int cnt, int dir) {
    if(cnt > 1) {
        int k = cnt/2;
        for (int i = low; i < low + k; i++) {
            compAndSwap(a, i, i+k, dir);
        }
    }
}

void printArray(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d \n", a[i]);
    }
}

int main(void) {
    int a[] = {7, 2, 5, 6, 1, 2, 3, 4};
    int N = sizeof(a)/sizeof(a[0]);

    compAndSwap(a, 0, 1, 0);
    
    printArray(a, N);
    return 0;
}