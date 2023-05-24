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

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
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
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

void bucket1(int lines, int *p) {
    int k = 0;
    clock_t t;
    
    t = clock();
    while(k < lines - 1) {
        int last = lines - 1;
        for(int j = lines - 1; j > k; j--) {
            if(p[j-1] > p[j]) {
                swap(&p[j-1], &p[j]);
                last = j;
            }
        }
        k = last;
    }

    t = clock() - t;
    processTime(t);
}

void bucket(int lines, int  *p) {
    clock_t t;
    
    t = clock();
    for (int i = 0; i < lines; i++) {
        int exc = 0;
        for(int j = lines - 1; j > i; j--) {
            if(p[j-1] > p[j]) {
                swap(&p[j-1], &p[j]);
                exc ++;
            }
        }
        if(exc == 0) break;
    }

    t = clock() - t;
    processTime(t);
}

void bubbleSort(int lines, int *p) {
    clock_t t;
    
    t = clock();

    for (int i = 0; i < lines; i++) {
        for(int j = lines - 1; j > i; j--) {
            if(p[j-1] > p[j])
                swap(&p[j-1], &p[j]);
        }
    }

    t = clock() - t;
    processTime(t);
}

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;

    if (argc == 2) {
        if((in = fopen(argv[1], "r")) == NULL) {
            printf("input file name error\n");
            return 1; //kalau mau tambahin return2 ini
        }
    } else {
        printf("No file name stated \n");
        return 2;
    } 


    int lines = countLines(in);

    int *p = malloc(lines * sizeof(int));
    store_array(in, p);

    // ini pilih satu
    // bucket(lines, p);
    // bucket1(lines, p);
    bubbleSort(lines, p);
    
    // output
    out = fopen("bubble.dat", "w");

    for (int i = 0; i < lines; i++) {
        fprintf(out, "%d\n", p[i]);
    }

    free(p);
    fclose(in);
    fclose(out);

    
    return 0;
}