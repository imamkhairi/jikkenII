#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SIZE 5

void printBoard(int *board) {
    for (int i = 0; i < SIZE; i++) {
        printf("%2d ", *board);
        board += SIZE; // ini buat akses per colom
    }
    // for (int i = 1; i <= SIZE * SIZE; i++) {
    //     printf("%2d ", *board);
    //     board++;
    //     if(i % 5 == 0) printf("\n");
    // }
}

void makeBoard(int *board) {
    for (int i = 0; i < SIZE * SIZE; i++) {
        *board = i;
        board++;
    }
}

int main(int argc, char **argv) {
    int *board = (int *)malloc(25 * sizeof(int));

    makeBoard(board);
    printBoard(board);

    free(board);
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