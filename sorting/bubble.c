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

    // rewind(in);
}

void processTime(clock_t t) {
    double time = ((double)t)/CLOCKS_PER_SEC;
    printf("%.3lf ms\n", time*1000); //kali 1000 biar jadi ms
}

// ini masih belum jalan
void optimezedBucket(int n, int *p) {
    clock_t t;
    int k = 0;
    
    t = clock();
    while (k < n - 1) {
        int last = n -1;
        for(int j = n - 1; j > k; j--) {
            if(p[j-1] > p[j]) {
                swap(&p[j-1], &p[j]);
                last = j;
            }
            k = last;
        }
    }

    t = clock() - t;
    processTime(t);
}

void bucketSort(int lines, int *p) {
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
    } else 
        printf("No file name stated \n");

    int lines = countLines(in);

    int *p = malloc(lines * sizeof(int));
    store_array(in, p);


    // Sorting 
    // for (int i = 0; i < lines; i++) {
    //     for(int j = lines - 1; j > i; j--) {
    //         if(p[j-1] > p[j])
    //             swap(&p[j-1], &p[j]);
    //     }
    // }

    // bucketSort(lines, p);
    optimezedBucket(lines, p);
    
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