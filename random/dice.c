#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define diceCount 7

void setValue(int *dst, int value) {
    *dst = value;
}

int checkResult(int diceSide, int *diceResult, int *result) {
    for (int i = 1; i < diceSide; i++) {
        if(diceResult[0] == diceResult[i]) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}

void startSimulation(int iteration, int count, int diceSide, int *result) {
    for (int i = 0; i < iteration; i++) {
        int *diceResult = malloc(diceCount * sizeof(int));
        printf("%d | ", i+1);
        for (int j = 0; j < count; j++) {
            diceResult[j] = rand() % diceSide + 1;  
            printf("%d ", diceResult[j]);
        }
        *result += checkResult(diceSide, diceResult, result);
        printf("| %d \n", *result);
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
        printf("Set dice sided and iteration number\n");
    }

    startSimulation(iteration, diceCount, diceSide, &result);

    printf("%f\n", (double)result/iteration);
}