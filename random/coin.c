#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
        printf("A = %d, B = %d\n", *A, *B);
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

void printAWinPercentage(int winA, int iteration) {
    printf("opportunity= %lf\n", (double)(winA)/(double)(iteration));
}

void startCalculation(int *A, int *B, int *winA, int *winB, int iteration) {
    for (int i = 0; i < iteration; i++) {
        resetCoin(A, B);
        startSimulation(A, B);
        updateWinCount(*A, winA);
        updateWinCount(*B, winB);
        printf("=====\n");
    }
    printf("winA = %d, winB = %d\n", *winA, *winB);
    printAWinPercentage(*winA, iteration);
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

    startCalculation(&coinA, &coinB, &winA, &winB, iteration);

    return 0;
}