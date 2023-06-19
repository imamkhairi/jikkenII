#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5

void allocateValue(int *dst) {
    for (int i = 0; i < SIZE; i++) {
        dst[i] = i;
    }
}

void printData(int *dst) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d | value = %d\n", i, dst[i]);
    }
}

void swapElement(int )

void shuffle(int *dst) {
    for (int i = SIZE - 1; i >= 0; i--) {

    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int *m = (int *)malloc(SIZE * sizeof(int));
    int *w = (int *)malloc(SIZE * sizeof(int));
    allocateValue(m);
    allocateValue(w);
    printData(m);
    printData(w);
}