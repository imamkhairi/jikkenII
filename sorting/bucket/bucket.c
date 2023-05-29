#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void setFileName(char *dst, int index) {
    sprintf(dst, "data%d.dat", index);
}

void setOutFileName(char *dst, int index){
    sprintf(dst, "bucket%d.dat", index);
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); 
}

void bucketSort(FILE *in, int *p, int *sort, int offset, int n) {
    int x;
    
    rewind(in);

    while (fscanf(in, "%d", &x) != EOF) {
        p[x-offset]++;
    }
    

    int s = 0;

    for (int i = 0; i <= n; i++) { 
        if (p[i] > 0)
            for (int j = 0; j < p[i]; j++) {
                sort[s] = i + offset;
                s++;
            }
    }
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

void startSorting(int n) {
    FILE *in;
    FILE *out;
    

    for (int i = 1; i <= n; i++) {
        int x;
        char *filename = malloc(10);
        char *outname = malloc(10);

        int max = 0;
        int min = 0;

        printf("%d  | ", i);
        
        setFileName(filename, i);

        if((in = fopen(filename, "r"))== NULL)
            printf("input file name wrong\n");

        while(fscanf(in, "%d", &x) != EOF) {
            max = (max < x) ? x : max;
            min = (min > x) ? x : min;
        }

        rewind(in);
        int lines = countLines(in);

        int *p = calloc((max-min), sizeof(int));
        int *s = malloc((lines) * sizeof(int));
        // int l = 0;

        clock_t t;
        t = clock();
        bucketSort(in, p, s, min, (max-min));
        t = clock() - t;
        processTime(t);

        setOutFileName(outname, i);


        out = fopen(outname, "w");

        for (int i = 0; i < lines; i++) {
            fprintf(out, "%d\n", s[i]);
        }
        
        free(p);
        free(s);
        free(filename);
        free(outname);
    }

    fclose(in);
    fclose(out);
}

int main() {
    startSorting(8);
    return 0;
}