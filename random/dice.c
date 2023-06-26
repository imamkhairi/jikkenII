#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

void startSimulation(int iteration, int count, int diceSide, int *result) {
    for (int i = 0; i < iteration; i++) {
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

int main(int argc, char **argv) {
    srand(time(NULL));
    
    int diceSide;
    int iteration;

    int result = 0;

    FILE *p = fopen("dice.csv", "a");

    if(p == NULL) {
        perror("File open error\n");
        return -1;
    }

    if(argc != 2) {
        setValue(&diceSide, atoi(argv[1]));
        setValue(&iteration, atoi(argv[2]));
    } else {
        printf("Set dice sided and iteration number\n");
        return -2;
    }


    // startSimulation(iteration, diceCount, diceSide, &result);
    // printf("count, result, probability\n");
    // printf("%d, %d, %.3le\n", iteration, result, (double)result/iteration);

    printf("count, probability\n");
    for (int i = 0; i < 1; i++) {
        for (int count = 1; count <= iteration; count ++) {
            startSimulation(count, diceCount, diceSide, &result);
            printf("%d, %.6lf\n", count, (double)result/count);
            // fprintf(p, "%d,  %.3le\n", count, (double)result/count);
            result = 0;
        }
    }

    fclose(p);
}