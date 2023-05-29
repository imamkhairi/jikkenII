#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 100000
#define tambah 50000

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
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

void quick_sort(int arr[], int low, int high)
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
    int number[N];
    int number2[N+tambah];
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

    quick_sort(number, 0, N-1);

    for(i = 0; i < N; i++){
	    number2[i] = number[i];
    }
    for(i = 0; i < tambah; i++){
	    number2[N+i] = i;
    }
	
    clock_t begin = clock();
    quick_sort(number2, 0, N+tambah-1);
    clock_t end = clock();

    fp2 = fopen("./output000.dat", "w");
    for(i = 0; i < N+tambah; i++){
        fprintf(fp2, "%d\n", number2[i]);
    }
    fclose(fp2);

    puts("Done!");
    printf("The elapsed time is %lf seconds \n", (double)(end - begin)/CLOCKS_PER_SEC);

  /*  //new kuufu
    clock_t begin = clock();
    int indeks = findmid(number2);
    quick_sort(number2, 0, N-1);
    clock_t end = clock();

    fp2 = fopen("./output000.dat", "w");
    for(i = 0; i < N; i++){
        fprintf(fp2, "%d\n", number2[i]);
    }
    fclose(fp2);
*/
    return 0;
}
