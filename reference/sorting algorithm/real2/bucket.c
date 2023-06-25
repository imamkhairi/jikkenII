#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000

int maxval(int a[])
{
    /*最大値を探す関数*/
    int max = a[0];
    int i;
  
    for(i = 1; i < N; i++){
        if(max < a[i]){
            max = a[i];
        }
    } 
    return max;
}

void bucket_sort(int number[], int maxvalue)
{
    int bucket[maxvalue + 1];
    int i,j, counter;

    /*最大値までバケツを準備する*/
    for(i = 0; i <= maxvalue; i++){
        bucket[i] = 0;
    }

    /*バケツに入れる*/
    for(i = 0; i < N; i++){
        bucket[number[i]] += 1;
    }
    
    /*ソートする*/
    j = 0;
    for(i = 0; i <= maxvalue; i++){
        if (bucket[i] != 0){
            counter = bucket[i];
            while(counter > 0){
                number[j] = i;
                j++; counter--;
            }
        }
    }
}

int main(int argc, char *argv[]){

    FILE *fp1;
    FILE *fp2;
    int number[N];
    int i;
    int maxvalue;

    if(argc != 2){                         
        puts("Parameter Error");
        return 0;
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL){
        puts("NO FILE WITH THAT NAME");
        return 0;
    }

    for(i = 0; i < N; i++){
        fscanf(fp1, "%d", &number[i]);
    }

    fclose(fp1);

    clock_t begin = clock();

    maxvalue = maxval(number);
    bucket_sort(number, maxvalue);

    clock_t end = clock();

    fp2 = fopen("./output000.dat", "w");
    for(i = 0; i < N; i++){
        fprintf(fp2, "%d\n", number[i]);
    }
    fclose(fp2);

    printf("%0.6lf\n", (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}
