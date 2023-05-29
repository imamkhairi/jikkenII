#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    // rewind(in);
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

// ini bisa dicoba bikin yang kalau store semua dulu baru sort
void insertionSort(FILE *in, int lines, int *p) {
    clock_t t;
    int key;
    int i = 0;

    t = clock();

    while (fscanf(in, "%d", &key) != EOF) {
        p[i] = key;
        int j = i - 1;
        while(j >= 0 && p[j] > key) {
            p[j+1] = p[j];
            j--;
        }
        p[j+1] = key;
        i ++;
    }
    
    t = clock() - t;
    processTime(t);
}

void setFileName(char *dst, int index) {
    sprintf(dst, "data%d.dat", index);
}

void setOutFileName(char *dst, int index){
    sprintf(dst, "insert%d.dat", index);
}

void startSorting(int n) {
    FILE *in;
    FILE *out;

    for (int i = 1; i <= n; i++) {
        char *filename = malloc(10);
        char *outname = malloc(10);

        printf("%d  | ", i);

        setFileName(filename, i);

        if((in = fopen(filename, "r")) == NULL)
            printf("input file name error\n");

        int lines = countLines(in);
        int *p = malloc(lines * sizeof(int));

        insertionSort(in, lines, p);

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

int main(void) {
    startSorting(8);
    return 0;
}