#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#define TARGET 1000
#define PROB 9.0/19.0


int main(int argc, char *argv[]) 
{
    if(argc != 2){              
        puts("Parameter Error");
        return 0;
    }

    int N = atoi(argv[1]);
    FILE* fp1;
    int money;
    int win, lose;
    int i, iter;
    double hantei;

    fp1 = fopen("kekka/roul.csv","a+");
    win = lose = 0;
    srand((unsigned int)time(NULL));
        iter = 0;

    for(i = 0; i < N; i++){
        money = 900;
        while(money < TARGET && money > 0){
            hantei = (double)rand() / RAND_MAX;
            if(hantei < PROB) money++;
            else money--;    
        }
        if(money>=TARGET)win++;
        else lose++;
        iter++;
        if(iter % 10000 == 0){
            printf("N[%d]\tkaisuu[%d]\titer[%d]\n", N, i, iter);
            iter = 0;
        }
    }
    
    fprintf(fp1, "%d %d %d \n", N, win, lose);
    fclose(fp1);

}