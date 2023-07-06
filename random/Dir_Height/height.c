#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

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

void startCalculation(int maxIteration, int *result) {
    int *combine = (int *)malloc(2*SIZE * sizeof(int));
    allocateValue(combine);

    for (int i = 0; i < maxIteration; i++) {
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

double actual() {
    return (double)(1*3*5*7*9)/(2*4*6*8*10);
}

double errorPercentage(double error) {
    double p = (error / actual()) * 100;
    return p;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int maxIteration;
    
    if (argc == 2) {
        maxIteration = atoi(argv[1]);
    } else {
        printf("Set Iteration Count");
        return 1;
    }

    int result = 0;
    FILE *p = fopen("height.csv", "w");
    
    const int repetitionCount = 3;
    const int increment = (int)log10(maxIteration);
    double *r = (double *)malloc(increment * repetitionCount * sizeof(double));
    double *error = (double *)malloc(repetitionCount * sizeof(double));

    double *q = r;
    for (int i = 0; i < repetitionCount; i++) {
        for (int count = 10; count <= maxIteration; count *= 10) {
            startCalculation(count, &result);
            *q = (double)result/(double)count;
            result = 0;
            q++;
        }
    }

    printf("count, actual, ");
    printf("probability_1, error_1, error_1, ");
    printf("probability_2, error_2, error_2, ");
    printf("probability_3, error_3, error_3,\n");

    fprintf(p, "count, actual, ");
    fprintf(p, "probability_1, error_1, error_1, ");
    fprintf(p, "probability_2, error_2, error_2, ");
    fprintf(p, "probability_3, error_3, error_3,\n");
    for (int i = 0; i < increment; i++) {
        printf("%d, %.10lf, ", (int)pow(10, i+1), actual()*100);
        fprintf(p, "%d, %.10lf, ", (int)pow(10, i+1), actual()*100);
        for (int j = 0; j < repetitionCount; j++) {
            error[j] = r[i + j*increment] - actual();
            printf("%.10lf, %.3lf, %.3lf%%, ", (r[i + j*increment])*100, fabs(errorPercentage(error[j])), fabs(errorPercentage(error[j])));
            fprintf(p, "%.10lf, %.3lf, %.3lf%%, ", (r[i + j*increment])*100, fabs(errorPercentage(error[j])), fabs(errorPercentage(error[j])));
        }
        printf("\n");
        fprintf(p, "\n");
    }

    free(r);
    free(error);
    fclose(p);
}