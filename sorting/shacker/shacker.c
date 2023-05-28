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

void shacker(const int lines, int *p) {
    int right = lines - 1;
    int left = 0;

    clock_t t;
    
    t = clock();
    while(left != right) {
        int i;
        int j;
        int last;

        for(i = left; i < right; i++) {
            if(p[i] > p[i+1]) {
                swap(&p[i], &p[i+1]);
                last = i;
            }
        }
        right = last;
        for(int j = right; j > left; j--) {
            if(p[j-1] > p[j]) {
                swap(&p[j-1], &p[j]);
                last = j;
            }
        }
        left = last;
    }

    t = clock() - t;
    processTime(t);
}

void setFileName(char *dst, int index) {
    sprintf(dst, "data%d.dat", index);
}

void setOutFileName(char *dst, int index){
    sprintf(dst, "shacker%d.dat", index);
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

        shacker(lines, p);

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