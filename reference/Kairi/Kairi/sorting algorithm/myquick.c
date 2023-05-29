#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 20
#define SA 3

void swap(int *a, int *b);
int partition(int arr[], int low, int high, int total);
void quick_sort(int arr[], int low, int high, int total);
int findmid(int arr[], int low, int high, int midval);

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

    //old
    clock_t begin = clock();
    quick_sort(number, 0, N-    1, N);
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

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, int total)
{
    int indekspivot = findmid(arr, low, high, total);
    int pivot = arr[indekspivot];
    printf("pivot = %d\n", pivot);
    int i = (low - 1); 
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++; 
            if(i >= indekspivot) indekspivot++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[indekspivot]);

    for(i = 0; i < high; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return (i + 1);
}

void quick_sort(int arr[], int low, int high, int total)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, (int)(total/2));

        quick_sort(arr, low, pi - 1, (int)(total));
        quick_sort(arr, pi + 1, high, (int)(total));
    }
}

int findmid(int arr[], int low, int high, int midval)
{
    int rabbit, turtle;
    rabbit = 1;
    for(int i = 0; i <= high; i++)
    {
        rabbit += 3;
        turtle = i;
        if (rabbit >= high || midval == 0) return high;

        if (arr[rabbit] >= (midval - SA) && arr[rabbit] <= (midval + SA)){
            printf("nilai midval = %d func rabbit\n", midval);
            return rabbit;
        }
        else if (arr[turtle] >= (midval - SA) && arr[turtle] <= (midval + SA)){
            printf("nilai midval = %d func turtle\n", midval);
            return turtle;
        }
    }
    printf("no func\n");
    return high;
}
















































