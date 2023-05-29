#include<stdio.h>
#include"data30.h"
#define N 50

void make_all_set(int a[][N], int b[][2]){
    FILE *fp; 
    fp = fopen("all_vertices.csv", "w");
    int known[N] ;
    int i, j;
    for(i = 0; i < N; i++){
        known[i] = 0;
    }

    for(i = 0 ; i < N; i++){
        for (j = 0; j < N; j++){
            if(a[i][j] == 1 && (known[i] == 0 && known[j] == 0)){
                fprintf(fp, "%d %d\n", i, j);
            }
        }
        known[i] = 1;
    }
    fclose(fp);
    
    int num1, num2;
    puts("B配列の初期化する");
    for(i = 0; i < N; i++){
        for(j = 0; j < 2; j++){
            b[i][j] = 0;
        }
    }
    
    puts("B配列にデータを入れる");
    fp = fopen("all_vertices.csv", "r");
    while(fscanf(fp, "%d %d", &num1, &num2) != EOF){
        b[num1][0] += 1;
        b[num2][1] += 1;
    }
    fclose(fp);

    fp = fopen("no_start_another.csv", "w");
    for(i = 0; i < N; i++){
        fprintf(fp, "%2d %2d %2d\n", i , b[i][0], b[i][1]);
    }
    fclose(fp);

    fp = fopen("no_all.csv", "w");
    for(i = 0; i < N; i++){
        fprintf(fp, "%2d %2d\n", i , b[i][0]+b[i][1]);
    }
    fclose(fp);
}

int find_the_smalldegree(int b[][2]){
    int min_no;
    int min_no_num;
    int i = 0;

    /*一番小さい探す*/
    for(i = 0; i < N; i++){
        if(b[i][0] + b[i][1] == 0) continue;
        min_no = b[i][0] + b[i][1];
        min_no_num = i;
    }

    for(i=0; i < N; i++){
        if((b[i][1] + b[i][0]) < min_no && ((b[i][1] + b[i][0]) != 0)){
            min_no = b[i][1] + b[i][0];
            min_no_num  = i;
        }
    }
    printf("%d番が一番少ない持っている = %d\n", min_no_num, min_no);
    return min_no_num;
}

void make_new_set(int min)
{   
    int num1, num2;
    FILE *fp1;
    FILE *fptmp;

    fptmp = fopen("all_vertices_temp.csv" , "w");
    fp1 = fopen("all_vertices.csv", "r");

    puts("tempファイルにコーピする");
    while(fscanf(fp1, "%d %d", &num1, &num2) != EOF){
        fprintf(fptmp, "%2d %2d\n", num1, num2);
    }

    fclose(fptmp);
    fclose(fp1);

    /*tempファイルからメインファイルにB配列の結果
    を用い,コーピする*/
    fptmp = fopen("all_vertices_temp.csv" , "r");
    fp1 = fopen("all_vertices.csv", "w");
    puts("コーピする");
    while(fscanf(fptmp, "%d %d", &num1, &num2) != EOF){
        if(num1 == min || num2 == min) continue; 
        fprintf(fp1, "%2d %2d\n", num1, num2);
    }
    fclose(fptmp);
    fclose(fp1);
}

void make_new_barray(int b[][2])
{
    FILE *fp;
    int num1, num2; 
    int i, j;

    puts("B配列を初期化と更新する");
    for(i = 0; i < N; i++){
        for(j = 0; j < 2; j++){
            b[i][j] = 0;
        }
    }
    fp = fopen("all_vertices.csv", "r");
    while(fscanf(fp, "%d %d", &num1, &num2) != EOF){
        b[num1][0] += 1;
        b[num2][1] += 1;
    }
    fclose(fp);
}

int check(int b[][2]){

    FILE *fp;
    int i;
    fp = fopen("no_start_another.csv", "w");
    for(i = 0; i < N; i++){
        fprintf(fp, "%2d %2d %2d\n", i , b[i][0], b[i][1]);
    }
    fclose(fp);

    fp = fopen("no_all.csv", "w");
    for(i = 0; i < N; i++){
        fprintf(fp, "%2d %2d\n", i , b[i][0]+b[i][1]);
    }
    fclose(fp);

    int diff = 0;
    int res;
    int flag = 0;
    for(i = 0; i < N-1; i++){
        if(b[i][0]+b[i][1] == 0) continue;
        if(flag == 0) {
            res = b[i][0]+b[i][1];
            flag = 1; continue;
        } else {
            if(res != (b[i][0]+b[i][1])){
                diff = 1;
                return diff;
            }
        }
    }
    return diff;
}

int main(void)
{
    int a[N][N]; 
    int b[N][2];
    int (*p)[N];
    int i;
    p = a;

    for(i = 0; i < N; i++){
        Input50(*(p+i), i);
    }

    make_all_set(a,b);

    int min, diff = 0;
    while(1){
        min = find_the_smalldegree(b);
        make_new_set(min);
        make_new_barray(b);
        diff = check(b);
        if(diff == 0) break;
    }
    printf("+====+\n");
    printf("|結果|\n");
    printf("+====+\n");
    int kn = 0;
    for(i = 0; i < N; i++){
        if(b[i][0] + b[i][1] != 0){
            kn+=1; 
            printf("%d ", i);
        }
    }
    printf("\n");
    printf("最大クリークは[%d]\n", kn);
    return 0;
}
