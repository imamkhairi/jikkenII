#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5

#define DEBUG 0

void allocateValue(int *dst) {
    for (int i = 1; i <= 2*SIZE; i++) {
        *dst = i;
        dst++;
    }
}

void printData(int *dst) {
    for (int i = 0; i < 2 * SIZE; i++) {
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
    for (int i = 2*SIZE - 1; i >= 0; i--) {
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
    int max;
    if (dst[0] == 10) return 1;
    if (dst[0] % 2 == 1) return 0;
    else {
        max = dst[0];
        for (int i = 1; i < 2*SIZE; i++) {
            if (dst[i] % 2 == 1) {
                if (max > dst[i]) continue;
                else return 0;
            } else {
                if (dst[i] > max) max = dst[i];
            }
        }
    }
    return 1;
}

void startCalculation(int iteration, int *result) {
    int *combine = (int *)malloc(2*SIZE * sizeof(int));
    allocateValue(combine);

    for (int i = 0; i < iteration; i++) {
        shuffle(combine);
        
        *result += check(combine);
        #if DEBUG == 1
            // if(!check(combine)) {
            if(!check(combine)) {
                for(int j = 0; j < 10; j++) {
                    printf("%d ", combine[j]);
                }
                printf("\n\n");
            }
        #endif
    }

    free(combine);
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int iteration;

    iteration = atoi(argv[1]);
    int result = 0;

    FILE *p = fopen("height.csv", "a");

    printf("count, probability\n");
    for (int i = 0; i < 30; i++) {
        for (int count = 10; count <= iteration; count *= 10) {
            startCalculation(count, &result);
            // printf("%d, %lf\n", count, (double)result/(double)count);
            fprintf(p, "%d, %lf\n", count, (double)result/(double)count);
            result = 0;
        }
    }

    fclose(p);
    // printf("result = %d\n", result);
}