#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5
#define INTERVAL 15

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

void shuffle(int *dummy) {
    for (int i = INTERVAL - 1; i >= 0; i--) {
        int target = rand() % INTERVAL;
        swapElement(dummy, i, target);
    }
}

void makeBoard(int *board) {
    int *dummy = (int *)malloc(INTERVAL * sizeof(int));

    for (int i = 0; i < SIZE; i++) {
        initiateDummy(dummy, i);
        shuffle(dummy);

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
    int row = target / 15;

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

int startBingo() {
    int *boardValue = malloc(SIZE*SIZE * sizeof(int));
    makeBoard(boardValue);

    int *boardCheck = (int *)malloc(SIZE*SIZE * sizeof(int));
    initiateBoardCheck(boardCheck);

    int count = 0;

    while (!checkCol(boardCheck) && !checkRow(boardCheck) && !checkDia(boardCheck)) {
        count ++ ;
        int target = rand() % 75 + 1;

        int dif = searchBoard(boardValue, target);

        updateCheck(boardCheck, dif);
    }

    free(boardValue);
    free(boardCheck);

    return count;
}

void printResult(int *result) {
    for (int i = 0;  i < 500; i++) {
        if(result[i] != 0) printf("%d, %d\n", i, result[i]);
        else continue;
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int *result = malloc(500 * sizeof(int));

    for (int i = 0; i < 5000; i++) {
        result[startBingo()]++;
    }

    printResult(result);
    free(result);

    return 0;
}