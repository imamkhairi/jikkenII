#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5

void allocateValue(int *dst) {
    for (int i = 0; i < SIZE; i++) {
        *dst = i;
        dst++;
    }
}

void printData(int *dst) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", *dst);
        dst++;
    }
    printf("\n");
}

void swapElement(int *dst, int a, int b) {
    int tmp = dst[a];
    dst[a] = dst[b];
    dst[b] = tmp;
}

void shuffle(int *dst) {
    for (int i = SIZE - 1; i >= 0; i--) {
        int target = rand() % SIZE;
        swapElement(dst, i, target);
    }
}

void combineValue(int *dst, int *m, int *w) {
    for (int i = 0; i < SIZE; i++) {
        *dst = *m;
        dst++;
        *dst = *w;
        dst++;
        
        m++;
        w++;
    }
}

int check(int *dst) {
    for (int i = 1; i < 2*SIZE; i += 2) {
        if(dst[i-1] >= dst[i]) continue;
        else return 0;
    }
    return 1;
}

void startCalculation(int iteration, int *result) {
    int *m = (int *)malloc(SIZE * sizeof(int));
    int *w = (int *)malloc(SIZE * sizeof(int));
    int *combine = (int *)malloc(2*SIZE * sizeof(int));
    allocateValue(m);
    allocateValue(w);


    for (int i = 0; i < iteration; i++) {
        shuffle(m);
        shuffle(w);
        combineValue(combine, m, w);

        // for(int j = 0; j < 10; j++) {
        //     printf("%d ", combine[j]);
        // }
        *result += check(combine);
            // printf("\nresult =  %d\n", *result);
        // if(check(combine)) {
        // }
    }

    free(m);
    free(w);
    free(combine);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int iteration;

    iteration = atoi(argv[1]);
    int result = 0;

    startCalculation(iteration, &result);
    printf("result = %d\n", result);
    
}