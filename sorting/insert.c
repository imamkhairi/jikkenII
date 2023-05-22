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

    rewind(in);
}

void swap_int(int *a, int *b) {
    int tmp = *a; 
    *a = *b;
    *b = tmp;
}

int main(int argc, char **argv) {
    FILE *in;
    FILE *out;

    if (argc == 2) {
        if((in = fopen(argv[1], "r")) == NULL) 
            printf("input file name error\n");
            // return 1; kalau mau tambahin return2 ini
    } else 
        printf("No file name stated \n");

    int lines = countLines(in);

    int *p = malloc(lines * sizeof(int));
    store_array(in, p);

    for(int i = 1; i < lines; i++) {
        int key = p[i];
        int j = i-1;
        while (j >= 0 && p[j] > key) {
            // swap_int(&p[j], &key);
            p[j + 1] = p[j];
            j--;
        }
        p[j+1] = key;
    }

    
    // output
    out = fopen("insert.dat", "w");

    for (int i = 0; i < lines; i++) {
        fprintf(out, "%d\n", p[i]);
    }

    fclose(in);
    fclose(out);
    
    return 0;
}