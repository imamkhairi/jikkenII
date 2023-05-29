#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data100.h"
#include"data500.h"
#include"data1000.h"
#define N 1000

int queue[N];
int known[N];
int item = -1;

void bfs(int node[][N]);

int main(void)
{
    int a[N][N];
    int (*p)[N];
    int i;
    p = a;
    for(i = 0; i < N; i++){
        Input1000s(*(p+i), i);
    }
    for(i = 0; i < N; i++){
        known[i] = 0;
        queue[i] = 0;
    }
    bfs(a);
    return 0;
}

void enqueue(int value){
    queue[++item] = value;
}

int dequeue(){
    int ver = queue[0];
    for(int i = 0; i < N; i++){
        queue[i] = queue[i+1];
    }
    item--;
    return ver;
}

int queueisempty(){
    if(item == -1) return 1;
    else return 0;
}

void bfs(int node[][N]){
    int i, j;
    int num = 0;
    i = 0;
    enqueue(i);
    known[i] = 1;
    
    while(1){
        
        for(j = 0; j < N; j++){
            if(node[i][j] == 1 && known[j] == 0){
                enqueue(j);
                known[j] = 1;
                printf("%d. %d -> %d\n", num+1, i+1, j+1);
                num+=1;
            }
        }
        if(j >= N-1){
            i = dequeue();
            j = 0;
            if(queueisempty() == 1) return;
        }
    }
}
