
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void compSwap(int a[], int i, int j, int dir)
{
	if (dir==(a[i]>a[j]))
		swap(&a[i],&a[j]);
}

void bitonicMerge(int a[], int low, int count, int dir)
{
	if (count>1)
	{
		int k = count/2;
		for (int i=low; i<low+k; i++) compSwap(a, i, i+k, dir);
		bitonicMerge(a, low, k, dir);
		bitonicMerge(a, low+k, k, dir);
	}
}


void bitonicSort(int a[],int low, int count, int dir)
{
	if (count>1)
	{
		int k = count/2;

		bitonicSort(a, low, k, 1);
		bitonicSort(a, low+k, k, 0);

		bitonicMerge(a,low, count, dir);
	}
}

void sort(int a[], int N, int up)
{
	bitonicSort(a,0, N, up);
}

int  countLines(FILE *in) {
    char c;
    int count = 0;

    do {
        c = fgetc(in);
        if(c == '\n') count++;
    } while (c != EOF);

    rewind(in);

    return count;
}

void store_array(FILE *in, int *p) {
    int x;
    int i = 0;

    while (fscanf(in, "%d", &x) != EOF) {
        p[i] = x;
        i++;
    }
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); 
}

void setFileName(char *dst, int index) {
    sprintf(dst, "data%d.dat", index);
}

void setOutFileName(char *dst, int index){
    sprintf(dst, "bitonic%d.dat", index);
}

int main() {   
    FILE *in;
    FILE *out;

    for (int i = 1; i <= 8; i++) {
        char *filename = malloc(10);
        char *outname = malloc(10);

        printf("%d  | ", i);
        
        setFileName(filename, i);

        if((in = fopen(filename, "r")) == NULL)
            printf("input file name error\n");

        int lines = countLines(in);

        int *p = malloc(lines * sizeof(int));
        store_array(in, p);

        int a[]= {3, 7, 4, 8, 6, 2, 1, 5};
        int N = sizeof(a)/sizeof(a[0]);

        clock_t t;
        
        t = clock();
        sort(p, lines, 1);
        t = clock() - t;
        processTime(t);

        setOutFileName(outname, i);

        out = fopen(outname, "w");

        for (int i = 0; i < lines; i++) {
            fprintf(out, "%d\n", p[i]);
        }

        free(p);
        free(filename);
        free(outname);
    }

	fclose(in);
    fclose(out);
}
