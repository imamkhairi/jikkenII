#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include<time.h>

#define DEBUG 0
#define N 10

void create_people(int* people);
void show_people(int* people);
void shuffle(int* people);
void swap(int *a, int *b);
int check_people(int* people);

int main(int argc, char *argv[]){

    if(argc != 2){
        puts("Parameter Error");
        return 0;
    }
    int KAISUU = atoi(argv[1]);
    int x = 0;
    int *people;
    int i;

    people = (int*)malloc(sizeof(int)*N);
    srand((unsigned int)time(NULL));

    
    //show_people(people);
    

    for(i=0;i<KAISUU;i++){
        create_people(people);
        shuffle(people);
        //show_people(people);
        x += check_people(people);
    }
    //printf("x value = %d\n", x);
    printf("%d %.6lf %d\n", KAISUU, (double)x / (double)KAISUU, x);
    free(people);


    return 0;
}

int check_people(int* people){
    int i, total_true, max;
    total_true = 0;

    //even is men, odd is woman 10>9>8>...>1
    if(people[0] == 10) return 1;
    if(people[0] % 2 == 1) return 0;
    else{
        max = people[0];
        for(i=1;i<N;i++){
            if(people[i] % 2 == 1){
                if(max > people[i]) continue;
                else return 0;
            } else {
                if(people[i] > max) max = people[i];
            }
        }
    }
    return 1;
}

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void shuffle(int* people){
    int i, index, temp;

    for(i=0; i<N; i++){
        index = rand()%9+1;
        swap(&people[i], &people[index]);
    }
}

void create_people(int* people){
    int i;
    for(i=N-1;i>=0;i--){
        people[i] = i+1;
    }
}

void show_people(int* people){
    int i;
    for(i=0;i<N;i++){
        printf("%2d  ",people[i]);
    }
    puts(" ");
}