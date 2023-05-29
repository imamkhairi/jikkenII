#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#define TARGET 1000
#define N 1000000
#define PROB 9.0/19.0


int main(void) 
{
    int money;
    int win, lose;
    int i;
    double hantei;

    win = lose = 0;
    srand((unsigned int)time(NULL));

    for(i = 0; i < N; i++){
        money = 900;
        while(money < TARGET && money > 0){
            hantei = (double)rand() / RAND_MAX;
            if(hantei < PROB) money++;
            else money--;    
        }
        if(money>=TARGET)win++;
        else lose++;
    }
    printf("N win lose\n");
    printf("%d %d %d \n",N, win, lose);         

}
