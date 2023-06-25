#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#define diceEye 6
#define totaldice 6
#define DEBUG 0


int roll(int a[], int* b);
int randnum();

int main(int argc, char *argv[]){

    if(argc != 2){              
        puts("Parameter Error");
        return 0;
    }

    int N = atoi(argv[1]);
    
    int i;
    int dice[6];
    int TotalSame = 0;
    int success;
    srand((unsigned int)time(NULL));

    //clock_t start, end;

    for(i = 0; i < N; i++){
        success = roll(dice, &TotalSame);  

        if (success == 1){
#if DEBUG == 1
            printf("%d %d %d %d %d %d \n", dice[0], dice[1], dice[2], dice[3], dice[4], dice[5]);
            //sleep(2);
#endif
        }

    }
    printf("%d %d %lf %e\n", TotalSame, N, (double)TotalSame/(double)N, fabs(((double)1/(double)7666) - (double)TotalSame/(double)N));
    
    return 1;

}


int roll(int dice[], int* TotalSame)
{
    int i;
    int isSame = 1;

    dice[0] = rand()%6 + 1;

    for(i = 1; i <= totaldice - 1; i++){
        dice[i] = randnum();
        if(dice[0] == dice[i]) isSame++;
    }

    if (isSame == totaldice){
        *TotalSame += 1;
        return 1;
    }
    return 0;
}

int randnum(){
    return rand()%diceEye + 1;
}



