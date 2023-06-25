#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data100.h"
#include"data500.h"
#include"data1000.h"

#define DEBUG 0
#define N 1000

int stack[N];
int known[N];
int top = -1;

void push(int value);
int pop();
int stackempty();
void dfs(int node[][N]);

int main(void)
{
    int a[N][N];
    int (*p)[N];
    int i;
    p = a;

    for(i = 0; i < N; i++){
        Input1000d(*(p+i), i);
    }

    for(i = 0; i < N; i++){
        known[i] = 0;
    }
    

#if DEBUG == 1   
    for(i = 0; i < N; i++){
        for(j=0; j < N; j++){
            printf("num[%d][%d] = %d\n", i,j,a[i][j]);
        }
    }
#endif

    dfs(a);
    return 0;
}

void push(int value){
    stack[++top] = value;
}

int pop(){
    int ver=stack[top--];
    return ver;
}

int stackempty(){
    if(top==-1) return 1;
    else return 0;
}

void dfs(int node[][N])
{
    int i = 0;
    int j;
    int num = 1;

    while(1){
        push(i);
        known[i] = 1;
        for(j = 0; j < N; j++){
            if(node[i][j] == 1 && known[j] == 0){
                printf("%d. %d -> %d\n", num, i+1, j+1);
                i = j;
                num++;
                break;
            }
            if(j >= N-1){
                i = pop();
                j = 0;
                if(stackempty() == 1) return;
            }
        }
    }
}
    
    
    
    


        
    
