#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define diceCount 7

#define DEBUG 0

void setValue(int *dst, int value) {
    *dst = value;
}

int checkResult(int diceSide, int *diceResult, int *result) {
    for (int i = 1; i < diceCount; i++) {
        if(diceResult[0] == diceResult[i]) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

void startSimulation(int maxIteration, int count, int diceSide, int *result) {
    for (int i = 0; i < maxIteration; i++) {
        int *diceResult = malloc(diceCount * sizeof(int));
        // printf("%d | ", i+1);
        for (int j = 0; j < count; j++) {
            diceResult[j] = rand() % diceSide + 1;  
            // printf("%d ", diceResult[j]);
        }
        *result += checkResult(diceSide, diceResult, result);

        #if DEBUG == 1
        if(checkResult(diceSide, diceResult, result)) {
            for (int j = 0; j < diceSide; j++) {
            printf("%d ", diceResult[j]);
            }
            printf("\n");
        }
        #endif
        // printf("| %d \n", *result);
        free(diceResult);
    }
}

double actual(int diceSide) {
    return 1/pow((double)diceSide, (double)diceCount-1);
}

double errorPercentage(double error, int diceSide) {
    double p = (error / actual(diceSide)) * 100;
    return p;
}   

int main(int argc, char **argv) {
    srand(time(NULL));
    
    int diceSide;
    int maxIteration;
    int result = 0;
    const int repetitionCount = 3;

    if(argc != 2) {
        setValue(&diceSide, atoi(argv[1]));
        setValue(&maxIteration, atoi(argv[2]));
    } else {
        printf("Set dice sided and maxIteration number\n");
        return -2;
    }

    char filename[20];
    sprintf(filename, "dice%d.csv", diceSide);
    printf("%s\n", filename);
    
    FILE *p = fopen(filename, "w");
    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    const int iteration = (int)log10(maxIteration);
    double *r = (double *)malloc(iteration * repetitionCount * sizeof(double));
    double *error = (double *)malloc(repetitionCount * sizeof(double));

    double *q  = r;
    for (int i = 0; i < repetitionCount; i++) {
        for (int count = 10; count <= maxIteration; count *= 10) {
            startSimulation(count, diceCount, diceSide, &result);
            *q = (double)result/count;
            result = 0;
            q++;
        }
    }

    printf("count, actual, probability1, errorPercentage1, errorPercentage1,");
    printf(" probability2, errorPercentage2, errorPercentage2,");
    printf(" probability3, errorPercentage3, errorPercentage3,\n");

    fprintf(p, "count, actual, probability1, errorPercentage1, errorPercentage1,");
    fprintf(p, " probability2, errorPercentage2, errorPercentage2,");
    fprintf(p, " probability3, errorPercentage3, errorPercentage3,\n");

    for (int i = 0; i < iteration; i++) {
        printf("%d, %.10lf, ", (int)pow(10, i + 1), actual(diceSide)*100);
        fprintf(p, "%d, %.10lf, ", (int)pow(10, i + 1), actual(diceSide)*100);
        for (int j = 0; j < repetitionCount; j++) {
            error[j] = r[i + j*iteration] - actual(diceSide);
            printf("%.10lf, %.3lf, %.3lf%%, ", (r[i + j*iteration])*100, fabs(errorPercentage(error[j], diceSide)), fabs(errorPercentage(error[j], diceSide)));
            fprintf(p, "%.10lf, %.3lf, %.3lf%%, ", (r[i + j*iteration])*100, fabs(errorPercentage(error[j], diceSide)), fabs(errorPercentage(error[j], diceSide)));
        }
        printf("\n");
        fprintf(p, "\n");
    }

    free(r);
    free(error);
    fclose(p);
}