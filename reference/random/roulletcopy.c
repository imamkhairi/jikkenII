#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>
#define HighestNum 19
#define TARGET 1000
#define N 10000


int main(void) {

    int money;
    int i, iter;
    int matchLose, matchWin;
    double prob = 9.0/19.0;
    
    iter = 0;
    matchLose = matchWin = 0;
    srand((unsigned int)time(NULL));

    for(i = 0; i < N; i++){
        money = 900;
        while(money > 0 && money < 1000){
            iter++;
            if((double)rand()/(double)(RAND_MAX) < prob){
                money -= 1; 
            } else {
                money += 1;
            }
            if(iter % 1000 == 0 && N % 1000 == 0){   
                printf("N=%d\t kaisuu=%d\t money = %d\n",i, iter, money);
            }
        }
        iter = 0;
        if(money <= 0) matchLose+=1;
        if(money >= 1000) matchWin+=1;
    }
    printf("N win lose\n");
    printf("%d %d %d \n",N, matchWin, matchLose);  
}





