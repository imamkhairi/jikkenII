#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>

#define DEBUG 0
#define N 10

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle(int people[]){
    int i, j;
    for (i=0;i<N;i++){
        people[i] = i+1;
    }

    for (i=0;i<N;i++){
        j = rand() % N;
        swap(&people[i], &people[j]);
    }
}   

int check(int people[]){
    int i, j, flag, correct;
    correct = 0;

#if DEBUG == 1 
    for(i = 0; i < N; i++){
	    printf("%d ", people[i]);
    }
    puts("--");
#endif

    if(people[0] % 2 == 1 || people[N-1] == 10) return 0;
    if(people[0] == N) return 1;

    for(i = N-1; i > 0; i--){
        flag = 0;
        if (people[i] % 2 == 1){
            for(j = i-1; j>=0; j--){
                if(people[j] % 2 == 1) continue;
                else {
                    if (people[j] > people[i]){
#if DEBUG == 1                         
                        printf("indexJ=%d %d > index=%d %d its girl 000\n",j, people[j], i, people[i]);
#endif
                        flag = 1;
                        break;
                    } else {
#if DEBUG == 1     
                        printf("indexJ=%d %d > index=%d %d its girl xxx\n",j, people[j], i, people[i]);
#endif                        
                    }
                }
            }
        }
        if (flag == 1) {
            correct += 1;
        }
        if (correct >= 5){
#if DEBUG == 1     
            for(i = 0; i < N; i++){
                printf("%d ", people[i]);
            }
            puts("oo");
#endif
        return 1;
        }
    }
    
    return 0;
}   


int main(int argc, char *argv[]){

    if(argc != 2){              
        puts("Parameter Error");
        return 0;
    }

    int KAISUU = atoi(argv[1]);

    int people[N];
    int x = 0;
    srand((unsigned int)time(NULL));

    for(int i = 0; i < KAISUU; i++){
        shuffle(people);
        x += check(people);
    }
#if DEBUG == 1     
    printf("total true1 = %d\n", x);
	printf("Percentage : %0.5lf\n", (double)x/(double)KAISUU);
#endif

    printf("%d %lf %d\n", KAISUU, (double)x/(double)KAISUU, x);


    return 0;
}