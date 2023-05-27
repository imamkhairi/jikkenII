#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *setFileName(int index) {
    char result[10];
    char prefix[4] = "data";
    char suffix[4] = ".dat";

    sprintf(result, "data%d.dat", 2);
    
    char *p = result;
    return p;
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

void bucketSort(FILE *in, int *p, int offset) {
    int x;
    clock_t t;
    
    rewind(in);

    t = clock();
    while (fscanf(in, "%d", &x) != EOF) {
        p[x-offset]++;
    }
    t = clock() - t;

    processTime(t);
}

int main(int argc, char *argv[]) {

    FILE *ptr;
    FILE *out;
    int max = 0;
    int min = 0;
    int x;

    if (argc == 2) {
        if((ptr = fopen(argv[1], "r"))== NULL)
            printf("input file name wrong\n");
    } else 
        printf("No file name stated\n");

    // start sorting 
    while(fscanf(ptr, "%d", &x) != EOF) {
        max = (max < x) ? x : max;
        min = (min > x) ? x : min;
    }

    int *p = calloc((max-min), sizeof(int));

    // bucketSort(ptr, p, min);

    char *name = setFileName(2);
    printf("%s", name);
    

    out = fopen("bucket.dat", "w");

    for (int i = 0; i <= (max-min); i++) { 
        if (p[i] > 0)
            for (int j = 0; j < p[i]; j++) 
                fprintf(out, "%d\n", i+min);
    }

    free(p);
    fclose(ptr);
    fclose(out);
    
    return 0;
}