#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bucketSort(FILE *in, int *p) {
    int x;
    rewind(in);
    while (fscanf(in, "%d", &x) != EOF) {
        p[x]++;
    }
}

int main(int argc, char *argv[]) {

    FILE *ptr;
    FILE *out;
    int max = 0;
    int x;

    if (argc == 2) {
        if((ptr = fopen(argv[1], "r"))== NULL)
            printf("input file name wrong\n");
    } else 
        printf("No file name stated\n");
    
    while(fscanf(ptr, "%d", &x) != EOF) { //get max value
        max = (max < x) ? x : max;
    }

    int *p = calloc(max, sizeof(int));

    clock_t t;
    t = clock();
    bucketSort(ptr, p);
    t = clock() - t;

    double time = ((double)t)/CLOCKS_PER_SEC /1000; 
    printf("%.5le\n", time);

    out = fopen("bucket.dat", "w");

    for (int i = 0; i <= max; i++) { //output
        if (p[i] > 0)
            for (int j = 0; j < p[i]; j++) 
                fprintf(out, "%d\n", i);
    }

    free(p);
    fclose(ptr);
    fclose(out);
    
    return 0;
}