#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

void bucketSort(FILE *in, int *p) {
    int x;
    clock_t t;
    
    rewind(in);

    t = clock();
    while (fscanf(in, "%d", &x) != EOF) {
        p[x]++;
    }
    t = clock() - t;

    processTime(t);
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

    bucketSort(ptr, p);

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