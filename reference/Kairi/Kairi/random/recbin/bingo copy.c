#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>


#define DEBUG 0
#define N 5
#define NUM 1000000

void create_numarray(int *bingo, int*test);
void create_bingo(int* bingo);
void tester(int *test);
void hyoji(int *bingo);
int play(int *bingo, int* counter);
int check(int *bingo);


int main(int argc, char *argv[]){

    int* bingo;
    int number;
    int counter;
    int min, mid, max;

    counter = 0;
    min = mid = max = 0;
    srand((unsigned int)time(NULL));

    for(int i=0; i < NUM; i++){
        bingo = (int*)malloc(sizeof(int)*N*N);
        create_bingo(bingo);
        play(bingo, &counter);
        //printf("counter mian = %d\n", counter);
        if(counter == 4) {
            min += 1;
        //   hyoji(bingo);
        }
        else if(counter == 71){
         max += 1; 
        }
        else if(counter <= 10) mid += 1;
        free(bingo);
        counter = 0;
    }

    printf("min mid max\n");
    printf("%d %d %d\n",min,mid,max);
    
    return 0;
}

void create_bingo(int* bingo){

    int y,x;
    int *test;

    test = (int*)malloc(sizeof(int)*75);
    tester(test);
    create_numarray(bingo, test);
    free(test);
}

void tester(int *test){
    int y,x;
    for(y = 0; y < 75; y++){
            test[y] = 0;
    }

}

void create_numarray(int *bingo, int* test){
    int num, index;
    int x,y;
    int min, max;
    min = 1; max = 15;
    for (x = 0; x < N; x++){
    y = 0;
        while(1){
            index = rand()%(max-min+1) + min;
            num = index + 1;

            //check
            if(test[index] == 0){
                bingo[y * N + x] = num;
                test[index] = 1;
                y++; 
            }

            if (y >= 5) {
                max += 15;
                min += 15;
                break;
            }
        }
    }
    bingo[2*N+2] = 0;
}

void hyoji(int *bingo){
    int y, x;
        printf("\n");
        for (y = 0; y < N; y++) {
            for (x = 0; x < N; x++) {
                printf("%6d", bingo[y * N + x]);
            }
            printf("\n");
        }
}

int play(int *bingo, int* counter){

    int i, number;
    int *test;
    test = (int*)malloc(sizeof(int)*75);
    tester(test);    

    while(1) {
        number = rand()%75 + 1;
        if(test[number] != 1){
            *counter += 1;
            test[number] = 1;
            //printf("number = %d %d\n ", number, *counter);
            for(i = 0; i < N*N; i++){
                if(bingo[i] == number){
                    bingo[i] = 0;
                    //printf("number = %d %d\n ", number, *counter);
                    //printf("%d counter \n", *counter);
                    
                }
            }
            //hyoji(bingo);
            if(check(bingo) == 1) {
                if (*counter <= 10) {
                    //printf("%d counter \n", *counter);
                }
                free(test);
                return 1;
            }
        }else continue;
    }  
}

int check(int *bingo){
    int x, y;

    //horizontal
    for(y = 0; y < N; y++){
        if (bingo[y * N + 0] == bingo[y * N + 1] && 
            bingo[y * N + 1] == bingo[y * N + 2] &&
            bingo[y * N + 2] == bingo[y * N + 3] &&
            bingo[y * N + 3] == bingo[y * N + 4] &&
            bingo[y * N + 4] == bingo[y * N + 1] ) return 1;
    }
        

    //vertical
    for(x = 0; x < N; x++){
        if(bingo[x + N * 0] == bingo[x + N * 1] &&
           bingo[x + N * 1] == bingo[x + N * 2] &&
           bingo[x + N * 2] == bingo[x + N * 3] &&
           bingo[x + N * 3] == bingo[x + N * 4] &&
           bingo[x + N * 4] == bingo[x + N * 0]) {
            //printf("its vertical %d %d %d %d %d\n", bingo[x + N * 0] , bingo[x + N * 1] , bingo[x + N * 2] , bingo[x + N * 3] ,bingo[x + N * 4]); 
            return 1;
        }
    }

    //diagonal left-right
    if (bingo[0] == bingo[6] &&
        bingo[6] == bingo[12] && 
        bingo[12] == bingo[18] && 
        bingo[18] == bingo[24]) {
        //printf("its dig 1 %d %d %d %d %d\n", bingo[0], bingo[6], bingo[12], bingo[18], bingo[24]); return 1;
    }

    //diagonal right-left
    if (bingo[4] == bingo[8] &&
        bingo[8] == bingo[12] && 
        bingo[12] == bingo[16] && 
        bingo[16] == bingo[20]) {
        //printf("its dig 2 %d %d %d %d %d\n", bingo[4], bingo[8], bingo[12], bingo[16], bingo[20]); return 1;
    }

}
