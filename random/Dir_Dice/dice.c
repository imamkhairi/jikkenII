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
    
    FILE *p = fopen(filename, "a");
    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    int pointCount = 25;
    double *r = (double *)malloc((pointCount+1) * repetitionCount * sizeof(double));
    int increment = maxIteration/pointCount;

    printf("count, actual, probability1, errorPercentage1,");
    printf(" probability2, errorPercentage2,");
    printf(" probability3, errorPercentage3\n");
    double *q  = r;
    for (int i = 0; i < repetitionCount; i++) {
        for (int count = 1; count <= maxIteration + 1; count += increment) {
            startSimulation(count, diceCount, diceSide, &result);
            // printf("%.0le, %.10lf\n", count, (double)result/count);
            // printf("%d, %.10lf\n", count, (double)result/count);
            *q = *q + (double)result/count;
            // fprintf(p, "%d,  %.10lf\n", count, (double)result/count);
            result = 0;
            q++;
        }
    }

    for(int i = 0; i <= maxIteration/increment; i++) {
        double error1 = r[i]-actual(diceSide);
        double error2 = r[i + pointCount + 1]-actual(diceSide);
        double error3 = r[i + 2*pointCount + 2]-actual(diceSide);
        printf("%d, %.10lf, %.10lf, %.3lf%%, %.10lf, %.3lf%%, %.10lf, %.3lf%%\n",
            (i*increment)+1,
            actual(diceSide)*100,
            (r[i])*100, 
            errorPercentage(error1, diceSide),
            (r[i + pointCount + 1])*100, 
            errorPercentage(error2, diceSide),
            (r[i + 2*pointCount + 2])*100, 
            errorPercentage(error3, diceSide)
            );
    }

    free(r);
    fclose(p);
}