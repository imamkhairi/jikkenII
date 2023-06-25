#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DEBUG 0

int rollDice() {
    return rand() % 6;
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
    *A = 6;
    *B = 2;
}

double printAWinPercentage(int winA, int iteration) {
    return (double)(winA)/(double)(iteration);
}

void startCalculation(int *A, int *B, int *winA, int *winB, int iteration) {
    for (int i = 0; i < iteration; i++) {
        resetCoin(A, B);
        startSimulation(A, B);
        updateWinCount(*A, winA);
        updateWinCount(*B, winB);
        // printf("=====\n");
    }
    // printf("winA = %d, winB = %d\n", *winA, *winB);
    // printAWinPercentage(*winA, iteration);
}

void resetValue(int *coinA, int *coinB, int *winA, int *winB) {
    *coinA = 6;
    *coinB = 2;
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

    int coinA = 6;
    int coinB = 2;

    int winA = 0;
    int winB = 0;

    FILE *p = fopen("coin.csv", "a");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    printf("Count, Probability\n");
    for (int i = 0; i < 10; i++) {
        for (int count = 1; count <= iteration; count *= 10) {
            startCalculation(&coinA, &coinB, &winA, &winB, count);
            fprintf(p, "%d, %.10lf\n", count, printAWinPercentage(winA, iteration));
            // printf("%d, %.10lf\n", count, printAWinPercentage(winA, iteration));
            resetValue(&coinA, &coinB, &winA, &winB);
        }
    }

    fclose(p);

    return 0;
}