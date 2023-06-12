#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define diceCount 7

void setValue(int *dst, int value) {
    *dst = value;
}

void checkResult(int diceSide, int *diceResult, int *result) {
    for (int i = 1; i < diceSide; i++) {
        if(diceResult[0] == diceResult[i]) {
            printf("kenanih \n");
            *result += 1;
        } else {
            break;
        }
    }
}

// void checkResult()

void startSimulation(int iteration, int count, int diceSide, int *result) {

    for (int i = 0; i < iteration; i++) {
        int *diceResult = malloc(diceCount * sizeof(int));
        printf("%d | ", i+1);
        for (int j = 0; j < count; j++) {
            diceResult[i] = rand() % diceSide + 1;  
            printf("%d ", diceResult[i]);
        }
        checkResult(diceSide, diceResult, result);
        printf("| %d \n", *result);
        // printf("\n");
        free(diceResult);
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    int diceSide;
    int iteration;

    int result = 0;

    if(argc > 1) {
        setValue(&diceSide, atoi(argv[1]));
        setValue(&iteration, atoi(argv[2]));
    } else {
        printf("Set dice sided and iteration number");
    }

    // int dummy[] = {1, 1, 1, 1, 1, 1};
    // checkResult(diceSide, dummy, &result);
    // printf("%d", result);

    startSimulation(iteration, diceCount, diceSide, &result);
}