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
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

void quick(int *p, int left, int right) {
    int pl = left;
    int pr = right;
    int x = p[(pl+pr)/2];

    do {
        while (p[pl] < x) pl++;
        while (p[pr] > x) pr--;
        if(pl <= pr) {
            swap(&p[pl], &p[pr]);
            pl++;
            pr--;
        }
    } while (pl <= pr);

    if (left < pr) quick(p, left, pr);
    if (right > pl) quick(p, pl, right);
}

void setFileName(char *dst, int index) {
    sprintf(dst, "data%d.dat", index);
}

void setOutFileName(char *dst, int index){
    sprintf(dst, "quick%d.dat", index);
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
        store_array(in, p);

        clock_t t;
        t = clock();

        quick(p, 0, lines -1);
    
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
    free(in);
    free(out);
}

int main(int argc, char **argv) {
    startSorting(8);

    return 0;
}