#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5

#define DEBUG 1

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
    for (int i = 1; i < 2*SIZE; i += 2) { // women
        int count = 0;
        for (int j = 0; j < i+1; j += 2) { // men
            printf("w: %d  | m: %d\n", i, j);
            if(dst[j] >= dst[i]) {
                count++;
                printf("kena | w: %d  | m: %d\n", i, j);
            }else continue;
        }
        printf("=======\n");
        // printf("%d\n", count);
        if (count < 1) return 0;
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

        *result += check(combine);
            // printf("\nresult =  %d\n", *result);
        #if DEBUG == 1
            // if(!check(combine)) {
            if(1) {
                for(int j = 0; j < 10; j++) {
                    printf("%d ", combine[j]);
                }
                printf("\n\n");
            }
        #endif
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

    // int dummy[] = {1, 4, 2, 3, 0, 1, 4, 0, 3, 2};
    // int dummy[] = {2, 2, 5, 5, 3, 3, 4, 4, 1, 1};
    // int dummy[] = {4, 4, 3, 3, 2, 2, 5, 5, 1, 5};
    // printf("hsail %d\n", check(dummy));
}