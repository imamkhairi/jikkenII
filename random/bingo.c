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
    for (int i = 0; i < SIZE; i++) {
        int *dummy = (int *)(malloc(INTERVAL * sizeof(int)));
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
        free(dummy);
    }
    // set FREE in middle
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

// int checkCol(int *boardCheck) {
//     int *p = boardCheck;

//     printf("==========+++++++\n");
//     int count = 0;
//     for (int i = 0; i < SIZE; i++) {
//         for(int j = 0; j < SIZE; j++) {
//             if (*p == 1){ 
//                 p += SIZE;
//                 count++;
//             }
//             else break;
//         }
//         if (count == 5) return 1;
//         p -= SIZE * SIZE - 1;
//     }

//     return 0;
// }

int checkRow(int *boardCheck) {
    int *p = boardCheck;
    int *q = boardCheck;
    int count = 0;
    printf("==========+++++++\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if(*p == 1) {
                p++;
                // printf("kena \n");
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

int main(int argc, char **argv) {
    srand(time(NULL));

    int *boardValue = (int *)malloc(SIZE*SIZE * sizeof(int));
    int *boardCheck = (int *)calloc(SIZE*SIZE, sizeof(int));

    boardCheck[5] = 1;
    boardCheck[6] = 1;
    boardCheck[7] = 1;
    boardCheck[8] = 1;
    boardCheck[9] = 1;
    // boardCheck[23] = 1;
    boardCheck[2*SIZE + 2] = 1;

    printCheck(boardCheck);


    makeBoard(boardValue);
    printBoard(boardValue);


    printf("result = %d\n", checkRow(boardCheck));


    free(boardValue);
    free(boardCheck);

    return 0;
}










/* NOTE */
/* 
void printArr(int *p) {
    for(int i = 0; i < 12; i++) {
        printf("%d ", *p);
        p++;
    }
}

int main() {
    int arr[4][3]={{1,2,3},{2,3,4},{3,4,5},{4,5,6}};
    
    printArr((int *)arr);
    return 0;
}
 */