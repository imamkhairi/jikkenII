#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000

void swap(double *a, double *b){
    double tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(double number[]){
    int i,j, sorted;
    j = N;
    do{
        sorted = 1; j=j-1;
        for(i=1; i <= j; i++){
            if(number[i-1] < number[i]){
                swap(&number[i-1], &number[i]);
                sorted = 0;
            }
        }
    } while(!sorted);
}


int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    double number[N];
    int i;

    if(argc != 2){                         
        puts("Parameter Error");
        return 0;
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL){
        puts("NO FILE WITH THAT NAME");
        return 0;
    }

    for(i = 0; i < N; i++){
        fscanf(fp1, "%lf", &number[i]);
    }

    fclose(fp1);

    clock_t begin = clock();
    bubble_sort(number);
    clock_t end = clock();

    fp2 = fopen("./output000.dat", "w");
    for(i = N-1; i == 0; i--){
        fprintf(fp2, "%lf\n", number[i]);
    }
    fclose(fp2);

    puts("Done!");
    printf("The elapsed time is %lf seconds \n", (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}
