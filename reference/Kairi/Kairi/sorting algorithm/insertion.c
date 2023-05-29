#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000

void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void insertion(int number[])
{
    int i, j, tmp;

    for(i=1; i < N; i++){
        tmp = number[i];
        j = i;
        while((j > 0) && (number[j-1] > tmp)){
            number[j] = number[j-1];
            j--;
        }
        number[j] = tmp;   
    }
}


int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    int number[N];
    int i = 0;

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
    insertion(number);
    clock_t end = clock();

    fp2 = fopen("./output000.dat", "w");
    for(i = 0; i < N; i++){
        fprintf(fp2, "%d\n", number[i]);
    }
    fclose(fp2);

    puts("Done!");
    printf("The elapsed time is %lf seconds \n", (double)(end - begin)/CLOCKS_PER_SEC);
    return 0;
}