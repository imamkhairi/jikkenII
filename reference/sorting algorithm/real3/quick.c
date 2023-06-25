#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000

void swap(double * a, double * b)
{
    double  t = *a;
    *a = *b;
    *b = t;
}

int partition(double  arr[], int low, int high)
{
    double  pivot = arr[high];
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++; 
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(double  arr[], int low, int high)
{
    if (low < high)
    {
       
        int pi = partition(arr, low, high);
 
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}


int main(int argc, char *argv[])
{
    FILE *fp1;
    FILE *fp2;
    double  number[N];
    double  number2[N+100];
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
        fscanf(fp1, "%lf", &number[i]);
    }

    fclose(fp1);

    clock_t begin;
    quick_sort(number, 0, N-1);
    clock_t end;
    	
    for (i = 0; i < N-1; i++){
    	number2[i] = number[i];
    }
    for (i = 0; i < 100; i++){
	number2[N+i] = 0;
    }
	    
    begin = clock();
    quick_sort(number2, 0, N+99);
    end = clock();
    printf("The elapsed time is %lf seconds \n", (double)(end - begin)/CLOCKS_PER_SEC);


    fp2 = fopen("./output000.dat", "w");
    for(i = 0; i < N+100; i++){
        fprintf(fp2, "%lf\n", number2[i]);
    }
    fclose(fp2);
    return 0;
}
