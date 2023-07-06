#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define DEBUG 0

int rollDice() {
    return rand() % 6 + 1;
}

int check(int dice) {
    if (dice == 1 || dice == 2) return 1;
    else return 0;
}

void giveCoin(int *dst, int *src) {
    *dst = *dst + 1;
    *src = *src - 1;
}

void startSimulation(int *A, int *B) {
    // for (int i = 0; i < 20; i++) {
    while(*A != 0 && *B != 0) {  
        int dice = rollDice();
        if (check(dice)) giveCoin(A, B);
        else giveCoin(B, A);
        
        #if DEBUG == 1
            printf("A = %d, B = %d\n", *A, *B);
        #endif
    }
}

void updateWinCount(int coin, int *winCount) {
    if(coin) *winCount = *winCount + 1;
    else return;
}

void resetCoin(int *A, int *B, int startA, int startB) {
    *A = startA;
    *B = startB;
}

double printAWinPercentage(int winA, int count) {
    return (double)(winA)/(double)(count);
}

void startCalculation(int *A, int *B, int *winA, int *winB, int maxIteration, int startA, int startB) {
    for (int i = 0; i < maxIteration; i++) {
        resetCoin(A, B, startA, startB);
        startSimulation(A, B);
        updateWinCount(*A, winA);
        updateWinCount(*B, winB);
    }
}

void resetValue(int *coinA, int *coinB, int *winA, int *winB, int startA, int startB) {
    *coinA = startA;
    *coinB = startB;
    *winA = 0;
    *winB = 0;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int maxIteration;
    int startA;
    if (argc == 3) {
        maxIteration = atoi(argv[1]);
        startA = atoi(argv[2]);
    } else {
        printf("Set maxIteration count\n");
        return 1;
    }

    int startB = 8 - startA;

    int coinA;
    int coinB;
    int winA;
    int winB;
    resetValue(&coinA, &coinB, &winA, &winB, startA, startB);

    char filename[20];
    sprintf(filename, "coin%d.csv", startA);
    printf("%s\n", filename);

    FILE *p = fopen(filename, "w");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    const int repetitionCount = 3;
    const int iteration = (int)log10(maxIteration);
    double *r = (double *)malloc(iteration * repetitionCount * sizeof(double));

    double *q = r;
    for (int i = 0; i < repetitionCount; i++) {
        for (int count = 10; count <= maxIteration; count *= 10) {
            startCalculation(&coinA, &coinB, &winA, &winB, count, startA, startB);
            // fprintf(p, "%d, %.10lf\n", count, printAWinPercentage(winA, count));
            // printf("%d, %.10lf\n", count, printAWinPercentage(winA, count));
            *q = printAWinPercentage(winA, count);
            q++;
            resetValue(&coinA, &coinB, &winA, &winB, startA, startB);
        }
    }

    printf("Count, Probability_1, Probability_2, Probability_3,\n");
    fprintf(p, "Count, Probability_1, Probability_2, Probability_3,\n");

    for (int i = 0; i < iteration; i++) {
        printf("%d, ", (int)pow(10, i+1));
        fprintf(p, "%d, ", (int)pow(10, i+1));
        for (int j = 0; j < repetitionCount; j++) {
            printf("%.10lf, ", r[i + j*iteration]*100);
            fprintf(p, "%.10lf, ", r[i + j*iteration]*100);
        }
        printf("\n");
        fprintf(p, "\n");
    }


    free(r);
    fclose(p);

    return 0;
}