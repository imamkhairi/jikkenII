#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5
#define INTERVAL 15
// #define MAXVALUE 500
#define MAXVALUE 75

void printBoard(int *board) {
    for (int i = 1; i <= SIZE * SIZE; i++) {
        printf("%2d ", *board);
        board++;
        if(i % 5 == 0) printf("\n");
    }
}

void initiateDummy(int *dummy, int scale) {
    for (int i = 0; i < INTERVAL; i++) {
        dummy[i] = i + INTERVAL*scale + 1;
    }
}

void swapElement(int *dst, int a, int b) {
    int tmp = dst[a];
    dst[a] = dst[b];
    dst[b] = tmp;
}

void shuffle(int *dummy, int size) {
    for (int i = size - 1; i >= 0; i--) {
        int target = rand() % size;
        swapElement(dummy, i, target);
    }
}

void makeBoard(int *board) {
    int *dummy = (int *)malloc(INTERVAL * sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        initiateDummy(dummy, i);
        shuffle(dummy, INTERVAL);

        int *p = dummy;
        int *q = board;

        for (int j = 0; j < SIZE; j++) {
            *board = *p;
            p++;
            board += SIZE;
        }

        board = ++q;
    }
    free(dummy);

    board += SIZE + 2;
    *board = 0;
}

void printCheck(int *boardCheck) {
    int *p = boardCheck;

    printf("==============\n");

    for (int i = 1; i <= SIZE * SIZE; i++) {
        printf("%2d ", *p);
        p++;
        if(i % 5 == 0) printf("\n");
    }

    printf("==============\n");
}

int checkRow(int *boardCheck) {
    int *p = boardCheck;
    int *q = boardCheck;
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(*p == 1) {
                p++;
                count ++;
                continue;
            } else break;
        }
        if (count == 5) return 1;
        count = 0;
        q += SIZE;
        p = q;
    }
    return 0;
}

int checkCol(int *boardCheck) {
    int *p = boardCheck;
    int *q = boardCheck;
    int count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(*p == 1) {
                p += SIZE;
                count ++;
                continue;
            } else break;
        }
        if (count == 5) return 1;
        count = 0;
        q ++;
        p = q;
    }
    return 0;
}

int checkDia(int *boardCheck) {
    int *p = boardCheck;
    int *q = boardCheck + 4;

    int count = 0;
    int inc = 1;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (*p == 1) count ++;
            else break;
            p += SIZE + inc;
        }
        if (count == 5) return 1;
        count = 0;
        p = q;
        inc = -1;
    }

    return 0;
}

void updateCheck(int *boardCheck, int offset) {
    if (offset < SIZE*SIZE){
        int *p = boardCheck;
        p += offset;
        *p = 1;
    }
}

int searchBoard(int *boardValue, int target) {
    int *p = boardValue;
    int *q = boardValue;
    int row = (target - 1) / 15;

    p += row;
    for (int i = 0; i < SIZE; i++) {
        if(*p == target) break;
        p += SIZE;
    }

    int dif = p - q;

    return dif;
}

void initiateBoardCheck(int *boardCheck) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        boardCheck[i] = 0;
    }
    boardCheck[2*SIZE + 2] = 1;
}

void initiateCheckValue(int *checkValue) {
    for (int i = 0; i < MAXVALUE; i++) {
        checkValue[i] = i+1;
    }
}

void printValue(int *checkValue) {
    for (int i = 0; i < MAXVALUE; i++) {
        printf("%d \n", checkValue[i]);
    }
}

int startBingo() {
    int *boardValue = (int *)malloc(SIZE*SIZE * sizeof(int));
    makeBoard(boardValue);

    int *boardCheck = (int *)malloc(SIZE*SIZE * sizeof(int));
    initiateBoardCheck(boardCheck);


    int *checkValue = (int *)malloc(MAXVALUE * sizeof(int));
    initiateCheckValue(checkValue);
    shuffle(checkValue, MAXVALUE);

    int count = 0;

    while (!checkCol(boardCheck) && !checkRow(boardCheck) && !checkDia(boardCheck)) {
        count ++ ;
        int dif = searchBoard(boardValue, checkValue[count]);
        updateCheck(boardCheck, dif);
    }

    free(boardValue);
    free(boardCheck);
    free(checkValue);

    return count;
}

void printResult(int *result) {
    for (int i = 0;  i < 500; i++) {
        if(result[i] != 0) printf("%d, %d\n", i, result[i]);
        else continue;
    }
}

void probUnderX(int iteration, int *result, int x)
{
    int total = 0;
    for (int i = 1; i <= x; i++) {
        total += result[i];
    }

    printf("Probability under %d = %lf\n", x, (double)(total)/(double)(iteration));
}

void probWhenX(int iteration, int *result, int x)
{
    printf("Probability when %d = %lf\n", x, (double)(result[x])/(double)(iteration));
}

int getMax(int *result) {
    int max = 0;
    int index = 0;
    for (int i = 0; i < MAXVALUE; i++) {
        if (result[i] != 0) index = i;
        else continue;
    }
    return index;
}

void resetResult(int *result) {
    for (int i = 0; i < MAXVALUE; i++) {
        result[i] = 0;
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int iteration;
    if (argc == 2) {
        iteration = atoi(argv[1]);
    } else {
        printf("Iteration value set to 5000\n");
        iteration = 5000;
    }


    const int repetitionCount = 3;
    int *result = (int *)malloc(MAXVALUE * repetitionCount * sizeof(int));
    int *flag = (int *)malloc(repetitionCount * sizeof(int));


    FILE *p = fopen("bingo.csv", "w");
    for (int i = 0; i < repetitionCount; i++) {
        for (int j = 0; j < iteration; j++) {
            int r = startBingo();
            result[r + i*MAXVALUE]++;
            if (flag[i] == 0 && r == 4) {
                flag[i] = j;
            }
        }
    }

    printf("Winning Round, Win Count, Win Count,\n");
    fprintf(p, "Winning Round, Win Count, Win Count,\n");
    for (int i = 0; i < MAXVALUE; i++) {
        printf("%d, ",i);
        fprintf(p, "%d, ",i);
        for (int j = 0; j < repetitionCount; j++) {
            printf("%d, %d, ", flag[j], result[i + j*MAXVALUE]);
            fprintf(p, "%d, %d, ", flag[j], result[i + j*MAXVALUE]);
        }
        printf("\n");
        fprintf(p, "\n");
    }

    free(flag);
    free(result);
    fclose(p);

    return 0;
}