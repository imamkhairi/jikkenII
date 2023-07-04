#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

void resetCoin(int *A, int *B) {
    *A = 5;
    *B = 3;
}

double printAWinPercentage(int winA, int count) {
    return (double)(winA)/(double)(count);
}

void startCalculation(int *A, int *B, int *winA, int *winB, int iteration) {
    for (int i = 0; i < iteration; i++) {
        resetCoin(A, B);
        startSimulation(A, B);
        updateWinCount(*A, winA);
        updateWinCount(*B, winB);
    }
}

void resetValue(int *coinA, int *coinB, int *winA, int *winB) {
    *coinA = 5;
    *coinB = 3;
    *winA = 0;
    *winB = 0;
}


int main(int argc, char **argv) {
    srand(time(NULL));

    int iteration;
    if (argc == 2) iteration = atoi(argv[1]);
    else {
        printf("Set iteration count\n");
        return 1;
    }

    int coinA = 5;
    int coinB = 3;

    int winA = 0;
    int winB = 0;

    FILE *p = fopen("coin53.csv", "a");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    printf("Count, Probability\n");
    for (int i = 0; i < 20; i++) {
        for (int count = 1; count <= iteration; count *= 10) {
            startCalculation(&coinA, &coinB, &winA, &winB, count);
            fprintf(p, "%d, %.10lf\n", count, printAWinPercentage(winA, count));
            // printf("%d, %.10lf\n", count, printAWinPercentage(winA, count));
            resetValue(&coinA, &coinB, &winA, &winB);
        }
    }

    fclose(p);

    return 0;
}